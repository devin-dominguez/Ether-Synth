#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	blobMaster.setup();
	oscMaster.setup();

	fonty.loadFont("Akashi.ttf", 96);
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
	fonty.drawString("ETHER\nSYNTH", 150, 640);
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
