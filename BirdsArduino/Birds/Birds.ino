#include <Wire.h>
#include <Adafruit_MotorShield.h>

char receivedChars[] = "F,0.0;";
char messageFromPC[32] = {0};
float floatFromPC = 0.0;
String inData;

#define LED_BANK_1_PIN 10
#define LED_BANK_2_PIN 11
#define MAX_MOTOR_SPEED 255

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);

//-----------------------------------------------------
// * Setup 
//-----------------------------------------------------
void setup() {
     //Set Serial Baud
     Serial.begin(115200); 
     Serial.println("Birds Connected");
     
     AFMS.begin();
     myMotor->run(FORWARD);
     myMotor->run(RELEASE);
}

//-----------------------------------------------------
// * Main Loop
//-----------------------------------------------------
void loop() {

  while (Serial.available() > 0) {
        char received = Serial.read();
        inData += received; 
        
        if (received == '\n' || received == "\r")
        {
            parseData();
            
            if (messageFromPC[0] == 'f'){
                myMotor->run(FORWARD);
                myMotor->setSpeed(constrain(int(floatFromPC),0,MAX_MOTOR_SPEED));
				        analogWrite(LED_BANK_1_PIN,int(floatFromPC));
				        analogWrite(LED_BANK_2_PIN,int(floatFromPC));
                Serial.println("O");
            }
            else if (messageFromPC[0] == 'b'){
                myMotor->run(BACKWARD);
                myMotor->setSpeed(constrain(int(floatFromPC),0,MAX_MOTOR_SPEED));
            }
            else if (messageFromPC[0] == 's'){
        				analogWrite(LED_BANK_1_PIN,0);
        				analogWrite(LED_BANK_2_PIN,0);
                myMotor->run(RELEASE);
            } else {
              
            }

            inData = ""; // Clear recieved buffer
        }
    }
}

//-----------------------------------------------------
// * Parse the incoming data
//-----------------------------------------------------
void parseData() {
  
  // this is used by strtok() as an index
  char * strtokIndx; 
  inData.toCharArray(receivedChars, inData.length());

  // get the first part - the string
  strtokIndx = strtok(receivedChars,",");
  
  // copy it to messageFromPC
  strcpy(messageFromPC, strtokIndx);
  strtokIndx = strtok(NULL, ";");
  
  // Convert to float 
  floatFromPC = atof(strtokIndx);
}
