/*  
 *   Ohotnik.ino
*/

#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

uint16_t color24to16( uint8_t r, uint8_t g, uint8_t b ){
    uint16_t c = ((r & 0xF8)<<8) | ((g & 0xFC)<<3) | ((b & 0xF8)>>3);
    Serial.println(c, HEX);
    return c;
}

void setup() {
    Serial.begin(115200);

    color24to16(0xC8, 0x8C, 0x1E);
  
    tft.init();
    tft.setRotation(2);
    tft.fillScreen(TFT_BLACK);

    //tft.setCursor(0, 0);
    tft.setTextSize(3);
    tft.setTextColor( color24to16(255,0,0) );
    tft.println("каждый");
    tft.setTextColor( color24to16(255,128,0) );
    tft.println("охотник");
    tft.setTextColor( color24to16(255,255,0) );
    tft.println("желает");
    tft.setTextColor( color24to16(0,255,0) );
    tft.println("знать");
    tft.setTextColor( color24to16(0,255,255) );
    tft.println("где");
    tft.setTextColor( color24to16(0,0,255) );
    tft.println("сидит");
    tft.setTextColor( color24to16(255,0,255) );
    tft.println("фазан");
}

void loop() {
}
