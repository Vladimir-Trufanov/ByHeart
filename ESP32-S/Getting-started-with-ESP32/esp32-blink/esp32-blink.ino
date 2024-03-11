/*
  esp32-blink.ino                2024.02.03
  -----------------------------------------
  Rewrite of classic Blink sketch for ESP32
  Use LED on GPIO2
   
  DroneBot Workshop 2020
  https://dronebotworkshop.com
*/
 
// LED on GPIO2
int ledPin = 2;
 
void setup()
{
    // Set LED as output
    pinMode(ledPin, OUTPUT);
    
    // Serial monitor setup
    Serial.begin(115200);
}
 
void loop()
{
    delay(1000);
    Serial.print("Привет");
    digitalWrite(ledPin, HIGH);
    delay(500);
    Serial.println(" мир!");
    digitalWrite(ledPin, LOW);
    delay(500);
}
