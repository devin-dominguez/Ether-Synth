#include "blobMaster.h"

void BlobMaster::setup() {

	voiceNumber = 0;

	for(int i = 0; i < 8; i++) {
		voices[8] = false;
	}

	gui.setup("Depth Settings");
	gui.add(nearClip.set("Near Clip", 640, 500, 4000));
	gui.add(farClip.set("Far Clip", 1620, 500, 4000));
	gui.add(blur.set("Blur", 10, 1, 50));
	gui.add(minBlobSize.set("Min Blob Size", 2000, 0, 25000));
	gui.add(maxBlobSize.set("Max Blob Size", 35000, 0, 50000));
	gui.add(maxDistance.set("Max Distance", 50, 0, 150));

	kinect.setRegistration(false);
	kinect.setUseTexture(false);
	kinect.init(false, false);
	kinect.open();

}

//--------------------------------------------------------------
void BlobMaster::update() {
	kinect.setDepthClipping(nearClip, farClip);

	kinect.update();

	if(kinect.isFrameNewDepth() ) {
		ofPixels filterTable;
		filterTable.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height, 1);
		
		int tableSize = kinect.width * kinect.height;
		for(int i = 0; i < tableSize; i++) {
			filterTable[i] = filterTable[i] == 255 ? 0 : filterTable[i];
		}

		
		kinectCv.setFromPixels(filterTable);
		kinectCv.blur(blur * 2 - 1);

		blobDetector.findContours(kinectCv, minBlobSize, maxBlobSize, 4, false, false);

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

		soundEvents.clear();
		updateBlobs();
	}


}

//--------------------------------------------------------------
void BlobMaster::draw() {

	kinectCv.draw(0, 0);
	
//	blobDetector.draw();	
	
	for(unsigned int i = 0; i < soundBlobs.size(); i++) {
		ofPushStyle();
		ofSetColor(128, 0, 0);
		ofCircle(soundBlobs[i].pos, 50 * (1 - soundBlobs[i].value / 255.0 ));
		ofSetColor(0, 128, 0);
		ofDrawBitmapString(ofToString(soundBlobs[i].voice) + 
				"\n" + 
				ofToString(soundBlobs[i].area) +
				"\n" +
				ofToString(soundBlobs[i].value),	
			soundBlobs[i].pos);
		
		ofPopStyle();
	}	
	
	
	if(drawGui) {	
		gui.draw();
	}
}

//--------------------------------------------------------------
void BlobMaster::toggleGui() {
	drawGui = !drawGui;
}
//--------------------------------------------------------------
void BlobMaster::updateBlobs() {
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
			soundEvents.push_back(soundEvent(newBlob.voice, 1));			
		}
	}

	//remove blobs	
	for(unsigned int i = 0; i < soundBlobs.size(); i++) {
		int blobId = getBlobAtPosition(&cameraBlobs, soundBlobs[i].pos); 
		if(blobId < 0) {
			cout << "removed blob #" << ofToString(soundBlobs[i].voice) << endl;
			voices[soundBlobs[i].voice] = false;
			soundEvents.push_back(soundEvent(soundBlobs[i].voice, 0));
			soundBlobs.erase(soundBlobs.begin() + i);
		}
	
	}
}


//--------------------------------------------------------------
int BlobMaster::getBlobAtPosition(vector<soundBlob> *blobs, ofVec2f pos) {
	for(unsigned int i = 0; i < blobs->size(); i++) {
		if( (*blobs)[i].pos.distance(pos) <= maxDistance ) {
			return i;
		}
	}
	return -1;
}

vector<BlobMaster::soundBlob> BlobMaster::getBlobs() {
	return soundBlobs;
}

vector<BlobMaster::soundEvent> BlobMaster::getEvents() {
	return soundEvents;
}
