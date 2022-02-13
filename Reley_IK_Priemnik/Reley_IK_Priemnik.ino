
#include "IRremote.h"
 
IRrecv irrecv(11);
decode_results results;

void setup()
{
  irrecv.enableIRIn();
  pinMode(13, OUTPUT); // 13 pin на реле IN
   Serial.begin(9600);
}
 
void loop()

{
  if (irrecv.decode(&results)) 
  {
    int res = results.value;
    Serial.println(res, HEX);

    
     if(res==0xFFFFA25D)// Если нажата кнопка "Отключить"
    {
     digitalWrite(13, LOW); // включаем реле     
    }

    
    if(res==0x6A95)// Если нажата кнопка "Включить" 
    {
     digitalWrite(13, HIGH);    // выключаем реле
    }
    
 
    irrecv.resume();
    delay(200);
  }
}
