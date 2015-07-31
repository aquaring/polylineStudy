#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    ttf.loadFont("apple_gothic.ttf", 72, true, false, true);
}

//--------------------------------------------------------------
void ofApp::update(){
    for (vector<MovingFont>::iterator it = fonts.begin(); it < fonts.end(); it++) {
        it->update();
        if (it->isDead) {
            fonts.erase(it);
            it--;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetWindowTitle(ofToString(fonts.size()) + ", " + ofToString(ofGetFrameRate()) + "fps");
    for (vector<MovingFont>::iterator it = fonts.begin(); it < fonts.end(); it++) {
        it->draw();
        
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    char c = key;
    // A-Z,a-z,0-9,記号
    if (key >= 33 and key <= 122) {
        MovingFont font;
        font.setWord(ofToString(c), ttf);
        
        fonts.push_back(font);
    }
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
