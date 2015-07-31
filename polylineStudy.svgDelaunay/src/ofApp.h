#pragma once

#include "ofMain.h"
#include "ofxSvg.h"
#include "ofxDelaunay.h"

struct svgLine {
    ofPolyline polyline;
    ofPoint basePosition;
    float width;
    float height;
};

class ofApp : public ofBaseApp{
private:
    ofxSVG svg;
    vector<svgLine> svgLines;
    float maxWidth;
    float maxHeight;
    
    int currIndex;
    int morphingCount;
    int maxMorphingCount;
    ofPolyline drawLine;
    
    ofxDelaunay triangulation;
    
    float easingOutBounce(float v);
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
