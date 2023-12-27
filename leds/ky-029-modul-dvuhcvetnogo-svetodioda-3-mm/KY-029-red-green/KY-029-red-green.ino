/* ========================================================================== */
/*   KY-029-red-green.ino                                                               */
/*   (c) 2012 Author                                                          */
/*                                                                            */
/*   Description:               Cкетч будет постепенно изменять интенсивность */ 
/*                                                  красного и зеленого цвета */
/* ========================================================================== */

int red = 12;   // Контакт для красного цвета
int green = 11; // Контакт для зеленого цвета
int val;        

void setup() 
{
  pinMode(red, OUTPUT);   
  pinMode(green, OUTPUT);
}

void loop() 
{
  /*
  for(val=255; val>0; val--) 
  { 
    analogWrite(red, val);          // Установка красного цвета
    analogWrite(green, 255 - val);  // Установка зеленого цвета
    delay(10);
  }
  
  for(val=0; val<255; val++) 
  { 
    analogWrite(red, val);          // Установка красного цвета
    analogWrite(green, 255 - val);  // Установка зеленого цвета
    delay(10);
  }
  */

  delay(1000);
  analogWrite(red, 0);         
  analogWrite(green, 0); 

  delay(2000);
  analogWrite(red, 0);         
  analogWrite(green, 255); 
 
  delay(1000);
  analogWrite(red, 0);         
  analogWrite(green, 0); 

  delay(2000);
  analogWrite(red, 255);         
  analogWrite(green, 0); 
  
  delay(1000);
  analogWrite(red, 0);         
  analogWrite(green, 0); 

  // хотелось сделать желтый
  delay(2000);
  analogWrite(green, 185); 
  analogWrite(red, 200);         
}
