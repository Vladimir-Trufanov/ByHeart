// PollingOnTemperature.ino

// Опрос датчика расстояния средствами Arduino (опрашиваем через 50 мс)
// с коррекцией по температуре и результатом в целых миллиметрах
// (если фильтровать, будет еще лучше)

#define HC_TRIG 3
#define HC_ECHO 2

void setup() 
{
  Serial.begin(9600);       // для связи
  pinMode(HC_TRIG, OUTPUT); // trig выход
  pinMode(HC_ECHO, INPUT);  // echo вход
}

void loop() 
{
  int t = 24;           // представим, что получили с датчика
  int dist = getMm(t);  // получаем расстояние в мм
  Serial.println(dist); // выводим
  delay(50);
}

// сделаем функцию для удобства
int getMm(int t) 
{
  // импульс 10 мкс
  digitalWrite(HC_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(HC_TRIG, LOW);
  // измеряем время ответного импульса
  uint32_t us = pulseIn(HC_ECHO, HIGH);
  // считаем расстояние и возвращаем
  return (us * (t * 6 / 10 + 330) / 2000ul);
}
