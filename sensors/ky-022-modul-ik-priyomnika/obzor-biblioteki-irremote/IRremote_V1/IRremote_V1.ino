#include <IRremote.h>

void setup() 
{
  // Открываем порт для связи с ПК
  Serial.begin(9600);
  // Старт приема: приемник ПИН 2,индикация ПИН 13
  IrReceiver.begin(2, true, 13);
}

void loop() 
{
  // Если есть данные на приёме  
  if (IrReceiver.decode()) 
  {                  
    IrReceiver.printIRResultShort(&Serial);  // выводим данные в монитор порта
    IrReceiver.resume();                     // очищаем и ждем следующую команду
  }
  delay(300);
}
