// константы для выводов
#define PIN_TRIG 11
#define PIN_ECHO 10
#define PIN_PE 12
// расстояние обнаружения см
#define DIST_DETECT 15 // 15 см

// подключение библиотеки для HC SR04

// Minimalist library for ultrasound module to Arduino
// Work with ultrasound module in a simple and light way. Compatible with the modules HC-SR04, Ping))) and Seeed Studio sensor. This library aims to resource efficiency and to simplify access to data.
// Author: Erick Simões

#include <Ultrasonic.h>
// создание объекта Ultrasonic
Ultrasonic ultrasonic(PIN_TRIG, PIN_ECHO);
// переменная для хранения измеренного расстояния
float dist_cm=0;

void setup()  
{
   // запуск последовательного порта
   Serial.begin(9600);
   // назначить P-E как OUTPUT
   pinMode(PIN_PE, OUTPUT);
   digitalWrite(PIN_PE, LOW);
}
 
void loop() 
{
  
   // получить данные с дальномера
   // dist_cm = ultrasonic.Ranging(CM); - было в других версиях !!!
   dist_cm = ultrasonic.distanceRead(CM);
   Serial.println(dist_cm);
   // обнаружение объекта в зоне
   if(dist_cm>0 && dist_cm<DIST_DETECT) 
   {
      // включить воспроизведения мелодии
      digitalWrite(PIN_PE, HIGH);
      // пауза на время воспроизведения
      delay(6000);
      digitalWrite(PIN_PE, LOW);
   }

}
