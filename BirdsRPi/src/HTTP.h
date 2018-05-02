//
//  HTTP.h
//  AngelaDavies
//
//  Created by David Haylock on 30/04/2018.
//

#ifndef HTTP_h
#define HTTP_h

#include <stdio.h>
#include "ofMain.h"
#include "ofxHttpUtils.h"
#include "Helper.h"

enum TYPE {
	ON = 0,
	OFF,
	LOG,
	ACTIVATED
};

class HTTP {
	public:
		//--------------------------------------------------------------
		static HTTP& instance() {
			static HTTP* instance_ = new HTTP();
			return *instance_;
		}
	
		//--------------------------------------------------------------
		/**
		 Setup the Post System

		 @param url where we send the data
		 @param secret the secret code
		 */
		//--------------------------------------------------------------
		void setup(string url,string secret,string where);
	
		//--------------------------------------------------------------
		/**
		 Send Event

		 @param t what type of event
		 @param value value
		 */
		//--------------------------------------------------------------
		void post(TYPE t,float value = 0);
	
		//--------------------------------------------------------------
		/**
		 Response Tag from the server

		 @param response response data
		 */
		//--------------------------------------------------------------
		void responseFromServer(ofxHttpResponse &response);
	
		//--------------------------------------------------------------
		/**
		 Says on the tin
		 */
		//--------------------------------------------------------------
		void exit();
	
	private:
	
		ofxHttpUtils httpUtils;
		string url;
		string secret;
		string where;
};

#endif /* HTTP_h */
