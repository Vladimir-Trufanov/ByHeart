/* ========================================================================== */
/*   KY-032-red-green.ino, v1.0, 2023.12.28                                   */
/*   (c) 2023 Труфанов В.Е.                                                   */
/*                                                                            */
/*   Description:            Cкетч датчика дальномера: лампочка горит зеленым */
/*                          цветом, пока препятствие нет и загорается красным */
/*                                                  при появлении препятствия */ 
/* ========================================================================== */

int red = 12;   // Контакт для красного цвета
int green = 11; // Контакт для зеленого цвета

int ledPin = 13;      // LED pin on arduino
int detectorPin = 3;  // obstacle avoidance sensor interface
int val;              // variable to store result

void setup() 
{
  pinMode(red, OUTPUT);   
  pinMode(green, OUTPUT);

  pinMode(ledPin, OUTPUT);  // Define LED as output interface
  pinMode(detectorPin, INPUT);  // Define obstacle avoidance sensor as input interface
  flashGreen(); 
}

void loop() 
{
  val = digitalRead(detectorPin); // Read value from sensor
  if(val == LOW) // When the sensor detects an obstacle, the LED on the Arduino lights up
  {
    flashRed();
    digitalWrite(ledPin, HIGH);
    delay(2000);  
  }
  else
  {
    digitalWrite(ledPin, LOW);
    flashGreen(); 
  }

  /*
  flashOff(); 
  delay(2000);
  flashGreen(); 
  delay(2000);
  flashOff(); 
  delay(2000);
  flashRed();
  delay(2000);
  */

}

// Зажечь лампочку зеленым цветом
void flashGreen() 
{
  analogWrite(red, 0);         
  analogWrite(green, 100); 
}

// Зажечь лампочку красным цветом
void flashRed() 
{
  analogWrite(red, 255);         
  analogWrite(green, 0); 
}
// Выключить лампочку
void flashOff() 
{
  analogWrite(red, 0);         
  analogWrite(green, 0); 
}
