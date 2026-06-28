/*  
 *   Nasal48.ino
*/

#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup() 
{  
    tft.init();
    tft.setRotation(2);
    tft.fillScreen(TFT_BLACK);


    // инициализация SPIFFS
    if (!SPIFFS.begin()) 
    {
        while (1) yield();
    }  

    tft.loadFont("nasalization48"); // загрузка в память шрифта
    tft.setCursor(40, 150);
    tft.setTextColor(TFT_ORANGE, TFT_BLACK);
    tft.println("ВНИМАНИЕ!");
    tft.unloadFont(); // выгрузка шрифта из памяти
}

void loop() 
{
}
