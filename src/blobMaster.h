#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxGui.h"

class BlobMaster {
	public:
		struct soundBlob {
			soundBlob(ofVec2f pos, double area, double z, unsigned int voice) 
				: pos(pos), area(area), z(z), voice(voice) {}; 
			
			ofVec2f pos;
			double area;
			double z;
			unsigned int voice;
		};

		struct soundEvent {
			soundEvent(int voice, int type) : voice(voice), type(type) {};
			int voice;
			int type;

		};
	
		void setup();
		void update();
		void draw();
		vector<soundBlob> getBlobs();
		vector<soundEvent> getEvents();
		void toggleGui();

	private:

		ofxKinect kinect;
		ofxCvGrayscaleImage kinectCv;
		ofxCvContourFinder blobDetector;

		bool drawGui;
		ofxPanel gui;
		ofParameter<int> nearClip;
		ofParameter<int> farClip;
		ofParameter<int> blur;
		ofParameter<int> minBlobSize;
		ofParameter<int> maxBlobSize;
		ofParameter<float> maxDistance;

		bool voices[8];
		
		unsigned int voiceNumber;

		void updateBlobs();
		int getBlobAtPosition(vector<soundBlob> *blobs, ofVec2f pos);

		ofRectangle viewport;

		vector<soundBlob> cameraBlobs, soundBlobs;
		vector<soundEvent> soundEvents;
};
