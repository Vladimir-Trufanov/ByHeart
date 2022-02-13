
#include <avr/pgmspace.h>

#include <avrpins.h>
#include <max3421e.h>
#include <usbhost.h>
#include <usb_ch9.h>
#include <Usb.h>
#include <usbhub.h>
#include <avr/pgmspace.h>
#include <address.h>
#include <hid.h>
#include <hiduniversal.h>

#include "hidjoystickrptparser.h"

#include <printhex.h>
#include <message.h>
#include <hexdump.h>
#include <parsetools.h>

USB                                             Usb;
USBHub                                          Hub(&Usb);
HIDUniversal                                    Hid(&Usb);
JoystickEvents                                  JoyEvents;
JoystickReportParser                            Joy(&JoyEvents);



#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#define MAX_BUFF 32 //Буфер приёма-передачи

void setup()
{
  Serial.begin( 115200 );
  Serial.println("Start");

  if (Usb.Init() == -1)
      Serial.println("OSC did not start.");
      
  delay( 200 );

  if (!Hid.SetReportParser(0, &Joy))
      ErrorMessage<uint8_t>(PSTR("SetReportParser"), 1  ); 


  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  
  Mirf.setRADDR((byte *)"defender"); //Хдесь задаём адрес
  Mirf.payload = MAX_BUFF; //Здесь задаём буфер
  Mirf.channel = 10; 
//Это канал приёма-передачи - должен 
//быть одинаковым у устройств.
  Mirf.config();
  
  Serial.println("Start.."); 
}

char buff[MAX_BUFF];
int c_count = 0;



void loop()
{
    Usb.Task();
    //if()
      //{
      Serial.print(JoyEvents.X,HEX);Serial.print(" ");
      Serial.print(JoyEvents.Y,HEX);Serial.print(" ");
      Serial.print(JoyEvents.Z1,HEX);Serial.print(" ");
      Serial.print(JoyEvents.Z2,HEX);Serial.print(" ");
      Serial.print(JoyEvents.Rz,HEX);Serial.print(" ");
      Serial.println();//}
      buff[0]=map(JoyEvents.X,0,255,1,100);
      buff[1]=map(JoyEvents.Y,0,255,1,100);;
      buff[2]=map(JoyEvents.Z1,0,255,1,100);
      buff[3]=map(JoyEvents.Z2,0,255,1,100);
      buff[4]=JoyEvents.Rz+1;
      buff[5]=0;
    Mirf.setTADDR((byte *)"automobile1"); //Адрес!
    Serial.print(">");
    Mirf.send((uint8_t *)buff);
    while(Mirf.isSending()){
    }
    Serial.println(buff);
      
    delay(300);
}

