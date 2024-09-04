// C++ code
//
#include <SoftwareSerial.h>

SoftwareSerial serialRX(4,3);

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  serialRX.begin(9600);  
  Serial.begin(9600);
}

void loop()
{
  Serial.println(serialRX.available());
}