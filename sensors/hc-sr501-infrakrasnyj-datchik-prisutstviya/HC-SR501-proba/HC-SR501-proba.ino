/* 
По мотивам статьи:
https://robotchip.ru/obzor-infrakrasnogo-datchika-dvizheniya-hc-sr501/

В примере подключается HC-SR501 к Arduino. В качестве индикации используются три светодиода, 
каждый из который отображает состояния датчика:

красный светодиод указывает, что датчик не готов;
желтый светодиод указывает, что датчик готов к обнаружению движения;
зеленый светодиод горит в течение 3 секунд при срабатывании датчика. 
 
Вместо светодиода, можно управлять внешним выходом (например, модулем реле)
*/ 

int waitLED = 11;                    // пин красного - датчик не готов
int readyLED = 12;                   // пин желтого - датчик готов к обнаружению движения          
int detectedLED = 13;                // пин зеленого - светодиод горит в течение 3 секунд при срабатывании датчика

int pirPin = 7;                      // пин сигнального контакта датчика 
int sensorReady = 0;                 // флаг готовности датчика к обнаружению движения
int motionDetected = 0;              // флаг обнаруженного движения
int pirValue;                        // переменная для сохранения значения из PIR

void setup() 
{
  pinMode(detectedLED, OUTPUT);      // установили пины как выход
  pinMode(readyLED, OUTPUT);         // 
  pinMode(waitLED, OUTPUT);          // 
  pinMode(pirPin, INPUT);            // установили пин датчика, как вход
  // Выполняем начальную задержку в 1 минуту для стабилизации датчика
  digitalWrite(detectedLED, LOW);    // погасили зеленый
  digitalWrite(readyLED, LOW);       // погасили желтый
  digitalWrite(waitLED, HIGH);       // зажгли красный
  delay(15000);
  // Минута прошла, зажигаем желтый, гасим красный
  digitalWrite(readyLED, HIGH);
  digitalWrite(waitLED, LOW);
  sensorReady = 1;                   // подняли флаг готовности датчика к обнаружению движения
}

void loop() 
{
  // Если датчику разрешено обнаруживать движение, считываем его значение
  if (sensorReady == 1)                 
  {
    pirValue = digitalRead(pirPin);    // считали значение датчика движения
    // Если движение есть, то зажигаем зеленый светодиод и делаем задержку в 3 сек
    if (pirValue == 1)                 
    { 
      // Сбрасываем флаг готовности датчика движения и гасим желтую лампочку
      sensorReady = 0;
      digitalWrite(readyLED, LOW);    
      // Зажигаем зеленую лампочу, устанавливаем флаг               
      digitalWrite(detectedLED, HIGH);
      motionDetected = 1;
      delay(3000);
      // Сбрасываем флаг, гасим зеленый
      motionDetected = 0;
      digitalWrite(detectedLED, LOW);
      // Зажигаем красный
      digitalWrite(waitLED, HIGH); 
      // Ждем пол-минутки и разрешаем обнаруживать движение      
      delay(15000);
      digitalWrite(readyLED, HIGH);
      digitalWrite(waitLED, LOW);
      sensorReady = 1;                   // подняли флаг готовности датчика к обнаружению движения
    } 
  }
}
