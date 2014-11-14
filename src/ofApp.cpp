#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    // this uses depth information for occlusion
    // rather than always drawing things on top of each other
    ofEnableDepthTest();
    
    // this sets the camera's distance from the object
    cam.setDistance(100);
    ofSetFrameRate(60);
    
    mParticleController.resetParticles();
    for (int i = 0; i < 200; i++) {
        mParticleController.addParticles(mouseLoc, mouseVel);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    if (mIsPressed) {
//        mouseVel = ofVec2f(ofGetMouseX() - mouseLoc.x, ofGetMouseY() - mouseLoc.y);
        mouseVel = ofVec3f(ofRandom(-2, 2), ofRandom(-2, 2), ofRandom(-2, 2));
        mouseLoc = ofPoint(0, 0, 0);//ofGetMouseX(), ofGetMouseY());
//    for (int i = 0; i < 10; i++) {
        mParticleController.addParticles(mouseLoc, mouseVel);
    }
    
    mParticleController.applyForce(6400, 0.60, 0.90);
    mParticleController.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(30,30,30), ofColor(10,10,10));
    
    cam.begin();    
    mParticleController.draw();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    mIsPressed = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    mIsPressed = false;
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
