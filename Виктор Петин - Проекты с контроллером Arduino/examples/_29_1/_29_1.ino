#include <OneWire.h>
OneWire  ds(10);  // линия 1-Wire будет на pin 10

#include <ros.h>
#include <std_msgs/Float32.h>

ros::NodeHandle  nh;
std_msgs::Float32 float32_msg;
ros::Publisher chatter("temperature", &float32_msg);


void setup(void) 
{
  nh.initNode();
  nh.advertise(chatter);
}



void loop(void) 
{
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];
  
  if ( !ds.search(addr)) {
      ds.reset_search();
      return;
  }
  

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1);         // запускаем конвертацию
  
  delay(1000);     // скорее всего достаточно 750ms 
  
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // считываем ОЗУ датчика

  for ( i = 0; i < 9; i++) {           // обрабатываем 9 байт
    data[i] = ds.read();
  }
  Serial.print(" CRC=");
  Serial.print( OneWire::crc8( data, 8), HEX);
  Serial.println();
  
  // высчитываем температуру :)
  int HighByte, LowByte, Temp;
  float Tempf1,Tempf2;
  LowByte = data[0];
  HighByte = data[1];
  Temp = (HighByte << 8) + LowByte;
  Tempf1=Temp/16; 
  Tempf2=(Temp%16)*100/16;
  float32_msg.data=Tempf1+Tempf2/100;
  
  chatter.publish( &float32_msg );
  nh.spinOnce();

}
