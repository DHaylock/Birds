//
//  Logger.h
//  AngelaDavies
//
//  Created by David Haylock on 30/04/2018.
//

#ifndef Logger_h
#define Logger_h

#include "ofMain.h"
#include "ofxCsv.h"
#include <stdio.h>

class Logger {
	public:
	
		static Logger& instance() {
			static Logger* instance_ = new Logger();
			return *instance_;
		}
	
		//--------------------------------------------------------------
		/**
		 Add a Value to the log file

		 @param value value
		 */
		//--------------------------------------------------------------
		void addLog(float value);
	
		//--------------------------------------------------------------
		/**
		 Save the File
		 */
		//--------------------------------------------------------------
		void close();
	
	private:
		ofxCsv logFile;
};


#endif /* Logger_h */
