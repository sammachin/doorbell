#include "RCSwitch.h"

RCSwitch mySwitch = RCSwitch();

int myValue = 2777576; //ID of My Buttons for Local Notifications
unsigned long lastTime = 0UL;

String publishString;

void setup() {
  Serial.begin(9600);
  pinMode(D0, INPUT); // Data Pin of 433 Receiver
  pinMode(D7, OUTPUT); // LED or Pizo for Local Notifications
  mySwitch.enableReceive(D0);  
}



void loop() {
  //Serial.println("Ready");
  if (mySwitch.available()) {
      if (mySwitch.getReceivedProtocol() == 1) {
		unsigned long now = millis();
		//Publish if >5secs since last event
		if (now-lastTime>5000UL) {
			lastTime = now;
			publishString = String(mySwitch.getReceivedValue());
		    Spark.publish("Doorbell",publishString);
		}   
    }
    //publishString = String(mySwitch.getReceivedValue());
	//Spark.publish("Doorbell",publishString);
	//Flash if its a known ID
	if (mySwitch.getReceivedValue() == myValue){
		flash();
	}
    mySwitch.resetAvailable();
  }
}

void flash(){
    digitalWrite(D7, HIGH);
    delay(200);
    digitalWrite(D7, LOW);
    delay(200);
    digitalWrite(D7, HIGH);
    delay(200);
    digitalWrite(D7, LOW);
    delay(200);
    digitalWrite(D7, HIGH);
    delay(200);
    digitalWrite(D7, LOW);
    delay(200);
}