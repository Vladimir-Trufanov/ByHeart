// Пример отправки и приёма структуры через Serial
// ПРИЁМНИК
// Ардуины соединены так:
// приёмник D00 -> отправитель D01
#include <SoftwareSerial.h>
SoftwareSerial mySerial(0,1); // RX, TX

// структура для приёма
// должна соответствовать отправляемой
struct Str 
{
  byte val_b;
  int val_i;
  long val_l;
  float val_f;
};

// создаём саму структуру
Str buf;
void setup() 
{
  Serial.begin(9600);
  mySerial.begin(4000);
}

void loop() 
{
  // читаем родным методом readBytes()
  // указываем ему буфер-структуру, но приводим тип к byte*
  // размер можно указать через sizeof()
  if (mySerial.readBytes((byte*)&buf, sizeof(buf))) 
  {
    Serial.println(buf.val_b);
    Serial.println(buf.val_i);
    Serial.println(buf.val_l);
    Serial.println(buf.val_f);
  }
}
