// Опрос датчика расстояния с помощью библиотеки NewPing
// PollingByNewPing.ino

#define HC_TRIG 3
#define HC_ECHO 2

#include "NewPing.h"
// указываем пины и макс. расстояние в сантиметрах
NewPing sonar(HC_TRIG, HC_ECHO, 100);
void setup() 
{
  Serial.begin(9600);       // для связи
}

void loop() 
{
  // получаем и выводим
  Serial.println(sonar.ping_cm());
  delay(50);
}
