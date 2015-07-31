#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxSvg.h"

class ofApp : public ofBaseApp{
    private:
        ofTrueTypeFont ttf;
        ofxSVG svg;
        vector<ofPolyline> svgLines;
    
    ofxUISuperCanvas *gui;
    float spacing;
    float count;
    float smoothed;
    
        void drawPolyline(ofPolyline polyline);
    
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
