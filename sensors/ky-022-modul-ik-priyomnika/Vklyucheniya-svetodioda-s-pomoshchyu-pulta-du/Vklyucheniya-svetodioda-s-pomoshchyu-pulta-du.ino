// Vklyucheniya-svetodioda-s-pomoshchyu-pulta-du.ino
//
// Включения штатного светодиода Arduino с помощью пульта ДУ от шторной ленты
// на Виданская 17б, кв.10

// FFA857   — зеленая стрелочка вверх
// FF8877   — зеленая стрелочка вниз

#include "IRremote.h"
IRrecv irrecv(2); // указываем вывод, к которому подключен приемник
decode_results results;

void setup() 
{
  // Запускаем прием
  irrecv.enableIRIn(); 
  // Подключаем и зажигаем светодиод
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() 
{
  // Действуем, если сигнал пришёл
  if (irrecv.decode(&results)) 
  {
    switch ( results.value ) 
    {
    case 0xFFA857:
        digitalWrite(LED_BUILTIN, HIGH );
        break;
    case 0xFF8877:
        digitalWrite(LED_BUILTIN, LOW );
        break;
    }    
    irrecv.resume(); // принимаем следующую команду
  }
  delay(100);
}
