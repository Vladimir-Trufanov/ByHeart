#include <SPI.h>      // библиотека для обмена данными по протоколу SPI 
#include <nRF24L01.h> // библиотека для nRF24L01+
#include <RF24.h>     // библиотека для радио модуля

RF24 radio(6,7);                 

int serial_putc(char c, FILE *) 
{
  Serial.write(c);
  return c;
}

void printf_begin(void) 
{
  fdevopen(&serial_putc, 0);
}

void setup(void)
{
  Serial.begin(9600);
  printf_begin();
  radio.begin();
  radio.setAutoAck(false);
  // Включаем прием сигнала
  radio.startListening(); 
  // Выводим настройки модуля
  radio.printDetails(); 
}

void loop(void) {;}
