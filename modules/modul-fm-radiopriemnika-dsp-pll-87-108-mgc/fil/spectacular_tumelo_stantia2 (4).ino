
// C++ code
//
#include <SoftwareSerial.h>
#define pinButton 8

SoftwareSerial serialTX(5,6);
void setup()
{
  pinMode(pinButton, INPUT_PULLUP);
  Serial.begin(9600);
  serialTX.begin(300);  
}

void loop()
{
  Serial.println  ("Time="+String(millis())+' '+
                 "Status="+String(!digitalRead(8)));
  serialTX.println("Time="+String(millis())+' '+
                 "Status="+String(!digitalRead(8)));
  //delay(10);
}