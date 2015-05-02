#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGui.h"
#include "blobMaster.h"

class OscMaster {
	public:
		void setup();
		void update(vector<BlobMaster::soundBlob> blobs, vector<BlobMaster::soundEvent> events);
		void draw();
		void addMessage(string address, double value);

	private:
		ofxOscSender oscOut;	
	
		enum {
			CONTINUOUS,
			DISCREET
		} mode;

		void continuous(vector<BlobMaster::soundBlob> blobs, vector<BlobMaster::soundEvent> events);
		void discreet(vector<BlobMaster::soundBlob> blobs, vector<BlobMaster::soundEvent> events);

		bool drawGui;
		ofxPanel gui;
		vector<ofxOscMessage> oscQueue;
	//	ofParameter<int> nearClip;

};
