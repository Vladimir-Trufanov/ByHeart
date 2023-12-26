/* прошивка гирлянды от АРТЕМА МАТВЕЕВА
 *  
 * может использоватся в качестве гирлянды или как подсветка рабочего стола
 * имеет 5 режимов работы (можно добавлять и убирать)
 * может работать автономно
 * ВСЕ КОМПОНЕНТЫ ДЛЯ СБОРКИ ЕСТЬ В ГАЙВЕР КИТ!
 * создано для конкурса GIANT4
 */
//==========ИЗМЕНИТЬ==========//
#define A 9 // пин энкодера
#define B 10 // пин энкодера
#define C 11 // пин кнопки энкодера
#define LED_PIN 8 // пин ардесной светодиодной ленты
#define MODEL WS2812 // модель ленты
#define LED_NUM 60 // кол-во светодиодов ленте
#define MIN_LIGHT 0 // минималная яркость
#define MAX_LIGHT 100 // максималная яркость
#define MODES 5 // всего режимов
#define BRIGHT 15 // начальня яркость ленты
#define DELAY 30 // скорость эффектов
//==========БИБЛИОТЕКИ==========//
#include "FastLED.h"
#include <EncButton.h>
//==========ОСНОВНОЙ КОД(НЕ ТРОГАТЬ)==========//
int mode = 1;
byte baza = 0;
CRGB leds[LED_NUM];
EncButton<EB_TICK, A, B, 4> enc;
EncButton<EB_TICK, C> btn;
unsigned long timing;
void setup() {
  FastLED.addLeds<MODEL, LED_PIN, GRB>(leds, LED_NUM);
 
  FastLED.setBrightness(BRIGHT);
  Serial.begin(9600);
}
byte counter;
int val = 0;
int val2 = 0;  
void loop() {
//==========ОПРОС ЭНКОДЕРА==========//
  enc.tick();
  btn.tick();
  
  if (btn.click()){
  mode = mode + 1;
  if (mode > MODES){
  mode = 1;
  }
  }
  if (enc.right()) {
    val += 1;
    //Serial.println(val);
  }
  if (enc.left()) {
    val -= 1;
    //Serial.println(val);
  }
 
  if(val < MIN_LIGHT){
   val = MIN_LIGHT;
  }
  if(val > MAX_LIGHT){
   val = MAX_LIGHT;
  }
  val2 = constrain(val, 0, 255);
  val2 = map(val, 0, 255, MIN_LIGHT, MAX_LIGHT);
  val2 = constrain(val, MIN_LIGHT, MAX_LIGHT);

  //==========ЭФФЕКТ "РАДУГА"==========//
  if(mode == 1){
  FastLED.clear();
  if (millis() - timing > DELAY){
  timing = millis(); 
  FastLED.setBrightness(val2);
  for (int i = 0; i < LED_NUM; i++) {
    leds[i].setHue(counter + i * 255 / LED_NUM);
  }
  counter++;        // counter меняется от 0 до 255 (тип данных byte)
  FastLED.show();
  }
  
  //==========ЭФФЕКТ "КОНФЕТИ"==========//
  }else if(mode == 2){
  FastLED.clear();
  
  if (millis() - timing > DELAY){
  timing = millis(); 
  fadeToBlackBy(leds, LED_NUM, 2);
  int pos = random16(LED_NUM);
  leds[pos] += CHSV(baza++ + random8(64), 200, 255);
  FastLED.setBrightness(val2);
  FastLED.show();
    }

  //==========ЭФФЕКТ "БЕГУЩИЙ ОГОНЕК"==========// 
  }else if(mode == 3){
  FastLED.clear();

  if (millis() - timing > DELAY){
  timing = millis(); 
  FastLED.setBrightness(val2);
  fadeToBlackBy(leds, LED_NUM, 2);
  int pos1 = beatsin16(13, 0, LED_NUM - 1);
  leds[pos1] += CHSV(baza++, 255, 192);
  FastLED.setBrightness(val2);
  FastLED.show();
   }

  //==========ЭФФЕКТ "ФОКУС"==========// 
  }else if(mode == 4){
  FastLED.clear();
  
  if (millis() - timing > DELAY){
  timing = millis(); 
  fadeToBlackBy(leds, LED_NUM, 2);
  for (int i = 0; i < 8; i++) {
  leds[beatsin16(i + 7, 0, LED_NUM - 1)] |= CHSV(baza+=16, 200, 255);
  }
  FastLED.setBrightness(val2);
  FastLED.show();
   }
   
  //==========ЭФФЕКТ "РАДУГА С МЕРЦАНИЕМ"==========//
  }else if(mode == 5){
  FastLED.clear(); 
  
   if (millis() - timing > 20){
  timing = millis(); 
  fill_rainbow( leds, LED_NUM, baza++, 7);
  if (random8() < 80) { leds[ random16(LED_NUM) ] += CRGB::White; }
  FastLED.setBrightness(val2);
  FastLED.show();
    }
  }
}
