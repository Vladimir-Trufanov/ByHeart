// Пример отправки и приёма структуры через Serial
// ОТПРАВИТЕЛЬ
// Ардуины соединены так:
// отправитель D01 -> приёмник D00
#include <SoftwareSerial.h>
SoftwareSerial mySerial(0,1); // RX, TX
struct Str 
{
  byte val_b;
  int val_i;
  long val_l;
  float val_f;
};
void setup() 
{
  Serial.begin(9600);
  mySerial.begin(4000);
}

void loop() 
{
  // буфер на отправку
  Str buf;
  // заполняем
  buf.val_b = 123;
  buf.val_i = 12345;
  buf.val_l = 123456;
  buf.val_f = 123.456;
  // отправляем родным write()
  // указываем ему буфер-структуру, но приводим тип к byte*
  // размер можно указать через sizeof()
  mySerial.write((byte*)&buf, sizeof(buf));
  delay(2000);
}
