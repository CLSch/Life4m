#pragma once

#include "ofMain.h"
#include "ofxDelaunay.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void draw();

        void addPoints();
        void delPoints();
        void pointManager();
    
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
    
    ofxDelaunay life4m;
    float startTime, dragTime, colorTime;
    int pointCounter, rStarter;
    bool entered, start, leftDir;
    ofShader shader;
    float colorGrad;
};
