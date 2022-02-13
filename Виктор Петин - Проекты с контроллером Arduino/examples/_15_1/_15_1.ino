
#include <Wire.h>
#include "RTClib.h"
#include <SD.h>

#include <SPI.h>
#include <OneWire.h>


OneWire  ds(7);  // on pin 7

byte my_addr[3][8]={{0x28,0x81,0xC4,0xBA,2,0,0,0x3B},
                    {0x28,0x67,0xE5,0xC7,2,0,0,0xA0},
                    {0x28,0xF6,0x98,0xBA,2,0,0,0x92}};
int tek_sensor=0;
File myFile;
RTC_Millis RTC;
DateTime dt;
unsigned int gettemp=0;
String sfilename;
char filename[20];
String sTemp;
String record;



void setup () {
    Serial.begin(9600);
    Wire.begin();
    RTC.begin(DateTime(__DATE__, __TIME__));
    if (!SD.begin(4)) {
      Serial.println("initialization SD failed!");
    return;
    }
    Serial.println("initialization SD done.");
       
}

void loop () 
 {
   
   // проверка прошло 60 сек?
   if(millis()/60000!=gettemp)
     {  
     //delay(5000);
     gettemp=millis()/60000;
     //char filename[get_file_name().length()-1];
     //int file=get_file_name().length();
     sfilename=get_file_name();
     //Serial.println(sfilename);
     sfilename.toCharArray(filename,20);
     //Serial.println(filename);
      if (SD.exists(filename)) 
       {
       ;//Serial.println("file exists.");
       } 
      else
       {
       ;//Serial.println("file not exists.");
       }
       myFile = SD.open(filename, FILE_WRITE);
       //String record;
       int Temp=get_temp(tek_sensor+1);
       //Serial.print(Temp/16);
       //Serial.print(".");
       //Serial.println(((Temp%16)*100)/16);
       sTemp=String(Temp/16);
       sTemp+=".";
       sTemp+=String(((Temp%16)*100)/16);
       //record=get_time()+" "+String(tek_sensor+1)+" "+sTemp;
       record=get_time();
       record+=" ";
       record+=String(tek_sensor+1);
       record+=" ";
       record+=sTemp;
       //Serial.println(sTemp);
       record=get_time();
       record+=" ";
       record+=String(tek_sensor+1);
       record+=" ";
       record+=sTemp;
       Serial.println(record);
       myFile.println(record);
       myFile.close(); 
       tek_sensor=(tek_sensor+1)%3;
       //Serial.println(millis());
      //Serial.println("999");
      }
}
// получение времени дня
String get_time()
 {
     String time1;
     dt = RTC.now();
     if(dt.hour()<10)
       time1="0"+String(dt.hour(),DEC);
     else
       time1=String(dt.hour(),DEC);
     if(dt.minute()<10)
       time1+=":0"+String(dt.minute(),DEC);
     else
       time1+=":"+String(dt.minute(),DEC);
     //time1+=":"+String(dt.second(),DEC);
     return time1;
 }
// получение имени файла для текущего дня
String get_file_name()
 {
     String filename1;
     dt = RTC.now();
     filename1+=String(dt.year()-2000,DEC);
     if(dt.month()<10)
       filename1+="-0"+String(dt.month(),DEC);
     else
       filename1+="-"+String(dt.month(),DEC);
     if(dt.day()<10)
       filename1+="-0"+String(dt.day(),DEC);
     else
       filename1+="-"+String(dt.day(),DEC);
     //filename1+="-"+String(dt.hour(),DEC);
     //filename1+="-"+String(dt.minute(),DEC);
     //filename1+="-"+String(dt.second(),DEC);
     filename1+=".txt";
     return filename1;

 }
// получение температуры датчика
int get_temp(int nn)
 {
byte i;
byte present = 0;
byte data[12];
byte addr[8];
int Temp;
  ds.reset();
  ds.select(my_addr[nn-1]);
  ds.write(0x44,1);        // start conversion, with parasite power on at the end
  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.

  present = ds.reset();
  ds.select(my_addr[nn-1]);
  ds.write(0xBE);          // Read Scratchpad
  for ( i = 0; i < 9; i++) {         // we need 9 bytes
    data[i] = ds.read();
  }
  Temp=(data[1]<<8)+data[0];//take the two bytes from the response relating to temperature

  Temp=Temp;//divide by 16 to get pure celcius readout
  
  return Temp;
 }
 

