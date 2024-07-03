/* 
Тестировалось на Arduino IDE 1.8.0
Дата тестирования 12.08.2016г.

https://robotchip.ru/obzor-infrakrasnogo-datchika-dvizheniya-hc-sr501/

В примере подключается HC-SR501 к Arduino. В качестве индикации используются три светодиода, 
каждый из который отображает состояния датчика:

красный светодиод указывает, что датчик не готов;
желтый светодиод указывает, что датчик готов к обнаружению движения;
зеленый светодиод горит в течение 3 секунд при срабатывании датчика. 
 
Вместо светодиода, можно управлять внешним выходом (например, модулем реле)
*/ 

int detectedLED = 13;                // пин желтого - датчик готов к обнаружению движения
int readyLED = 12;                   // пин зеленого - светодиод горит в течение 3 секунд при срабатывании датчика
int waitLED = 11;                    // пин красного - датчик не готов

int pirPin = 7;                      // пин сигнального контакта датчика 
int motionDetected = 0;              // переменная для обнаружения движения
int pirValue;                        // переменная для сохранения значения из PIR

void setup() 
{
  pinMode(detectedLED, OUTPUT);      // установили пины как выход
  pinMode(readyLED, OUTPUT);         // 
  pinMode(waitLED, OUTPUT);          // 
  pinMode(pirPin, INPUT);            // установили пин датчика, как вход
  // Выполняем начальную задержку в 1 минуту для стабилизации датчика
  digitalWrite(detectedLED, LOW);    // погасили желтый
  digitalWrite(readyLED, LOW);       // погасили зеленый
  digitalWrite(waitLED, HIGH);       // зажгли красный
  delay(60000);
  // Минута прошла, зажигаем зеленый, гасим красный
  digitalWrite(readyLED, HIGH);
  digitalWrite(waitLED, LOW);
}

void loop() 
{
  pirValue = digitalRead(pirPin);    // считали значение датчика движения
  // Если движение есть, делаем задержку в 3 сек
  if (pirValue == 1)                 
  {               
    digitalWrite(detectedLED, HIGH);
    motionDetected = 1;
    delay(3000);
  } 
  /*
  pirValue = digitalRead(pirPin);    // считали значение датчика движения
  // Если движение есть, делаем задержку в 3 сек
  if (pirValue == 1)                 
  {               
    digitalWrite(detectedLED, HIGH);
    motionDetected = 1;
    delay(3000);
  } 
  else 
  {
    digitalWrite(detectedLED, LOW);
  }

  // Если сработал датчик, делаем задержку в 6 сек
  if (motionDetected == 1)
  {
    digitalWrite(detectedLED, LOW);
    digitalWrite(readyLED, LOW);
    digitalWrite(waitLED, HIGH);
    delay(6000);
    digitalWrite(readyLED, HIGH);
    digitalWrite(waitLED, LOW);
    motionDetected = 0;
  }
  */
}
