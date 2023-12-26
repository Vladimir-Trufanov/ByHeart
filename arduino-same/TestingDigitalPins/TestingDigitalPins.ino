/* ========================================================================== */
/*   TestingDigitalPins.ino                                                   */
/*   (c) 2012 Author                                                          */
/*                                                                            */
/*   Description:  Тестирование цифровых пинов                                */
/* ========================================================================== */

#define FIRST_PIN 0 // первый вывод
#define LAST_PIN 19 // последний вывод

void Test1(byte pin)
{
   // Указываем номер пина
   if(pin < 10) Serial.print(" PIN:  ");
   else Serial.print(" PIN: ");
   Serial.print(pin);
   // Проверяем перевод пина на нижний уровень
   pinMode(pin, OUTPUT);
   digitalWrite(pin, 0);
   Serial.print("    LOW: ");
   if(!digitalRead(pin)) Serial.print("OK  ");
   else Serial.print("FAIL");
   // Проверяем перевод пина на верхний уровень
   digitalWrite(pin, 1);
   Serial.print("  HIGH: ");
   if(digitalRead(pin)) Serial.print("OK  ");
   else Serial.print("FAIL");
   // Переводим пин на вход и проверяем
   pinMode(pin, INPUT);
   Serial.print("  PULL UP: ");
   if(digitalRead(pin)) Serial.print("OK  ");
   else Serial.print("FAIL");
   // Записываем ноль на вход (не знаю, зачем?)
   digitalWrite(pin, 0);
}

void Test2(byte pin)
{
   Serial.print("     ");
   pinMode(pin, OUTPUT);
   digitalWrite(pin, 1);
   delay(5);
   if(!digitalRead(pin))Serial.println("SHORT");
   else Serial.println("OK");
   pinMode(pin, INPUT);
   digitalWrite(pin, 0);
}

void setup() 
{
   Serial.begin(9600);
   Serial.println("Проверка короткого замыкания на GND или VCC и между контактами:");
   Serial.println();
   for(byte i = FIRST_PIN; i <= LAST_PIN; i++)
   {
      // Все пины переводим на чтение
      for(byte j = FIRST_PIN; j <= LAST_PIN; j++)
      {
         pinMode(j, INPUT);
         digitalWrite(j, 0);
      }
      Test1(i);
      for(byte j = FIRST_PIN; j <= LAST_PIN; j++)
      {
         pinMode(j, OUTPUT);
         digitalWrite(j, 0);
      }
      Test2(i);
  }
  for(byte j = FIRST_PIN; j <= LAST_PIN; j++)
  {
      pinMode(j, INPUT);
      digitalWrite(j, 0);
  }
}

void loop() 
{
   // Все пины переводим на чтение
   for(byte j = FIRST_PIN; j <= LAST_PIN; j++)
   {
      pinMode(j, INPUT);
      digitalWrite(j, 0);
   }
   // Мигаем 13-тым пином
   // Проверяем перевод пина на нижний уровень
   Serial.println(" ");
   pinMode(13, OUTPUT);
   digitalWrite(13, 0);
   Serial.print("13 LOW: ");
   if(!digitalRead(13)) Serial.print("OK");
   else Serial.print("FAIL");
   delay(1000);
   // Проверяем перевод пина на верхний уровень
   digitalWrite(13, 1);
   Serial.print(" -> 13 HIGH: ");
   if(digitalRead(13)) Serial.println("OK");
   else Serial.println("FAIL");
   delay(2000);
}
