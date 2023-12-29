// Proverka-kodov-pulta-du.ino
//
// Проверка кодов пульта ДУ
// для версии IRremote 3.5.2

#include "IRremote.h"

int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();                    // инициализировали работу с IR
  Serial.println("Enabled IRin");
}
void loop() 
{
  if (irrecv.decode(&results))            // The function decode(&results)) is deprecated and may not work as expected! Just use decode() without a parameter
  {
    Serial.println(results.value, HEX);
    irrecv.resume();                      // ждем следующее значение от пульта ДУ
  }
  delay(100);
}
