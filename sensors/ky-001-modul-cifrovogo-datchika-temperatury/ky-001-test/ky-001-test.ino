/* ========================================================================== */
/*                                                                            */
/*   ky-001-test.ino                                                           */
/*   (c) 2012 Author                                                          */
/*                                                                            */
/*   Description                                                              */
/*                                                                            */
/* ========================================================================== */

#include "OneWire.h"
#include "DallasTemperature.h"

// Провод данных подключен к контакту 2 на Arduino
#define ONE_WIRE_BUS 2
// Настройка экземпляра OneWire для связи с любыми устройствами OneWire (не только с микросхемами Maxim/Dallas temperature)
OneWire oneWire(ONE_WIRE_BUS);
// Передача ссылки экземпляра  OneWire для создания экземпляра DallasTemperature.
DallasTemperature sensors(&oneWire);
void setup(void)
{
  // Запуск последовательного порта
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");
  // Инициализация библиотеки DallasTemperature
  sensors.begin();
}
void loop(void)
{ 
  // вызвать sensors.requestTemperatures() для отправки глобального запроса температуры всем устройствам на шине
  Serial.println("Requesting temperatures...");
  sensors.requestTemperatures(); // Отправка команды для получения температуры
  Serial.println("DONE");
  Serial.print("Temperature for Device 1 is: ");
  Serial.println(sensors.getTempCByIndex(0)); //На одной шине может быть несколько устройств. 0 относится к первому устройству на проводе
  delay(3000);
}
