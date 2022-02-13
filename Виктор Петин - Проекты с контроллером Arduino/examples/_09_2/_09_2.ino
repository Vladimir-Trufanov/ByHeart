// Пример из книги
// Опрос состояния мыши PS/2
// и вывод в поседовательный порт

#include <ps2.h>

// pin 10 - mouse data pin, 
// pin11 -  clock pin
PS2 mouse(11, 10);

// Инициализация мыши - сброс
// установка режима для трехкнопочной мыши
 
void mouse_init()
{
  mouse.write(0xff);  // команда сброса
  mouse.read();  // ответ мыши
  mouse.read();  //  
  mouse.read();  //  
  mouse.write(0xf0);  // remote mode
  mouse.read();  // ответ мыши
  delayMicroseconds(100);
  mouse.write(0xF3);Serial.print(0xF3,HEX);Serial.print(" - "); 
  Serial.println(mouse.read(),HEX);
  mouse.write(200);Serial.print(200,DEC);Serial.print(" - "); 
  Serial.println(mouse.read(),HEX);
  mouse.write(0xF3);Serial.print(0xF3,HEX);Serial.print(" - "); 
  Serial.println(mouse.read(),HEX);
  mouse.write(100);Serial.print(100,DEC);Serial.print(" - "); 
  Serial.println(mouse.read(),HEX);
  mouse.write(0xF3);Serial.print(0xF3,HEX);Serial.print(" - "); 
  Serial.println(mouse.read(),HEX);
  mouse.write(80);Serial.print(80,DEC);Serial.print(" - "); 
  Serial.println(mouse.read(),HEX);
  mouse.write(0xF2);Serial.print(0xF2,HEX);Serial.print(" - "); 
  Serial.println(mouse.read(),HEX);
  Serial.println(mouse.read(),HEX);
  delay(1000);
}

void setup()
{
  Serial.begin(9600);
  mouse_init();
}

// запрос состояния мыши
// получение ответа - 4 байт
void loop()
{
  char mstat;
  char mx;
  char my;
  char mz;

  /* чтение из мыши */
  mouse.write(0xeb);  // запрос
  mouse.read();      // 
  mstat = mouse.read();
  mx = mouse.read();
  my = mouse.read();
  mz = mouse.read();
  if(mstat!=0x08) // ничего не произошло
   {
   Serial.print(mstat, BIN);
   if(bitRead(mstat,0)==1)
     Serial.print("Click left button ");
   if(bitRead(mstat,1)==1)
     Serial.print("Click right button ");
   if(bitRead(mstat,2)==1)
     Serial.print("Click middle button ");
   Serial.print("\tX=");
   Serial.print(mx, DEC);
   Serial.print("\tY=");
   Serial.print(my, DEC);
   Serial.print("\tZ=");
   Serial.print(mz, DEC);
   Serial.println();
   delay(300);
   }
}
