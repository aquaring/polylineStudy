#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    svg.load("japan_district.svg");

    int size = svg.getNumPath();
    for (int i = 0; i < size; i++) {
        ofPath path = svg.getPathAt(i);
        // SVGから、アウトラインを取得する場合に、設定する
        path.setPolyWindingMode(OF_POLY_WINDING_ODD);
        vector<ofPolyline>& polyline = path.getOutline();
        for (vector<ofPolyline>::iterator pit = polyline.begin(); pit < polyline.end(); pit++) {
            ofRectangle rect = pit->getBoundingBox();
            // ようわからんけど、邪魔な子がいる
            if (rect.width < 8 && rect.height < 8) {
                continue;
            }
            svgLine svgInfo;
            svgInfo.polyline = pit->getResampledByCount(50);
            svgInfo.width = rect.width;
            svgInfo.height = rect.height;
            // x, yの開始位置
            svgInfo.basePosition = rect.getPosition();

            if (maxWidth < rect.width) {
                maxWidth = rect.width;
            }
            if (maxHeight < rect.height) {
                maxHeight = rect.height;
            }
            // 各ポイントの位置を再設定する
            vector<ofPoint>& vertices = svgInfo.polyline.getVertices();
            for(vector<ofPoint>::iterator it = vertices.begin(); it < vertices.end(); it++) {
                it->x = it->x - svgInfo.basePosition.x;
                it->y = it->y - svgInfo.basePosition.y;
            }
            svgLines.push_back(svgInfo);

        }
    }

    maxWidth = 500;
    maxHeight = 500;
    
    currIndex = 0;
    morphingCount = 0;
    maxMorphingCount = 100;
}

//--------------------------------------------------------------
void ofApp::update(){
    drawLine.clear();
    triangulation.reset();
    
    // 現在の位置
    vector<ofPoint>& points = svgLines[currIndex].polyline.getVertices();
    float scaleWidth = (maxWidth/svgLines[currIndex].width);
    float scaleHeight = (maxHeight/svgLines[currIndex].height);
    if (scaleWidth < scaleHeight) {
        scaleHeight = scaleWidth;
    } else {
        scaleWidth = scaleHeight;
    }
    
    // 次の位置
    int nextIndex = currIndex == svgLines.size() - 1 ? 0 : currIndex + 1;
    vector<ofPoint>& nextPoints = svgLines[nextIndex].polyline.getVertices();
    float nextScaleWidth = (maxWidth/svgLines[nextIndex].width);
    float nextScaleHeight = (maxHeight/svgLines[nextIndex].height);
    if (nextScaleWidth < nextScaleHeight) {
        nextScaleHeight = nextScaleWidth;
    } else {
        nextScaleWidth = nextScaleHeight;
    }
    
    // モーフィング処理
    float size = points.size();
    float value = ofMap(morphingCount, 0, maxMorphingCount, 0.f, 1.f);
    // イージング
    //value = 1 - pow(1 - value, 5);
    value = easingOutBounce(value);
    for (int i = 0; i < size; i++) {
        // たまにサンプル数分、頂点をくれない場合がある
        if (i >= nextPoints.size()) {
            continue;
        }
        float x = ofMap(value, 0.f, 1.f, points[i].x*scaleWidth, nextPoints[i].x*nextScaleWidth);
        float y = ofMap(value, 0.f, 1.f, points[i].y*scaleHeight, nextPoints[i].y*nextScaleHeight);
        drawLine.addVertex(x, y);
        triangulation.addPoint(ofPoint(x, y));
    }
    
    morphingCount++;
    if (morphingCount > maxMorphingCount) {
        morphingCount = 0;
        currIndex++;
        if (currIndex == svgLines.size()) {
            currIndex = 0;
        }
    }
    drawLine.close();
    triangulation.triangulate();
}

// jQuery easing pluginを参考に
float ofApp::easingOutBounce(float v) {
    float ret = v;
    if (ret < (1/2.75)) {
        ret = 7.5625*pow(ret, 2);
    } else if (ret < (2/2.75)) {
        ret -= (1.5/2.75);
        ret = 7.5625*pow(ret, 2) + .75;
    } else if (ret < (2.5/2.75)) {
        ret -= (2.25/2.75);
        ret = 7.5625*pow(ret, 2) + .9375;
    } else {
        ret -= (2.625/2.75);
        ret = 7.5625*pow(ret, 2) + .984375;
    }
    
    return ret;
}

//--------------------------------------------------------------
void ofApp::draw(){

    svg.draw();
    
    ofPushMatrix();

    ofPoint cent = drawLine.getCentroid2D();
    ofTranslate(ofGetWidth()/2 - cent.x, ofGetHeight()/2 - cent.y);
    
    ofSetColor(255);
    
    // ドロネーでぬりつぶす（色は、面積に対応）
    ofFill();
    ofMesh triangulationMesh = triangulation.triangleMesh;
    
    ofMesh drawMesh;
    drawMesh.setMode(OF_PRIMITIVE_TRIANGLES);
    vector<ofMeshFace> uniqueFaces = triangulationMesh.getUniqueFaces();
    for (vector<ofMeshFace>::iterator it = uniqueFaces.begin(); it < uniqueFaces.end(); it++) {
        ofVec3f v1 = it->getVertex(0);
        ofVec3f v2 = it->getVertex(1);
        ofVec3f v3 = it->getVertex(2);
        
        // 面積の計算　外積の大きさ/2
        float area = (v1 - v2).cross(v3 - v2).length()/2.f;
        // ええかんじに調整
//        area /= 40.f;
//        area = min(255.f, area);

        area /= 10000.f;
        area = min(1.f, area);
        area = 1 - pow(1 - area, 3);
        area *= 255.f;
        ofColor c(255, 255, area, area*0.8);
        
        drawMesh.addVertex(v1);
        drawMesh.addVertex(v2);
        drawMesh.addVertex(v3);
        
        drawMesh.addColor(c);
        drawMesh.addColor(c);
        drawMesh.addColor(c);
    }
    drawMesh.draw();
    
    ofNoFill();
    triangulation.draw();
    
    ofFill();
    vector<ofPoint> &vertices = drawLine.getVertices();
    int size = vertices.size();
    // １ポイントごと
    for (int i = 0; i < size; i++) {
        ofPoint point = vertices.at(i);
        ofPushMatrix();
        ofTranslate(point.x, point.y);
        // 頂点
        float b = ofMap(point.y, 0, ofGetHeight(), 255.f, 0.f);
        ofSetColor(0, 255, b);
        ofCircle(0, 0, 8);
        // 法線
        ofVec3f normal = drawLine.getNormalAtIndex(i);
        normal *= 30;
        ofSetColor(255, 0, b);
        ofLine(0, 0, normal.x, normal.y);

        ofPopMatrix();
    }
    ofSetColor(55, 0, 55);
    
    ofCircle(cent.x, cent.y, 20);
    
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
