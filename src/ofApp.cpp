#include "ofApp.h"

/* Code used from OF example: 02_simpleVertexDisplacement
This program models a lifeform that grows and shrinks in space but gets scared when the user gets to close. */

void ofApp::setup(){

    shader.load("shadersES2/shader");
    ofEnableSmoothing();
    ofBackground(0);
    pointCounter = 0;
    startTime = ofGetElapsedTimeMillis();
    dragTime = ofGetElapsedTimeMillis();
    colorTime = ofGetElapsedTimeMillis();
    entered = false;
    start = true;
    rStarter = 0;
    ofNoFill();
    colorGrad = 0.5;
    leftDir = true;
}

void ofApp::draw(){
    if (entered) {
        delPoints();
    }
    else {
        // make sure color shifts gradially
        if (colorTime + 100 < ofGetElapsedTimeMillis()) {
            if (leftDir && colorGrad < 0.95) {
                colorGrad += 0.05;
            }
            else if (leftDir && colorGrad >= 0.95) {
                colorGrad -= 0.05;
                leftDir = false;
            }
            else if (!leftDir && colorGrad > 0.05) {
                colorGrad -= 0.05;
            }
            else if (!leftDir && colorGrad <= 0.05) {
                colorGrad += 0.05;
                leftDir = true;
            }
            colorTime = ofGetElapsedTimeMillis();
        }
            
        ofColor colorLeft = ofColor::magenta;
        ofColor colorRight = ofColor::cyan;
        ofColor colorMix = colorLeft.getLerped(colorRight, colorGrad);
        ofSetColor(colorMix);

        shader.begin();
        shader.setUniform1f("time", ofGetElapsedTimef());
        shader.end();
        
        pointManager();
    }
    life4m.draw();
}

// delete points from the map (shrink)
void ofApp::delPoints() {
    // while mouse is in window delete a point every 10 millisecs
    if (pointCounter > 0 && (dragTime + 10 < ofGetElapsedTimeMillis())) {
        life4m.removePointAtIndex(pointCounter);
        pointCounter--;
        dragTime = ofGetElapsedTimeMillis();
    }
    // reset map if there are no points left
    else if (pointCounter == 0) {
        life4m.reset();
    }
    
    // let lifeform be 'cautious' for a few moves
    rStarter = ofRandom(3,5) + pointCounter;
}

// add points to the map (grow)
void ofApp::addPoints(){
    // add a random point in 3d space to the map
    int tx = ofRandom(100, ofGetWindowWidth() - 100);
    int ty = ofRandom(100, ofGetWindowHeight() - 100);
    int tz = ofRandom(10, 100);
    life4m.addPoint(ofPoint(tx,ty,tz));
    life4m.triangulate();
    pointCounter++;
}

// decide wether a point gets added or deleted or to stay idle (growing)
void ofApp::pointManager(){
    // grow every 100 - 400 millisecs, unless lifeform is still 'cautious' from last visit of the mouse
    // in that case grow every 1000 millisecs
    int growTimer = ofRandom(1,5) * 100;
    
    // rStarter decides how long the lifeform will stay 'cautious'
    if ((start && startTime + growTimer < ofGetElapsedTimeMillis()) || (!start && pointCounter >= rStarter && startTime + growTimer < ofGetElapsedTimeMillis()) || (!start && pointCounter < rStarter && startTime + 1000 < ofGetElapsedTimeMillis())) {
        
        // when the lifeform is still small (< 12 points), it has 60% chance of growing, 20% of staying idle, %20 of shrinking
        // if the lifeform is > 12, it has 60% chance of staying idle, 20% of growing and %20 of shrinking
        int ran = ofRandom(10);
        
        // create first triangle if map is empty
        while (pointCounter < 3) {
            addPoints();
            ran = 0;
        }
        
        if ((pointCounter < 12 && ran > 3)  || (ran > 7 && pointCounter < 100)) {
            addPoints();
        }
        else if(pointCounter > 0 && ((pointCounter < 12  && ran > 1) || (ran < 8 && ran > 5 && pointCounter >= 12))) {
            life4m.removePointAtIndex(pointCounter);
            pointCounter--;
            life4m.triangulate();
        }
        startTime = ofGetElapsedTimeMillis();
    }
}

// be 'scared' when mouse enters the window
void ofApp::mouseEntered(int x, int y){
    entered = true;
    start = false;
    ofFill();
    ofSetColor(255, 255, 255);
}

// return to normal when mouse leaves window
void ofApp::mouseExited(int x, int y){
    entered = false;
    ofNoFill();
    ofSetColor(ofColor::magenta.getLerped(ofColor::cyan, colorGrad));
}
