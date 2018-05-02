#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::exit() {
	
	staticTimer.stop();
	rampTimer.stop();
	ofRemoveListener(staticTimer.timerStarted, this, &ofApp::staticTimerStarted);
	ofRemoveListener(rampTimer.timerStarted, this, &ofApp::rampTimerStarted);
	
	ofRemoveListener(staticTimer.timerFinished, this, &ofApp::staticTimerFinished);
	ofRemoveListener(rampTimer.timerFinished, this, &ofApp::rampTimerStarted);
	sculptureController.exit();
	
	if(bCanLog || bCanPost)
		ofRemoveListener(logTimer.timerFinished, this, &ofApp::logTimerFinished);
	
	if(bCanLog)
		Logger::instance().close();
	
	if(bCanPost) {
		HTTP::instance().post(OFF);
		HTTP::instance().exit();
	}
}

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetDataPathRoot("../Resources/data/");
	
	// Load the Config File
	ofxJSONElement config;
	if(!config.open(ofToDataPath("config.json"))) {
		ADMessage("Load", "Failed to load due to missing or corrupt config file");
		return;
	}
	else {
		where = config["where"].asString();
		threshold = config["threshold"].asInt();
		deviceName = config["serialname"].asString();
		baudRate = config["baudrate"].asInt();
		url = config["url"].asString();
		secret = config["secret"].asString();
		staticTimerLength = config["statictimerlength"].asInt();
		rampTimerLength = config["ramptimerlength"].asInt();
		logTimerLength = config["logtimerlength"].asInt();
		bCanLog = config["log"].asBool();
		bCanPost = config["post"].asBool();
	}
	
	// Set the Variables for the Sculpture Control
	motorPower = 0;
	LEDPower = 0;
	
	// First Load
	bFirst = false;

	// Set the Current State
	currentState = STATE::RAMP_IN;
	
	// Load Some Font
	if(content == nullptr) {
		content = new ofTrueTypeFont();
		if(content->load(ofToDataPath("Fonts/Verdana.ttf"), 15) ) {
			ADMessage("Font", "Loaded");
		}
		else {
			ADMessage("Font", "Not Loaded");
		}
	}
	
	// Init the Audio Manager
	audioManager.setup();
	sculptureController.setup(deviceName,baudRate);
	
	// Setup the Timers
	staticTimer.setup((1000*staticTimerLength),"Static",false);
	rampTimer.setup((1000*rampTimerLength),"Ramp",false);
	
	if(bCanPost)
		HTTP::instance().setup(url, secret, where);
	
	if(bCanLog || bCanPost) {
		logTimer.setup((1000*logTimerLength), "Log", true);
		ofAddListener(logTimer.timerFinished, this, &ofApp::logTimerFinished);
		logTimer.start();
	}
	
	// Ensure the transition timer waits for the start up loop
	staticTimer.start();
	rampTimer.stop();

	// Add the Listeners
	ofAddListener(staticTimer.timerStarted, this, &ofApp::staticTimerStarted);
	ofAddListener(rampTimer.timerStarted, this, &ofApp::rampTimerStarted);
	ofAddListener(staticTimer.timerFinished, this, &ofApp::staticTimerFinished);
	ofAddListener(rampTimer.timerFinished, this, &ofApp::rampTimerFinished);
}

//--------------------------------------------------------------
void ofApp::update(){
	
	if (logs.size() > 10) {
		logs.pop_back();
	}
	
	audioManager.update();
	
	switch (currentState) {
		case NORMAL:
		{
			if(bFirst && audioManager.getSmoothedVolume() > 25 && rampTimer.hasTimerFinished()) {
				rampTimer.start();
				if(bCanPost)
					HTTP::instance().post(ACTIVATED,audioManager.getSmoothedVolume());
			}
		}
			break;
		case LOUD: break;
		case RAMP_IN:
		{
				motorPower = ofMap(rampTimer.getTimeLeft(),rampTimer.getTimerLength(),0,0,255);
				
				sculptureController.setSpeed(ofMap(rampTimer.getTimeLeft(),rampTimer.getTimerLength(),0,0,2.8));
				
				if (motorPower >= 255) {
					motorPower = 255;
					currentState = NORMAL;
				}
		}
			break;
		case RAMP_OUT:
			sculptureController.setSpeed(ofMap(rampTimer.getTimeLeft(),rampTimer.getTimerLength(),0,2.8,0));
			break;
		default:
			break;
	}
}

//--------------------------------------------------------------
void ofApp::drawTimers() {
	char t[100];
	sprintf(t,"Ramp Timer: %.0f / %.0f",rampTimer.getTimeLeft(),rampTimer.getTimerLength());
	ofDrawBitmapString(t, 10, 465);
	char s[100];
	sprintf(s,"Static Timer: %.0f / %.0f",staticTimer.getTimeLeft(),staticTimer.getTimerLength());
	ofDrawBitmapString(s, 10, 485);
	
	for (int i = 0; i < logs.size(); i++) {
		ofDrawBitmapString(logs[i], 10, 515+(i*15));
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	
#ifndef TARGET_RASPBERRY_PI
	ofSetWindowTitle("Angela Davies Bird");
#endif

	ofSetColor(255,255,255);
	sculptureController.draw();
	audioManager.draw();
	
	drawTimers();
	
	string ss;
	switch (currentState) {
		case NORMAL: {
			ofSetColor(46, 204, 113);
			ss = "Normal State";
		}
			break;
		case LOUD: {
			ofSetColor(231, 76, 60);
			ss = "Loud State";
		}
			break;
		case RAMP_IN: {
			ofSetColor(155, 89, 182);
			ss = "Ramp In State";
		}
			break;
		case RAMP_OUT: {
			ofSetColor(230, 126, 34);
			ss = "Ramp Out Mode";
		}
			break;
		default:
			break;
	}
	content->drawString(ss, 10, 450);
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	cout << msg.message << endl;
	logs.push_front(msg.message);
}

//--------------------------------------------------------------
void ofApp::staticTimerStarted(std::string &val) {
//	ADMessage("Timer", "Static Timer Started");
}

//--------------------------------------------------------------
void ofApp::staticTimerFinished(std::string &val) {
	ADMessage("State Machine", "Transitioning to Normal Mode");
	currentState = RAMP_IN;
	rampTimer.start();
	if (!bFirst)
		bFirst = true;
}

//--------------------------------------------------------------
void ofApp::rampTimerStarted(std::string &val) {
	switch (currentState) {
		case NORMAL:
		{
			currentState = RAMP_OUT;
			ADMessage("State Machine", "Starting to Ramp Out");
		}
			break;
		case LOUD:
		{
			currentState = RAMP_IN;
			ADMessage("State Machine", "Starting to Ramp In");
		}
			break;
		default: break;
	}
}

//--------------------------------------------------------------
void ofApp::rampTimerFinished(std::string &val) {
	switch (currentState) {
		case RAMP_OUT:
		{
			currentState = LOUD;
			staticTimer.start();
			ADMessage("State Machine", "Loud Mode");
		}
			break;
		case RAMP_IN: {
			currentState = NORMAL;
			ADMessage("State Machine", "Normal Mode");
		}
			break;
		default: break;
	}
}

//--------------------------------------------------------------
void ofApp::logTimerFinished(std::string &val) {
	if (bCanLog)
		Logger::instance().addLog(audioManager.getSmoothedVolume());
	
	if (bCanPost)
		HTTP::instance().post(LOG,audioManager.getSmoothedVolume());
}
