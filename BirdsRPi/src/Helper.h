//-----------------------------------------------------
/**
 Logging Message System
 
 @param s_Class Class / Manager Message Sent from
 @param s_Message message
 */
//-----------------------------------------------------
#pragma once

#define MAX_VISUAL_MOTOR_SPEED 2.8f
#define MAX_MOTOR_SPEED 255
#include "ofxJSON.h"
#include "Logger.h"
#include "HTTP.h"

template<typename T>
void ADMessage(T s_Class,T s_Message) {
	string msg = string(s_Class) + " | " + string(s_Message);
	ofSendMessage(msg);
}
