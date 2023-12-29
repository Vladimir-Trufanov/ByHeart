// IRremote_V3.ino
// Пример управления телевизором Samsung:
// "переключиться на меньший канал, переключиться на больший канал"

#include <IRremote.h>

void setup() 
{
  // Старт передачи: ИК светодиод ПИН 4,индикация ПИН 12
  IrSender.begin(4, true, 12);
}

void loop() 
{
  IrSender.sendSamsung(0x707, 0x12, 0); // переключаем ТВ канал туда ch+
  delay(5000);                          // пауза 5 секунд
  IrSender.sendSamsung(0x707, 0x10, 0); // переключаем ТВ канал обратно ch-
  delay(5000);                          // пауза 5 секунд
}
