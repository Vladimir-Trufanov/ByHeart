#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#define MAX_BUFF 32 //Буфер приёма-передачи

void setup(){
  Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  
  Mirf.setRADDR((byte *)"module1"); //Здесь задаём адрес
  Mirf.payload = MAX_BUFF; //Здесь задаём буфер
  Mirf.channel = 10; 
//Это канал приёма-передачи - должен 
//быть одинаковым у устройств.
  Mirf.config();
  
  Serial.println("Start.."); 
}

char buff[MAX_BUFF];
int c_count = 0;

void loop(){
  int i;
  //sending  
  if (c_count = Serial.available()) {
    if (c_count <= MAX_BUFF) {
      for (i=0; i<c_count; i++) {
        buff[i] = Serial.read();
      }
    } else {
      for (i=0; i<MAX_BUFF; i++) {
        buff[i] = Serial.read();
      }
    }
    buff[i] = 0;
    Mirf.setTADDR((byte *)" module2"); //Адрес!
    Serial.print(">");
    Mirf.send((uint8_t *)buff);
    while(Mirf.isSending()){
    }
    Serial.println(buff);
  }
  delay(10);
  //receiving  
  if(Mirf.dataReady()) {
    Mirf.getData((uint8_t *)buff);
    Serial.print("<");
    Serial.println(buff);
  }
  delay(100);
}

