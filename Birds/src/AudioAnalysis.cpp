//
//  AudioAnalysis.cpp
//  FFTtoML
//
//  Created by David Haylock on 17/04/2018.
//

#include "AudioAnalysis.h"

//--------------------------------------------------------------
AudioAnalysis::AudioAnalysis() {
	
}

//--------------------------------------------------------------
AudioAnalysis::~AudioAnalysis() {
	
}

//--------------------------------------------------------------
void AudioAnalysis::setup() {
	fft.setup();
	fft.setHistorySize(50);
}

//--------------------------------------------------------------
void AudioAnalysis::update() {
	fft.update();
}

//--------------------------------------------------------------
void AudioAnalysis::draw() {
//	fft.drawBars();
	fft.drawDebug(430,10);
	
	fft.drawHistoryGraph(ofPoint(10,10), MAXSOUND,50); // What we are really interested in
	fft.drawHistoryGraph(ofPoint(220,10), LOW);
	fft.drawHistoryGraph(ofPoint(10,220), MID);
	fft.drawHistoryGraph(ofPoint(220,220), HIGH);
	
	ofPushStyle();
	ofSetColor(ofColor::gray);
	ofNoFill();
	ofDrawRectangle(10, 10, 200, 200);
	ofDrawRectangle(220, 10, 200, 200);
	ofDrawRectangle(10, 220, 200, 200);
	ofDrawRectangle(220, 220, 200, 200);
	
	ofSetColor(ofColor::white);
	ofDrawBitmapString("Max Sound", 15, 25);
	ofDrawBitmapString("Low Sound", 225, 25);
	ofDrawBitmapString("Mid Sound", 15, 235);
	ofDrawBitmapString("High Sound", 225, 235);
	
	ofPopStyle();
}

//--------------------------------------------------------------
float AudioAnalysis::getSmoothedVolume() {
	return fft.getUnScaledLoudestValue();
}

//--------------------------------------------------------------
void AudioAnalysis::close() {

}
