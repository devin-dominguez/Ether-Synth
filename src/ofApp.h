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

		} depthSettings;

		struct soundBlob {
			soundBlob(int x, int y, int area, double value) : x(x), y(y), area(area), value(value) {}; 
			int x;
			int y;
			int area;
			double value;
		};

		vector<soundBlob> cameraBlobs;
};
