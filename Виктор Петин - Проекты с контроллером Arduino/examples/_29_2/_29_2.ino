/* 
 * rosserial Subscriber Example
 * Blinks an LED on callback
 Subscriber and Publisher
 */

#include <ros.h>
#include <std_msgs/Empty.h>
#include <std_msgs/String.h>

ros::NodeHandle  nh;
int x;
String str;

void messageCb( const std_msgs::Empty& toggle_msg){
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
  x=HIGH-digitalRead(13);
}

ros::Subscriber<std_msgs::Empty> sub("toggle_led", &messageCb );

void setup()
{ 
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(chatter);
}

void loop()
{  
  nh.spinOnce();
  delay(1000);
}


