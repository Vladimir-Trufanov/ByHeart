// амплитудный анализ звука

#include "VolAnalyzer.h"
VolAnalyzer analyzer(A0);

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (analyzer.tick()) 
  {
    // Пример1. Обработка звука
    Serial.print(analyzer.pulse() * 20); // скачок громкости
    Serial.print(',');
    Serial.print(analyzer.getVol());    // громкость 0-100
    Serial.print(',');
    Serial.print(analyzer.getRaw());    // сырая величина
    Serial.print(',');
    Serial.println(analyzer.getMax());  // амплитудная огибающая

    /*
    // Пример2. Просто вывод 5 линий на плоттере
    Serial.print(1); 
    Serial.print(',');
    Serial.print(4);     // громкость 0-100
    Serial.print(',');
    Serial.print(9);     // сырая величина
    Serial.print(',');
    Serial.print(16);    // сырая величина
    Serial.print(',');
    Serial.println(25);  // амплитудная огибающая
    */
  }
}
