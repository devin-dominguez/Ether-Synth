#include "oscMaster.h"

void OscMaster::setup() {
	oscOut.setup("localhost", 6666);
	mode = CONTINUOUS;
}

//--------------------------------------------------------------
void OscMaster::update(vector<BlobMaster::soundBlob> blobs, vector<BlobMaster::soundEvent> events) {

	switch(mode) {
		case CONTINUOUS:
			continuous(blobs, events);	

		break;

		case DISCREET:
			discreet(blobs, events);
		break;

	}	



	//flush messages
	for(unsigned int i = 0; i < oscQueue.size(); i++) {
		oscOut.sendMessage(oscQueue[i]);
	}
	oscQueue.clear();

}

//--------------------------------------------------------------
void OscMaster::draw() {

}

//--------------------------------------------------------------
void OscMaster::addMessage(string address, double value) {
	ofxOscMessage msg;
	msg.setAddress("/" + address + "/");
	msg.addFloatArg(value);
	oscQueue.push_back(msg);

}


//--------------------------------------------------------------
void OscMaster::continuous(vector<BlobMaster::soundBlob> blobs, vector<BlobMaster::soundEvent> events) {
	for(unsigned int i = 0; i < events.size(); i++) {
		cout << events[i].voice << " " << events[i].type << endl;
	}

}

//--------------------------------------------------------------


void OscMaster::discreet(vector<BlobMaster::soundBlob> blobs, vector<BlobMaster::soundEvent> events) {

}
