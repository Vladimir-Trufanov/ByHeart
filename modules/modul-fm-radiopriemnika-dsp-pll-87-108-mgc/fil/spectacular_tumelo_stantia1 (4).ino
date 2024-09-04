// C++ code
//
#include <SoftwareSerial.h>

SoftwareSerial serialRX(4,3);

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  serialRX.begin(300);  
  Serial.begin(115200);
}

void loop()
{
  serialRX.available()?digitalWrite(13,1):digitalWrite(13,0);
  // Serial.println(serialRX.available());
  if (serialRX.available())
  {
    char simb=serialRX.read();
    Serial.print(simb);
    delay(1);
  }
}