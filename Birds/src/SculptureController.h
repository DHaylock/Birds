//
//  MotoSculptureController.h
//  AngelaDavies
//
//  Created by David Haylock on 27/04/2018.
//

#ifndef SculptureController_h
#define SculptureController_h

#include <stdio.h>
#include "ofMain.h"
#include "Helper.h"
enum STATE {
	NORMAL = 0,
	RAMP_IN,
	RAMP_OUT,
	LOUD
};

class SculptureController {
	public:
	
		//--------------------------------------------------------------
		/**
		 Setup the Serial Device

		 @param serialDevice the name of the Serial Device
		 @param baudRate the Baud rate
		 */
		//--------------------------------------------------------------
		void setup(string deviceName,int baudRate);
		void exit();
	
		//--------------------------------------------------------------
		/**
		 Set the Motor Speed

		 @param speed sets the new speed of the motor
		 */
		//--------------------------------------------------------------
		void setSpeed(float speed);
		void addSpeed(float speed);
		void reduceSpeed(float speed);
	
		//--------------------------------------------------------------
		/**
		 Send Serial Data the Arduino
		 */
		//--------------------------------------------------------------
		void sendSerialData();
	
		//--------------------------------------------------------------
		/**
		 Draw a Simulation
		 */
		//--------------------------------------------------------------
		void draw();
	 
	private:
		ofSerial serialDevice;
		float currentAngle = 0;
		float speed = 0.1;
		float motorSpeed = 255;
};


#endif /* SculptureController_h */
