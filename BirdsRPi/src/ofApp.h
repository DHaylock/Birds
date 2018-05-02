#pragma once

#include "ofMain.h"
#include "AudioAnalysis.h"
#include "Timer.h"
#include "SculptureController.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();
	
		void keyPressed(int key);
		void keyReleased(int key);
		void gotMessage(ofMessage msg);
	
		deque <string> logs;
	
		int motorPower;
		int LEDPower;
		bool bFirst;
	private:
		STATE currentState;
		AudioAnalysis audioManager;
		SculptureController sculptureController;
	
		ofTrueTypeFont *content = nullptr;
	
		Timer rampTimer;
		Timer staticTimer;
		Timer logTimer;
	
		void staticTimerStarted(string &val);
		void staticTimerFinished(string &val);
	
		void rampTimerStarted(string &val);
		void rampTimerFinished(string &val);
	
		void logTimerFinished(string &val);
	
		void drawTimers();
	
	protected:
		string where;
		int threshold = 10000;
		string deviceName = "";
		int baudRate = 0;
		string url = "";
		string secret = "";
		int staticTimerLength = 3000;
		int rampTimerLength = 3000;
		int logTimerLength = 5000;
		bool bCanLog = false;
		bool bCanPost = false;
};
