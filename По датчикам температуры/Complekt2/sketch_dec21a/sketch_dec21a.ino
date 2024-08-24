
/*
// t=20.54
#include <math.h>
const int pin_sensor = A0;

double f(int value) {
  double t;
  // t = log(10000.0 * ((1024.0 / value - 1)));
  t = log(((10240000/value) - 10000));
  t = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * t * t ))* t ); // уравнение Стейнхарта-Харта
  t = t - 273.15;
  return t;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(pin_sensor);
  double t =  f(value);
  Serial.print(t); 
  Serial.println(" C");
  delay(500);
}
*/

/*
// t=87.33
 #include "GyverNTC.h"
// термистор на пине А0
// сопротивление резистора 10к
// тепловой коэффициент 3950
GyverNTC therm(0, 10000, 3950);
void setup() {
  Serial.begin(9600);
}
void loop() {
  // вывести температуру (чтение с усреднением)
  Serial.println(therm.getTempAverage());
  delay(2000);
}
*/








/*
// t=-127
#include "OneWire.h"
#include "DallasTemperature.h"

#define ONE_WIRE_BUS 2 // Digital pin connected to the Data pin of the sensor

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600); // Initialize serial communication for debugging (optional)
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures(); // Request temperature reading
  float temperatureC = sensors.getTempCByIndex(0); // Get the temperature in Celsius

  // Display the temperature on the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  delay(1000); // Delay for one second before taking another reading
}
*/

//DS18B20
// t=-127
#include "OneWire.h"
#include "DallasTemperature.h"
 
OneWire oneWire(2);  // порт подключения датчика
DallasTemperature ds(&oneWire);

void setup() 
{
  Serial.begin(9600);   // инициализация монитора порта
  ds.begin();                 // инициализация датчика ds18b20
}

void loop() 
{
  ds.requestTemperatures();                       // считываем температуру с датчика
  
  Serial.print(ds.getTempCByIndex(0));   // выводим температуру на монитор
  Serial.println("C");
  delay (2000);
}
