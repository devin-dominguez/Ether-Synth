#include "oscMaster.h"

void OscMaster::setup() {
	oscOut.setup("localhost", 6666);
	
	fmGui.setup("Synth Settings");
	fmGui.setPosition(660, 160);
	fmGui.add(volume.set("Volume", .5, 0, 1));

	fmGui.add(timbre.set("Synth", 0, 0, 3));
	fmGui.add(cont.set("Continuous Pitch", true));
	fmGui.add(steps.set("Scale Steps", 25, 1, 64));
	fmGui.add(scale.set("Scale", 1, 0, 2));
	fmGui.add(tonic.set("Tonic", 64, 32, 256));
	fmGui.add(drone.set("Drone Level", .75, 0, 1));
	fmGui.add(synthType.set("B-B-B-BONUS MODE!!!", false));
	lastMode = false;
	lastScale = -1;
	lastTonic = -1;
	lastSynth = -1;

	bbGui.setup("Synth Settings");
	bbGui.setPosition(660, 160);

	bbGui.add(volume);
	bbGui.add(tempo.set("Tempo", 176, 100, 200));
	bbGui.add(synthType);
	lastTempo = -1;
	lastTimbre = -1;
}

//--------------------------------------------------------------
void OscMaster::update(vector<BlobMaster::soundBlob> blobs, vector<BlobMaster::soundEvent> events) {

	addMessage(-1, "volume", volume);

	for(unsigned int i = 0; i < events.size(); i++) {
		addMessage(events[i].voice, "spawn", events[i].type); 
	}

	if(synthType != lastSynth) {
		lastSynth = synthType;
		addMessage(-1, "synthType", synthType);
	}


	switch(synthType) {
		case 0 :
			fmSynth(blobs, events);
			addMessage(-1, "fmSynth", 1);
			addMessage(-1, "bbSynth", 0);
			break;
		case 1 :
			bbSynth(blobs, events);
			steps = 8;
			addMessage(-1, "bbSynth", 1);
			addMessage(-1, "fmSynth", 0);
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
	if(!cont || synthType == 1) {
		for(int i = 0; i < steps; i++) {
			ofPushStyle();
			ofNoFill();
			ofSetColor(255);
			for(unsigned int h = 0; h < hilight.size(); h++) {
				if(i == hilight[h]) {
					ofSetColor(255, 255, 255, 128);
					ofFill();
				}
			}
			ofRect(640 * i / steps + 10, 10, 640 / steps, 480);
			ofPopStyle();
		}
	}

	hilight.clear();
	switch(synthType) {
		case 0:
			fmGui.draw();
			break;
		case 1:
			bbGui.draw();
			break;

	}
}

//--------------------------------------------------------------
void OscMaster::addMessage(int voice, string address, double value) {
	ofxOscMessage msg;
	msg.setAddress("/voice" + ofToString(voice) + "/" + address + "/");
	msg.addFloatArg(value);
	oscQueue.push_back(msg);

}

//--------------------------------------------------------------

void OscMaster::fmSynth(vector<BlobMaster::soundBlob> blobs, vector<BlobMaster::soundEvent> events) {
	
	if(timbre != lastTimbre) {
		lastTimbre = timbre;
		addMessage(-1, "timbre", timbre);
	}

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
	addMessage(-1, "drone", drone);
	
	if(scale != lastScale) {
		lastScale = scale;
		addMessage(-1, "scale", scale);
	}

	if(tonic != lastTonic) {
		lastTonic = tonic;
		addMessage(-1, "tonic", tonic);
	}

}

//--------------------------------------------------------------


void OscMaster::bbSynth(vector<BlobMaster::soundBlob> blobs, vector<BlobMaster::soundEvent> events) {
	if(tempo != lastTempo) {
		lastTempo = tempo;
		addMessage(-1, "tempo", tempo);
	}	

	for(int v = 0; v < steps; v++) {
		bool trig = false;
		for( unsigned int i = 0; i < blobs.size(); i++) {
			if(v == (int)(steps * blobs[i].pos.x / 640) ) {
				trig = true;
			}
		hilight.push_back((int)(steps * blobs[i].pos.x / 640.0));
		}
		addMessage(0, "trigger" + ofToString(v), trig ? 1: 0);
	}

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


int OscMaster::getSynth() {
	if(synthType) return 4;
	else return timbre;
}
