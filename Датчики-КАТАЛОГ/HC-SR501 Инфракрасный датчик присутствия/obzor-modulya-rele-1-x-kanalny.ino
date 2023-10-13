/*
  Тестирование производилось на Arduino IDE 1.6.11
  Дата тестирования 28.09.2016г.
*/ 

int Relay = 5;          // Указываем, что вывод реле In1, подключен к реле цифровому выводу 5

void setup()
{
  pinMode(5, OUTPUT);  
}
void loop(){
 digitalWrite(5, LOW);  // Включаем реле
 delay(4000);           // Ждем 4с
 digitalWrite(5, HIGH); // Выключаем реле
 delay(4000);           // Ждем 4С
}
