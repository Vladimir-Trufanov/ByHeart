// Опрос датчика расстояния с фильтрацией данных
// при помощи простейшего экспоненциального фильтра
//
// PollingWithDataFiltering.ino

#define HC_TRIG 3
#define HC_ECHO 2

void setup() 
{
  Serial.begin(9600);       // для связи
  pinMode(HC_TRIG, OUTPUT); // trig выход
  pinMode(HC_ECHO, INPUT);  // echo вход
}

float distFilt = 0;

void loop() 
{  
  float dist = getDist();               // получаем расстояние  
  distFilt += (dist - distFilt) * 0.2;  // фильтруем  
  Serial.println(distFilt);             // выводим
  delay(50);
}


float getDist() 
{
  // импульс 10 мкс
  digitalWrite(HC_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(HC_TRIG, LOW);
  // измеряем время ответного импульса
  uint32_t us = pulseIn(HC_ECHO, HIGH);
  // считаем расстояние и возвращаем
  return (us / 58.3);
}
