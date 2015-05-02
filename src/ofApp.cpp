#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	voiceNumber = 0;

	depthSettings.gui.setup("Depth Settings");
	depthSettings.gui.add(depthSettings.nearClip.set("Near Clip", 640, 500, 4000));
	depthSettings.gui.add(depthSettings.farClip.set("Far Clip", 1620, 500, 4000));
	depthSettings.gui.add(depthSettings.blur.set("Blur", 10, 1, 50));
	depthSettings.gui.add(depthSettings.minBlobSize.set("Min Blob Size", 2000, 0, 25000));
	depthSettings.gui.add(depthSettings.maxBlobSize.set("Max Blob Size", 35000, 0, 50000));
	depthSettings.gui.add(depthSettings.maxDistance.set("Max Distance", 50, 0, 150));




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
			ofRectangle rect = thisBlob->boundingRect;
			double area = rect.getArea();
			double value = 0.0;
			for(int y = rect.getTop(); y < rect.getBottom(); y++) {
				for(int x = rect.getLeft(); x < rect.getRight(); x++) {
					value += kinectCv.getPixels()[y * (int)kinectCv.getWidth() + x];
				}
			}
			value /= area;

			cameraBlobs.push_back(soundBlob(thisBlob->centroid, area, value, 0));
		}

		updateBlobs();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(48);
	kinectCv.draw(0, 0);
	
	blobDetector.draw();	
	
	for(unsigned int i = 0; i < soundBlobs.size(); i++) {
		ofPushStyle();
		ofSetColor(128, 0, 0);
		ofCircle(soundBlobs[i].pos, 20);
		ofSetColor(0, 128, 0);
		ofDrawBitmapString(ofToString(soundBlobs[i].voice) + 
				"\n" + 
				ofToString(soundBlobs[i].area) +
				"\n" +
				ofToString(soundBlobs[i].value),	
			soundBlobs[i].pos);
		
		ofPopStyle();
	}	
	
	
	
	depthSettings.gui.draw();
}


//--------------------------------------------------------------
void ofApp::updateBlobs() {
	//add blobs to cam
	for(unsigned int i = 0; i < cameraBlobs.size(); i++) {
		int blobId = getBlobAtPosition(&soundBlobs, cameraBlobs[i].pos);
		if(blobId >= 0) {
			soundBlobs[blobId].pos = cameraBlobs[i].pos;
			soundBlobs[blobId].area = cameraBlobs[i].area;
			soundBlobs[blobId].value = cameraBlobs[i].value;
			//cout << "updated blob #" << ofToString(blobId) << endl;
		}
		else {
			soundBlob newBlob = cameraBlobs[i];
			unsigned int n = 0;
			while(voices[n]) {
				n++;
			}
			newBlob.voice = n;
			voices[n] = true;

			soundBlobs.push_back(newBlob);
			cout << "added blob #" << ofToString(newBlob.voice) <<endl;
				
		}
	}

	//remove blobs	
	for(unsigned int i = 0; i < soundBlobs.size(); i++) {
		int blobId = getBlobAtPosition(&cameraBlobs, soundBlobs[i].pos); 
		if(blobId < 0) {
			cout << "removed blob #" << ofToString(soundBlobs[i].voice) << endl;
			voices[soundBlobs[i].voice] = false;
			soundBlobs.erase(soundBlobs.begin() + i);
		}
	
	}
}


//--------------------------------------------------------------
int ofApp::getBlobAtPosition(vector<soundBlob> *blobs, ofVec2f pos) {
	for(unsigned int i = 0; i < blobs->size(); i++) {
		if( (*blobs)[i].pos.distance(pos) <= depthSettings.maxDistance ) {
			return i;
		}
	}
	return -1;
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
