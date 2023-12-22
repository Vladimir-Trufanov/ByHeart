/* ========================================================================== */
/*   KY013-test-v2.ino                                                        */
/*   (c) 2012 Author                                                          */
/*                                                                            */
/*   Description:                                                             */
//      Export: 16.06.2017 Copyright by Joy-IT - Published under CC BY-NC-SA 3.0 Page 56 of 214
//      KY-013 Temperature-Sensor module
/* ========================================================================== */

#include <math.h>

int sensorPin = A0; // Declaration of the input pin

// These function translates the recorded analog measurement
double Thermistor(int RawADC)
{
  double Temp;
  Temp = log(10000.0 * ((1024.0 / RawADC - 1)));
  Temp = 1 /(0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp)) * Temp);
  Temp = Temp - 273.15; // convert from Kelvin to Celsius
  return Temp;
}

// Serial output in 9600 Baud
void setup()
{
  Serial.begin(9600);
}

// The program measures the current voltage value on the NTC
// and translates it intp °C for the serial output
void loop()
{
  int readVal = analogRead(sensorPin);
  double temp = Thermistor(readVal);
  // Output on the serial interface
  Serial.print("Current temperature is:");
  Serial.print(temp);
  Serial.println("ºC");
  Serial.println("---------------------------------------");
  delay(500);
}
