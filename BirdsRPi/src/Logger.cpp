//
//  Logger.cpp
//  AngelaDavies
//
//  Created by David Haylock on 30/04/2018.
//

#include "Logger.h"

//--------------------------------------------------------------
void Logger::addLog(float value) {
	ofxCsvRow row;
	row.setString(0, ofGetTimestampString("%H-%M-%S"));
	row.setFloat(1, value);
	logFile.addRow(row);
	cout << row << endl;
}

//--------------------------------------------------------------
void Logger::close() {
	logFile.save(ofToDataPath("Logs/"+ofGetTimestampString("%Y-%m-%d")+".csv"), true, ",");
}
