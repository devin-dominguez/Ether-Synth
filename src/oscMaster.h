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
		int getSynth();
	private:
		ofxOscSender oscOut;	
	
		void continuous(vector<BlobMaster::soundBlob> blobs, vector<BlobMaster::soundEvent> events);
		void discreet(vector<BlobMaster::soundBlob> blobs, vector<BlobMaster::soundEvent> events);

		bool drawGui;
		ofxPanel fmGui, bbGui;
		ofParameter<float> volume;
		ofParameter<bool> synthType;

	//fm
		ofParameter<int> timbre;
		ofParameter<bool> cont;
		ofParameter<int> steps;
		ofParameter<int> scale;
		ofParameter<int> tonic;	
		ofParameter<float> drone;

	//bb
		ofParameter<float> tempo;
		float lastTempo;
	
		void fmSynth(vector<BlobMaster::soundBlob> blobs, vector<BlobMaster::soundEvent> events);
		void bbSynth(vector<BlobMaster::soundBlob> blobs, vector<BlobMaster::soundEvent> events);

		bool lastMode;
		int lastScale;
		int lastTonic;
		int lastTimbre;

		int lastSynth;


		vector<int> hilight;
		vector<ofxOscMessage> oscQueue;

};
