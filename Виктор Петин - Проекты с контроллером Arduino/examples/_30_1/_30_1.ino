// include the X10 library files:
#include <x10.h>
#include <x10constants.h>

#define zcPin 2         // the zero crossing detect pin
#define dataPin 4       // the X10 data out pin
#define repeatTimes 1   // how many times each X10 message should repeat
// in an electrically noisy environment, you  
// can set this higher.


// set up a new x10  library instance:
x10 myHouse =  x10(zcPin, dataPin);

// ros_lib libraries
#include <ros.h>
#include <vp_x10_voice/X10.h>

ros::NodeHandle  nh;

vp_x10_voice::X10 x10_msg;
ros::Publisher pub_x10("data_from_x10", &x10_msg);

void messageCb( const vp_x10_voice::X10& toggle_msg){
  digitalWrite(13, HIGH-digitalRead(13)); 
  x10_msg.command1 = toggle_msg.command1;
  x10_msg.command2 = toggle_msg.command2;
  x10_msg.repeatTime = toggle_msg.repeatTime;
  pub_x10.publish(&x10_msg);
  int command1=toggle_msg.command1;
  int command2=toggle_msg.command2;
  int repeatTime=toggle_msg.repeatTime;
  myHouse.write(command1, command2,repeatTime);               
 }
ros::Subscriber<vp_x10_voice::X10> sub_x10("data_to_x10", &messageCb );


void setup() {
  Serial.begin(9600);
  nh.initNode();
  nh.subscribe(sub_x10);
  nh.advertise(pub_x10);
}

void loop() {
  nh.spinOnce();
  delay(1000);
}
