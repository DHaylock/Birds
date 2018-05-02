//
//  AudioAnalysis.h
//  FFTtoML
//
//  Created by David Haylock on 17/04/2018.
//

#ifndef AudioAnalysis_h
#define AudioAnalysis_h

#include <stdio.h>
#include "ofxProcessFFT.h"
#include "Helper.h"



class AudioAnalysis : public ofBaseApp {
public:
	
	/**
	 Constructor
	 */
	AudioAnalysis();
	
	/**
	 Deconstructor
	 */
	~AudioAnalysis();
	
	/**
	 Setup the Analysis

	 @param font pass through the font to describe the scene
	 */
	void setup();
	
	/**
	 Update
	 */
	void update();
	
	/**
	 Show me the Waveform
	 */
	void draw();

	/**
	 Get the Smoothed Volume from the Audio Manager

	 @return the smoothed value
	 */
	float getSmoothedVolume();
	
	/**
	 Close the FFT and Microphone
	 */
	void close();
	
	
//	ofEvent<STATE> StateEvent;
	
private:
	ProcessFFT fft;

protected:
	int plotHeight;
	int bufferSize;
	ofTrueTypeFont fnt;
	int binNo;
};

#endif /* AudioAnalysis_h */
