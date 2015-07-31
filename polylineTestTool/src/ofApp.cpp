#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    
    ttf.loadFont("apple_gothic.ttf", 72, true, false, true);
    svg.load("test.svg");
    for (int i = 0; i < svg.getNumPath(); i++){
        ofPath p = svg.getPathAt(i);
        // svg defaults to non zero winding which doesn't look so good as contours
        p.setPolyWindingMode(OF_POLY_WINDING_ODD);
        vector<ofPolyline>& lines = p.getOutline();
        for(int j=0;j<(int)lines.size();j++){
            svgLines.push_back(lines[j]);
        }
    }
    
    spacing = 5.f;
    count = 20;
    smoothed = 5;
    
    gui = new ofxUISuperCanvas("SETTING");
    gui->addSpacer();
    gui->addSlider("SPACING", 0.1, 100.0, &spacing)->setTriggerType(OFX_UI_TRIGGER_ALL);
    gui->addSlider("COUNT", 1.0, 100.0, &count)->setTriggerType(OFX_UI_TRIGGER_ALL);
    gui->addSlider("SMOOTHED", 1.0, 100.0, &smoothed)->setTriggerType(OFX_UI_TRIGGER_ALL);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // フォントの表示
    ofSetColor(255);
    ttf.drawString("FONT", 250, 110);
    
    vector<ofTTFCharacter> vecTtf = ttf.getStringAsPoints("FONT");
    
    ofDrawBitmapString("SPACING", 100, 230);
    ofDrawBitmapString("COUNT", 100, 340);
    ofDrawBitmapString("SMOOTHED", 100, 450);
    ofDrawBitmapString("SPACING + SMOOTHED", 100, 560);
    ofDrawBitmapString("COUNT + SMOOTHED", 100, 670);
    
    
    ofPushMatrix();
    ofTranslate(250, 200);
    
    // 一文字ごと
    for (vector<ofTTFCharacter>::iterator it = vecTtf.begin(); it < vecTtf.end(); it++) {
        ofSetColor(255);
        //it->draw(0, 0);
        vector<ofPolyline> &outline = it->getOutline();
        
        int size = outline.size();
        for (int i = 0; i < size; i++) {
            ofPolyline polyline = outline.at(i);
            drawPolyline(polyline);
            ofPushMatrix();
            ofTranslate(0, 110);
            drawPolyline(polyline.getResampledBySpacing(spacing));
            ofTranslate(0, 110);
            drawPolyline(polyline.getResampledByCount(count));
            ofTranslate(0, 110);
            drawPolyline(polyline.getSmoothed(smoothed));
            ofTranslate(0, 110);
            drawPolyline(polyline.getResampledBySpacing(spacing).getSmoothed(smoothed));
            ofTranslate(0, 110);
            drawPolyline(polyline.getResampledByCount(count).getSmoothed(smoothed));
            ofPopMatrix();
        }
    }
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(500, 10);
    svg.draw();
    
    ofTranslate(0, 110);
    for (int i = 0; i < svgLines.size(); i++) {
        
        ofPolyline polyline = svgLines.at(i);
        drawPolyline(polyline);
        ofPushMatrix();
        ofTranslate(0, 110);
        drawPolyline(polyline.getResampledBySpacing(spacing));
        ofTranslate(0, 110);
        drawPolyline(polyline.getResampledByCount(count));
        ofTranslate(0, 110);
        drawPolyline(polyline.getSmoothed(smoothed));
        ofTranslate(0, 110);
        drawPolyline(polyline.getResampledBySpacing(spacing).getSmoothed(smoothed));
        ofTranslate(0, 110);
        drawPolyline(polyline.getResampledByCount(count).getSmoothed(smoothed));
        ofPopMatrix();
    }
    
    ofPopMatrix();
}


void ofApp::drawPolyline(ofPolyline polyline) {
    ofSetColor(255, 0, 255);
    polyline.draw();
    
    vector<ofPoint> &vertices = polyline.getVertices();
    int size = vertices.size();
    // １ポイントごと
    for (int i = 0; i < size; i++) {
        ofSetColor(255);
        ofPoint point = vertices.at(i);
        ofVec3f normal = polyline.getNormalAtIndex(i);
        normal *= 10;
        ofCircle(point.x, point.y, 2);
        ofSetColor(0, 255, 255);
        ofLine(point.x, point.y, point.x + normal.x, point.y + normal.y);
    }
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
