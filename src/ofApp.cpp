#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowShape(880, 500);
	
	ofSetFrameRate(60);
	ofEnableAlphaBlending();

	blobMaster.setup();
	oscMaster.setup();

	fonty.loadFont("Akashi.ttf", 48);
	bgColor = ofColor(0);
	bgTarget = ofColor(48, 16, 0);

	time = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
	
	blobMaster.update();
	oscMaster.update(blobMaster.getBlobs(), blobMaster.getEvents());


}

//--------------------------------------------------------------
void ofApp::draw(){
	switch(oscMaster.getSynth()) {
		case 0:
			bgTarget = ofColor(48, 16, 0);
			break;
		case 1:
			bgTarget = ofColor(72, 72, 96);
			break;
		case 2:
			bgTarget = ofColor(12, 64, 12);
			break;
		case 3:
			bgTarget = ofColor(96, 0, 96);
			break;
		case 4:
			if(time > 15) {
				time = 0;
				bgTarget = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
			}
			else {
				time++;
			}
			break;
	}
	bgColor = bgColor.getLerped(bgTarget, .1);
	ofBackground(bgColor);
	blobMaster.draw();
	oscMaster.draw();
	fonty.drawString("ETHER\nSYNTH", 660, 400);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key) {
		case ' ' :
			blobMaster.toggleGui();
			break;
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
