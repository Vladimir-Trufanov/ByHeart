/* ========================================================================= */
/*   Test02_LCD1602.ino                                                      */
/*   (c) 2024-01-27 - 2024-08-16 Труфанов Владимир                           */
/*                                                                           */
/*   Description:            проверка подключения дисплея LCD1602a через I2C */
/*                           в различных версиях Arduino IDE: 1.8.18 и 2.2.1 */
/* ========================================================================= */

// Подключаем штатную библиотеку Wire.h
#include <Wire.h>

// Подключаем библиотеку LCD_1602_RUS (наследницу LiquidCrystal_I2C.h)
#include <LCD_1602_RUS.h> 
// Создаём объект для LCD-дисплея
LCD_1602_RUS lcd(0x27,16,2); 
 
void setup()
{
  lcd.init();                       // проинициализировали lcd    
  lcd.backlight();                  // включили подсветку
  lcd.setCursor(0,0);               // установили курсор в начало 1 строки
  lcd.print("Hello, world");        // вывели текст
  lcd.setCursor(0,1);               // установили курсор в начало 2 строки
  lcd.print("РУСИФИК-ация! 58");    // распечатали текст
}

void loop()
{
}
