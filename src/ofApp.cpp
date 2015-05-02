#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	blobMaster.setup();
	oscMaster.setup();

}

//--------------------------------------------------------------
void ofApp::update(){
	
	blobMaster.update();
	oscMaster.update(blobMaster.getBlobs(), blobMaster.getEvents());


}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(48);
	blobMaster.draw();
	oscMaster.draw();
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
