//
//  HTTP.cpp
//  AngelaDavies
//
//  Created by David Haylock on 30/04/2018.
//

#include "HTTP.h"

//--------------------------------------------------------------
void HTTP::setup(string url, string secret,string where) {
	this->url = url;
	this->secret = secret;
	this->where = where;
	
	ofAddListener(httpUtils.newResponseEvent, this, &HTTP::responseFromServer);
	httpUtils.setMaxRetries(1);
	httpUtils.start();
	
	// Hello World / Server
	post(ON,1);
}

//--------------------------------------------------------------
void HTTP::post(TYPE t,float value) {
	
	switch (t) {
		case ON: {
			// We are Logging to the Server
			ofxHttpForm formIn;
			formIn.action = url;
			formIn.method = OFX_HTTP_POST;
			formIn.addFormField("where", where);
			formIn.addFormField("when", ofGetTimestampString("%Y-%m-%d-%H-%M-%S"));
			formIn.addFormField("secret", secret);
			formIn.addFormField("event","On");
			httpUtils.addForm(formIn);
		}
			break;
		case OFF: {
			// We are Logging to the Server
			ofxHttpForm formIn;
			formIn.action = url;
			formIn.method = OFX_HTTP_POST;
			formIn.addFormField("where", where);
			formIn.addFormField("when", ofGetTimestampString("%Y-%m-%d-%H-%M-%S"));
			formIn.addFormField("secret", secret);
			formIn.addFormField("event","Off");
			httpUtils.addForm(formIn);
		}
			break;
		case LOG: {
			// We are Logging to the Server
			ofxHttpForm formIn;
			formIn.action = url;
			formIn.method = OFX_HTTP_POST;
			formIn.addFormField("where", where);
			formIn.addFormField("when", ofGetTimestampString("%Y-%m-%d-%H-%M-%S"));
			formIn.addFormField("volume", ofToString(value));
			formIn.addFormField("secret", secret);
			formIn.addFormField("event","Log");
			httpUtils.addForm(formIn);
		}
			break;
		case ACTIVATED: {
			// We are Logging to the Server
			ofxHttpForm formIn;
			formIn.action = url;
			formIn.method = OFX_HTTP_POST;
			formIn.addFormField("where", where);
			formIn.addFormField("when", ofGetTimestampString("%Y-%m-%d-%H-%M-%S"));
			formIn.addFormField("volume", ofToString(value));
			formIn.addFormField("secret", secret);
			formIn.addFormField("event","Activated");
			httpUtils.addForm(formIn);
		}
			break;
		default: break;
	}
}

//--------------------------------------------------------------
void HTTP::responseFromServer(ofxHttpResponse &response) {
//	ADMessage("HTTP", "Received");
	cout << response.status << endl;
	cout << response.responseBody << endl;
}

//--------------------------------------------------------------
void HTTP::exit() {
	httpUtils.stop();
}
