#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	depthSettings.gui.setup("Depth Settings");
	depthSettings.gui.add(depthSettings.nearClip.set("Near Clip", 640, 500, 4000));
	depthSettings.gui.add(depthSettings.farClip.set("Far Clip", 1620, 500, 4000));
	depthSettings.gui.add(depthSettings.blur.set("Blur", 10, 1, 50));
	depthSettings.gui.add(depthSettings.minBlobSize.set("Min Blob Size", 2000, 0, 25000));
	depthSettings.gui.add(depthSettings.maxBlobSize.set("Max Blob Size", 35000, 0, 50000));




	kinect.setRegistration(false);
	kinect.setUseTexture(false);
	kinect.init(false, false);
	kinect.open();


}

//--------------------------------------------------------------
void ofApp::update(){
	kinect.setDepthClipping(depthSettings.nearClip, depthSettings.farClip);

	kinect.update();

	if(kinect.isFrameNewDepth() ) {
		ofPixels filterTable;
		filterTable.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height, 1);
		
		int tableSize = kinect.width * kinect.height;
		for(int i = 0; i < tableSize; i++) {
			filterTable[i] = filterTable[i] == 255 ? 0 : filterTable[i];
		}

		
		kinectCv.setFromPixels(filterTable);
		kinectCv.blur(depthSettings.blur * 2 - 1);

		blobDetector.findContours(kinectCv, depthSettings.minBlobSize, depthSettings.maxBlobSize, 4, false, false);

		cameraBlobs.clear();	
		for(int i = 0; i < blobDetector.nBlobs; i++) {
			ofxCvBlob *thisBlob = &blobDetector.blobs[i];
			cameraBlobs.push_back(soundBlob(thisBlob->centroid.x, thisBlob->centroid.y, 0, 0.0));
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(48);
	//kinect.drawDepth(0, 0);
	kinectCv.draw(0, 0);
	
	blobDetector.draw();	
	
	for(unsigned int i = 0; i < cameraBlobs.size(); i++) {
		ofPushStyle();
		ofSetColor(128, 0, 0);
		ofCircle(cameraBlobs[i].x, cameraBlobs[i].y, 20);
		ofPopStyle();
	}	
	
	
	
	depthSettings.gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
