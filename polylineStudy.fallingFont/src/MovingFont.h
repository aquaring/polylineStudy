//
//  MovingFont.h
//  polyline_study_0724_002
//
//  Created by 深谷泰士 on 2015/07/24.
//
//

#ifndef __polyline_study_0724_002__MovingFont__
#define __polyline_study_0724_002__MovingFont__

#include <stdio.h>
#include "ofMain.h"

class MovingFont {
private:

    float noiseRotate, noiseX, noiseY, noiseScale, noiseSpacing, noiseSmoothed;
    
    float x, y;
    
    vector<ofTTFCharacter> vecTtf;
    
    void fillPolyline(ofPolyline& polyline);
    
public:
    float increRotate, increX, increY, increScale, increSpacing, increSmoothed;
    bool isDead;
    
    MovingFont();
    
    void setWord(string keyword, ofTrueTypeFont& ttf);
    
    void update();
    
    void draw();
};
#endif /* defined(__polyline_study_0724_002__MovingFont__) */
