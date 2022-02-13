// Подключение библиотеки
#include <LiquidCrystalRus.h>
// Создаём объект используя конструктор класса LiquidCrystal
// 12 – RS,11 – Enable,5 – D4, 4 – D5,3 – D6,2 - D7
LiquidCrystalRus lcd(12, 11, 5, 4, 3, 2);

byte s1[8]={B11111,B11111,B11111,B11111,B11111,B11111,B11111};
byte s2[8]={B00000,B00000,B11111,B11111,B11111,B11111,B11111};
byte s3[8]={B00000,B00000,B00000,B00000,B11111,B11111,B11111};
byte s4[8]={B00011,B00011,B00011,B00011,B00011,B00011,B00011};

// начальная установка
void setup()
 {
  // размерность индикатора 
  lcd.begin(16, 4);
  // Начальное сообщение
  lcd.setCursor(0, 0);
  lcd.print("Демо к книге");
  lcd.setCursor(0, 1);
  lcd.print("Arduino");
  lcd.setCursor(0, 2);
  lcd.print("Возможности");
  lcd.setCursor(0, 3);
  lcd.print("WH1604");
  lcd.cursor();
  delay(10000);
void loop()
 {
  // выключить дисплей без потери отображаемой на нем информации
  lcd.noDisplay();
  delay(3000);
  // включить дисплей без потери отображаемой на нем информации
  lcd.display();
  delay(3000);  
  //***** Вывод слева-направо  *******
  lcd.clear();                      // очистить экран
  lcd.leftToRight();                // слева-направо
  lcd.cursor();                     // курсор - подчеркивание
  lcd.setCursor(0, 0);              // позиция 0,0
  String text1="Слева-направо";
  for(int i = 0; i < text1.length(); i++)
   {
   lcd.write(text1[i]);             // посимвольный вывод
   delay(300);                      // задержка
   } 
  lcd.noCursor();                   // курсор - спрятан
  lcd.setCursor(0, 1);              // позиция 0,1
  for(int i = 0; i < text1.length(); i++)
   {
   lcd.write(text1[i]);             // посимвольный вывод
   delay(300);                      // задержка
   }  
  //***** Вывод Справа-налево  *******
  lcd.rightToLeft();                // справа-налево
  lcd.blink();                      // курсор - мигающий
  lcd.setCursor(15, 2);             // позиция 15,2
  String text2="овелан-оварпС";
  for(int i = 0; i < text2.length(); i++)
   {
   lcd.write(text2[i]);             // посимвольный вывод
   delay(300);                      // задержка  
   }   
  lcd.clear();
//***** autoscroll слева-направо  *******
  lcd.leftToRight();
  lcd.autoscroll();
  String text3="autoscroll";
  lcd.blink();
  lcd.setCursor(7, 1);
  for(int i = 0; i < text3.length(); i++)
   {
   lcd.write(text3[i]);
   delay(300);  
   } 
  // справо-налево 
  lcd.rightToLeft();
  lcd.setCursor(7, 2);
  for(int i = 0; i < text3.length(); i++)
   {
   lcd.write(text3[i]);
   delay(300);  
   }  
  lcd.noAutoscroll();
  lcd.clear(); 
//***** перемещения курсора  *******
  lcd.leftToRight();
  lcd.cursor();
  lcd.blink();
  for(int i=0;i<10;i++)
   {
   int rand1=(micros()+millis())%1000;  
   lcd.setCursor(rand1%15,rand1%4);
   delay(1000);
   }
  lcd.noBlink();
  for(int i=0;i<10;i++)
   {
   int rand1=(micros()+millis());  
   lcd.setCursor(rand1%15,rand1%4);
   delay(1000);
   }
  delay(1000);
  lcd.home();  
for(int i=0;i<4;i++)
   {
   ;
   }
 lcd.createChar(0, s1);
 lcd.createChar(1, s1);
 lcd.createChar(2, s1);
 lcd.createChar(3, s1);
 lcd.setCursor(0, 0);
 lcd.write(0);lcd.write("");
 lcd.write(1);lcd.write("");
 lcd.write(2);lcd.write("");
 lcd.write(3);lcd.write("");
 delay(10000);


}

