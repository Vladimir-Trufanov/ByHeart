/*  
 *   Privet.ino
*/

#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup() 
{
    tft.init(); // инициализация дисплея
    tft.setRotation(2); // вращение на 180 градусов
    tft.fillScreen(TFT_BLACK); // заливка фона чёрным цветом

    tft.setCursor(60, 150); // x,y координаты текста
    tft.setTextColor(TFT_WHITE); // цвет текста - белый
    tft.setTextSize(2); // размер текста - №2 (7*2 = 14 точек)
    //tft.print("Привет!"); // вывод текста - Рсйгжу!   
    tft.print("А Б В Г Д Е Ё Ж З И Й К Л М Н О П Р С Т У Ф Х Ц Ч Ш Щ Ъ Ы Ь Э Ю Я а б в г д е ё ж з и й к л м н о п р с т у ф х ц ч ш щ ъ ы ь э ю я"); // вывод текста - Рсйгжу!   
    
}

void loop() 
{
}
