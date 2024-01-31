/*
Тестировалось на Arduino IDE 1.8.5
Дата тестирования 11.02.2020г.
*/

const int sampleWindow = 60;                    // Время измерения в мс
unsigned int sample;                             // Объявляем переменную sample
 
void setup() 
{
   Serial.begin(9600);                      
}
 
void loop() 
{
   // Cохраняем текущие значение millis в startMillis
   unsigned long startMillis= millis();         
   // Создаем переменноую peakToPeak, где храним разницу между минимальным и максимальным сигналом
   unsigned int peakToPeak = 0;                

   // signalMax максимальным значением
   unsigned int signalMax = 0; 
   // signalMin минимальным значением                 
   unsigned int signalMin = 1024;              

   // Пока в startMillis содержащиеся больше заданного sampleWindow, выполняется код в цикле while
   while (millis() - startMillis < sampleWindow) 
   {
      // Сохраняем значение переменной sample считаннное с аналогового входе 0
      sample = analogRead(0);    
      // Если значение sample меньше 1024, то есть максимальное значение, читаемое на аналоговом порту                
      if (sample < 1024)                         
      {
         // Если значение семпла больше максимального значения, найденного в signalMax
         if (sample > signalMax)                
         {
            // Обновление значения signalMax, содержащимся в sample
            signalMax = sample; 
         }
         //  В противном случае, если значение семпла меньше, чем signalMin
         else if (sample < signalMin) 
         {
            // Обновление значения signalMin, содержащимся в sample
            signalMin = sample;  
         }
      }
   }
   //  В переменной peakToPeak будет хранится разницу между максимальным значением и минимальным значением.
   peakToPeak = signalMax - signalMin; 
   // Значение peakToPeak умножается на 5 - это напряжение, с которым работает Arduino, а затем делим на 1024, поскольку на аналоговом порту от 0 до 1024.
   double volts = (peakToPeak * 5.0) / 1024;  
   // Отправляем переменную в вольте.
   Serial.println(volts); 
}
