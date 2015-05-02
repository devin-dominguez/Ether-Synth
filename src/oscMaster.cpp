#include "oscMaster.h"

void OscMaster::setup() {
	oscOut.setup("localhost", 6666);
	
	gui.setup("Synth Settings");
	gui.setPosition(650, 160);
	gui.add(cont.set("Continuous Pitch", true));
	gui.add(steps.set("Scale Steps", 15, 1, 64));
	gui.add(scale.set("Scale", 0, 0, 2));
	gui.add(tonic.set("Tonic", 64, 32, 256));
	gui.add(drone.set("Drone Level", .75, 0, 1));
	lastMode = false;
	lastScale = -1;
	lastTonic = -1;
}

//--------------------------------------------------------------
void OscMaster::update(vector<BlobMaster::soundBlob> blobs, vector<BlobMaster::soundEvent> events) {

	for(unsigned int i = 0; i < events.size(); i++) {
		addMessage(events[i].voice, "spawn", events[i].type); 
	}


	addMessage(-1, "drone", drone);
	
	if(cont) {
		continuous(blobs, events);
		if(!lastMode) {
			lastMode = true;
			addMessage(-1, "mode", 0);
		}	
	}
	else {
		discreet(blobs, events);
		if(lastMode) {
			lastMode = false;
			addMessage(-1, "mode", 1);
		}
	}

	if(scale != lastScale) {
		lastScale = scale;
		addMessage(-1, "scale", scale);
	}

	if(tonic != lastTonic) {
		lastTonic = tonic;
		addMessage(-1, "tonic", tonic);
	}


	//flush messages
	for(unsigned int i = 0; i < oscQueue.size(); i++) {
		oscOut.sendMessage(oscQueue[i]);
	}
	oscQueue.clear();

}

//--------------------------------------------------------------
void OscMaster::draw() {
	if(!cont) {
		for(int i = 0; i < steps; i++) {
			ofPushStyle();
			ofNoFill();
			for(unsigned int h = 0; h < hilight.size(); h++) {
				if(i == hilight[h]) {
					ofFill();
				}
			}
			ofRect(640 * i / steps, 0, 640 / steps, 480);
			ofPopStyle();
		}
	}

	hilight.clear();

	gui.draw();
}

//--------------------------------------------------------------
void OscMaster::addMessage(int voice, string address, double value) {
	ofxOscMessage msg;
	msg.setAddress("/voice" + ofToString(voice) + "/" + address + "/");
	msg.addFloatArg(value);
	oscQueue.push_back(msg);

}


//--------------------------------------------------------------
void OscMaster::continuous(vector<BlobMaster::soundBlob> blobs, vector<BlobMaster::soundEvent> events) {

	for(unsigned int i = 0; i < blobs.size(); i++) {
		addMessage(blobs[i].voice, "x", blobs[i].pos.x / 640.0);
		addMessage(blobs[i].voice, "y", blobs[i].pos.y / 480.0);
		addMessage(blobs[i].voice, "z", blobs[i].z / 255.0);
		addMessage(blobs[i].voice, "area", blobs[i].area / (640.0 * 480.0));
	}
}

//--------------------------------------------------------------


void OscMaster::discreet(vector<BlobMaster::soundBlob> blobs, vector<BlobMaster::soundEvent> events) {

	for(unsigned int i = 0; i < blobs.size(); i++) {
		addMessage(blobs[i].voice, "x", (int)(steps * blobs[i].pos.x / 640.0));
		addMessage(blobs[i].voice, "y", blobs[i].pos.y / 480.0);
		addMessage(blobs[i].voice, "z", blobs[i].z / 255.0);
		addMessage(blobs[i].voice, "area", blobs[i].area / (640.0 * 480.0));
		
		hilight.push_back((int)(steps * blobs[i].pos.x / 640.0));
	}
}
