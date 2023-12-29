// IRremote_V2.ino
// 
// Формирование готовых команд для отправки ИК сообщения
// с пультов разных устройств по типу:
//
// sendNEC(0x0, 0x15);
// sendNEC(0x0, 0x11);
// 
// sendSamsung(0x707, 0x2);
// sendNEC(0x4000, 0x10);

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
  if (IrReceiver.decode()) 
  {
    switch (IrReceiver.decodedIRData.protocol) 
    {
      case RC5: printDemo("sendRC5"); break;
      case RC6: printDemo("sendRC6"); break;
      case NEC: printDemo("sendNEC"); break;
      case SONY: printDemo("sendSony"); break;
      case PANASONIC: printDemo("sendPanasonic"); break;
      case JVC: printDemo("sendJVC"); break;
      case SAMSUNG: printDemo("sendSamsung"); break;
      case WHYNTER: printDemo("sendWhynter"); break;
      case LG: printDemo("sendLG"); break;
      case SHARP: printDemo("sendSharp"); break;
      case DENON: printDemo("sendDenon"); break;
      case LEGO_PF: printDemo("sendLegoPowerFunctions"); break;
      default:
        IrReceiver.printIRResultShort(&Serial); //неведомая хрень
    }
    IrReceiver.resume();
  }
}

void printDemo(const char *functionName) 
{
  Serial.print(functionName);
  Serial.print("(0x");
  Serial.print(IrReceiver.decodedIRData.address, HEX);
  Serial.print(", 0x");
  Serial.print(IrReceiver.decodedIRData.command, HEX);
  Serial.println(");");
}
