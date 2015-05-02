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
		void addMessage(int voice, string address, double value);

	private:
		ofxOscSender oscOut;	
	
		void continuous(vector<BlobMaster::soundBlob> blobs, vector<BlobMaster::soundEvent> events);
		void discreet(vector<BlobMaster::soundBlob> blobs, vector<BlobMaster::soundEvent> events);

		bool drawGui;
		ofxPanel gui;
		ofParameter<bool> cont;
		ofParameter<int> steps;
		ofParameter<int> scale;
		ofParameter<int> tonic;	
		ofParameter<float> drone;
		
		bool lastMode;
		int lastScale;
		int lastTonic;


		vector<int> hilight;
		vector<ofxOscMessage> oscQueue;

};
