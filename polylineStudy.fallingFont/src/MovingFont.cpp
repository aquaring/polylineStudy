//
//  MovingFont.cpp
//  polyline_study_0724_002
//
//  Created by 深谷泰士 on 2015/07/24.
//
//

#include "MovingFont.h"

MovingFont::MovingFont() {
    
    noiseRotate = ofRandom(100.f);
    noiseX = ofRandom(100.f);
    noiseY = ofRandom(100.f);
    noiseScale = ofRandom(100.f);
    noiseSpacing = ofRandom(100.f);
    noiseSmoothed = ofRandom(100.f);
    
    increRotate = 0.01;
    increX = 0.0001;
    increY = 0.0001;
    increScale = 0.0001;
    increSpacing = 0.01;
    increSmoothed = 0.1;
    
    isDead = false;
}

void MovingFont::setWord(string keyword, ofTrueTypeFont& ttf) {
    vecTtf = ttf.getStringAsPoints(keyword);
    
    x = ofRandom(ofGetWidth());
    y = -50;
}

void MovingFont::update() {
    noiseRotate += increRotate;
    noiseX += increX;
    noiseY += increY;
    noiseScale += increScale;
    noiseSpacing += increSpacing;
    noiseSmoothed += increSmoothed;
    
    x += ofSignedNoise(noiseX);
    y += 1;
    
    if (y > ofGetHeight() + 50) {
        isDead = true;
    }
}

void MovingFont::draw() {
    ofSetColor(0);
    ofPushMatrix();
    
    ofTranslate(x, y);
    ofRotate(180.f + ofNoise(noiseRotate)*360.f);
    // 一文字ごと
    for (vector<ofTTFCharacter>::iterator it = vecTtf.begin(); it < vecTtf.end(); it++) {
        // 線ごと
        vector<ofPolyline> &outline = it->getOutline();
        for (vector<ofPolyline>::iterator oit = outline.begin(); oit < outline.end(); oit++) {
            ofPolyline polyline = oit->getResampledBySpacing(10.f*ofNoise(noiseSpacing)).getSmoothed(15.f*ofNoise(noiseSmoothed));
            polyline.draw();
            polyline = oit->getResampledBySpacing(20.f*ofNoise(noiseSpacing)).getSmoothed(1 + 5.f*ofNoise(noiseSmoothed));
            fillPolyline(polyline);
            polyline.draw();
            polyline = oit->getResampledBySpacing(10.f*ofNoise(noiseSpacing)).getSmoothed(1 + 3.f*ofNoise(noiseSmoothed));
            polyline.draw();
            //fillPolyline(polyline);
        }
    }
    
    ofPopMatrix();
}

void MovingFont::fillPolyline(ofPolyline& polyline) {
    ofPath path;
    path.setHexColor(0x333333);
    path.setPolyWindingMode(OF_POLY_WINDING_NONZERO);
    vector<ofPoint> &vertices = polyline.getVertices();
    int size = vertices.size();
    
    for (int i = 0; i < size; i++) {
        if (i == 0) {
            path.moveTo(vertices[i].x, vertices[i].y);
        } else {
            path.lineTo(vertices[i].x, vertices[i].y);
        }
    }
    path.close();
    path.draw();
    
}

