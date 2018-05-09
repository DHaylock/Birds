//
//  Logger.cpp
//  AngelaDavies
//
//  Created by David Haylock on 30/04/2018.
//

#include "Logger.h"

//--------------------------------------------------------------
void Logger::addLog(float value,string event) {
	ofxCsvRow row;
	row.setString(0, ofGetTimestampString("%H-%M-%S"));
	row.setFloat(1, value);
	row.setString(2, event);
	logFile.addRow(row);
}

//--------------------------------------------------------------
void Logger::close() {
	logFile.save(ofToDataPath("Logs/"+ofGetTimestampString("%Y-%m-%d")+".csv"), true, ",");
}
