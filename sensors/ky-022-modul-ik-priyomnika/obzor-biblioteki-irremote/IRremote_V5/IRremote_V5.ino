#include <IRremote.h>

void setup() 
{
  // Старт приема: приемник ПИН 15,индикация ПИН 13
  IrReceiver.begin(15, true, 12);
  // Светодиод ПИН 14
  pinMode(14,OUTPUT);
}
void loop() 
{
  if (IrReceiver.decode()) 
  {
    // Получаем сырые данные и сохраняем в переменную
    uint32_t r = IrReceiver.decodedIRData.decodedRawData;
    if (r == 0xED120707) digitalWrite(14,HIGH); // зажигаем светодиод
    if (r == 0xEF100707) digitalWrite(14,LOW);  // гасим светодиод   
    IrReceiver.resume();
  }
}
