#Ether Synth
Ether Synth is an in-progress Kinect based OSC controller.
Visit [www.dominguezaudio.com](http://www.dominguezaudio.com) for more info.


Ether Synth uses [openFrameworks](http://www.openframeworks.cc) as well as some addons.

The current version of Ether Synth was the grand prize winner of the first ever [HackitFresno](http://www.hackitfresno.com}.

##Use
Generate an oF project with the following addons and copy the contents of the Ether Synth src/ folder to your new project's src/ folder.
+ ofxOsc
+ ofxOpenCv
+ ofxKinect
+ ofxGui

Copy the contents of the EtherSynth data/ folder to your new project's data/ folder.

Load up the pd-patch/main.pd in a version of vanilla PD recent enough to have native OSC support. Check if you have the [oscparse] object. Right now the patch expects a drum loop called amen.wav to be in the same folder as main.pd. This is not provided but any appropriately named drum loop should work pretty well.

Plug in a Kinect and you are good to go.
