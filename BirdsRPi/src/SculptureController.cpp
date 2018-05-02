//
//  SculptureController.cpp
//  AngelaDavies
//
//  Created by David Haylock on 27/04/2018.
//

#include "SculptureController.h"
#define PRINT_NAME(x) std::cout << #x << " - " << typeid(x).name() << '\n'
#define SSR "f,255;\n"

//--------------------------------------------------------------
void SculptureController::exit() {
	unsigned char stopBuffer[] = { 'f',',','0',';','\n'};
	serialDevice.writeBytes(&stopBuffer[0], sizeof(stopBuffer));
	serialDevice.flush();
	usleep(1000);
	serialDevice.close();
}

//--------------------------------------------------------------
void SculptureController::setup(std::string deviceName, int baudRate) {
	speed = 0.0;
	serialDevice.listDevices();
	serialDevice.setup(deviceName, baudRate);
	
	// make the initial bytes
	unsigned char buffer1[] = { '\n', '\n' };
	unsigned char buffer2[] = { 'f',',','2','5','5',';','\n'};
	
	// Get the Serial Device Ready for action
	serialDevice.writeBytes(&buffer1[0], sizeof(buffer1));
	serialDevice.flush();
	
	serialDevice.writeBytes(&buffer2[0], sizeof(buffer2));
	serialDevice.flush();
}

//--------------------------------------------------------------
void SculptureController::setSpeed(float speed) {
	this->speed = speed;
	sendSerialData();
}
//--------------------------------------------------------------
void SculptureController::addSpeed(float speed) {
	if (this->speed >= MAX_VISUAL_MOTOR_SPEED ) {
		this->speed = MAX_VISUAL_MOTOR_SPEED;
		return;
	}
	
	this->speed += speed;
	
	cout << this->speed << endl;
}

//--------------------------------------------------------------
void SculptureController::sendSerialData() {

	if(serialDevice.isInitialized()) {
		unsigned char buffer[25];
		int n = snprintf((char *)buffer, sizeof(buffer), "f,%u;\n",int(ofMap(this->speed,0.0,2.8f,0,255)));
		serialDevice.writeBytes(&buffer[0], n);
		serialDevice.flush();
	}
}

//--------------------------------------------------------------
void SculptureController::reduceSpeed(float speed) {
	if (this->speed <= 0.0) {
		this->speed = 0.0;
		return;
	}
	
	this->speed += speed;
	cout << this->speed << endl;
}

//--------------------------------------------------------------
void SculptureController::draw() {
	ofPushStyle();
	ofPushMatrix();
	ofTranslate(475, 270);
	ofNoFill();
	ofDrawRectangle(-50, -50, 200, 200);
	ofDrawCircle(125, 50, 10);
	ofDrawCircle(50, 50, 3);
	ofDrawCircle(50, 50, 75);
	ofFill();
	ofDrawBitmapString("Current Rotations " + ofToString(int(currentAngle / 360)), -45, -35);
	ofPushMatrix();
	ofTranslate(50, 50);
	ofPushMatrix();
	currentAngle += this->speed;
	
	ofRotateZ(currentAngle);
	ofTranslate(-50, -50);
	
	ofDrawCircle(125, 50, 10);
	ofPopMatrix();
	ofPopMatrix();
	ofPopMatrix();
	ofPopStyle();
}
