#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxGui.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		ofxKinect kinect;
		ofxCvGrayscaleImage kinectCv;
		ofxCvContourFinder blobDetector;

		struct {
			ofxPanel gui;
			ofParameter<int> nearClip;
			ofParameter<int> farClip;
			ofParameter<int> blur;
			ofParameter<int> minBlobSize;
			ofParameter<int> maxBlobSize;
			ofParameter<float> maxDistance;

		} depthSettings;


		bool voices[8] = {false};
		unsigned int voiceNumber;
		struct soundBlob {
			soundBlob(ofVec2f pos, int area, double value, unsigned int voice) 
				: pos(pos), area(area), value(value), voice(voice) {}; 
			
			ofVec2f pos;
			int area;
			double value;
			unsigned int voice;
		};

		void updateBlobs();
		int getBlobAtPosition(vector<soundBlob> *blobs, ofVec2f pos);

		vector<soundBlob> cameraBlobs, soundBlobs;
};
