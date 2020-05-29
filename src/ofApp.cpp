#include "ofApp.h"

int pointCounter, rStarter;
int dragTime;
bool entered, start;

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableSmoothing();
    ofBackground(0);
    pointCounter = 0;
    startTime = ofGetElapsedTimeMillis();
    dragTime = ofGetElapsedTimeMillis();
    entered = false;
    start = true;
    rStarter = 0;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofNoFill();
    //life4m.triangleMesh;
    
    life4m.draw();
    if (entered)
        delPoints();
    else
        addPoints();
    //ofDrawBitmapString("'r' to reset", ofPoint(10,20));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'r'){
        life4m.reset();
    }
    if(key == 's'){
        std::cout << "pointC: " << pointCounter << endl;
    }
    if(key == 't'){
        life4m.removePointAtIndex(pointCounter);
        pointCounter--;
        life4m.triangulate();
    }
}

void ofApp::delPoints() {
    if (pointCounter > 0 && (dragTime + 10 < ofGetElapsedTimeMillis())) {
        std::cout << "entered pc: " << pointCounter << endl;
        life4m.removePointAtIndex(pointCounter);
        pointCounter--;
        dragTime = ofGetElapsedTimeMillis();
    }
    else if (pointCounter == 0) {
        life4m.reset();
    }
}

//
void ofApp::addPoints(){
    if ((start && startTime + 200 < ofGetElapsedTimeMillis()) || (!start && pointCounter >= rStarter && startTime + 200 < ofGetElapsedTimef()) || (!start && pointCounter < rStarter && startTime + 1000 < ofGetElapsedTimeMillis())) {
        int ran = ofRandom(10);
        std::cout << "inadd ran " << ran << endl;
        // 0 is niks doen
        if ((pointCounter < 15 && ran > 3)  || (ran > 6 && pointCounter < 100)) {
            int tx = ofRandom(100, ofGetWindowWidth() - 100);
            int ty = ofRandom(100, ofGetWindowHeight() - 100);
            int tz = ofRandom(10, 100);
            life4m.addPoint(ofPoint(tx,ty,tz));
            //points[pointCounter] = {tx, ty};
            life4m.triangulate();
            pointCounter++;
        }
        else if(pointCounter > 0 && ((pointCounter < 15  && ran > 1) || (ran < 7 && ran > 3 && pointCounter >= 15))) {
            life4m.removePointAtIndex(pointCounter);
            pointCounter--;
            life4m.triangulate();
        }
        startTime = ofGetElapsedTimeMillis();
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
void ofApp::mouseEntered(int x, int y){
    entered = true;
    start = false;
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    entered = false;
    rStarter = ofRandom(2,6);
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
