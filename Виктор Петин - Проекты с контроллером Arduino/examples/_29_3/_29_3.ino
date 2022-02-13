/*  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

/* 
 * rosserial Subscriber Example
 */
#include <ros.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Float32.h>

ros::NodeHandle  nh;
void messageCb( const std_msgs::Float32& toggle_msg){
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp=");
  lcd.setCursor(0, 1);
  lcd.print(toggle_msg.data);}

ros::Subscriber<std_msgs::Float32> sub("temperature", &messageCb );

void setup() {
  lcd.begin(8, 2);
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  nh.spinOnce();
  delay(1000);
}
