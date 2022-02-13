#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#define MAX_BUFF 32 //Буфер приёма-передачи

void setup(){
  Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  
  Mirf.setRADDR((byte *)"automobile1"); //Здесь задаём адрес
  Mirf.payload = MAX_BUFF; //Здесь задаём буфер
  Mirf.channel = 10; 
//Это канал приёма-передачи - должен 
//быть одинаковым у устройств.
  Mirf.config();
  
  // настраиваем выводы для моторов
  pinMode(3, OUTPUT); 
  pinMode(4, OUTPUT); 
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  Serial.println("Start.."); 
}

char buff[MAX_BUFF];

void loop(){
  delay(10);
  //receiving  
  if(Mirf.dataReady()) {
    Mirf.getData((uint8_t *)buff);
    int fb1=buff[0];
    int lr=buff[1];
    go12(fb1,lr1);
  }
  delay(100);
}
// 
void go12(int fb,int lr)
  {
  //вперед-назад
  if(fb>50)  
     {digitalWrite(3,HIGH);digitalWrite(4,LOW);
      digitalWrite(5,HIGH);digitalWrite(6,LOW);}
  else if(fb<50)
     {digitalWrite(3,LOW);digitalWrite(4,HIGH);
      digitalWrite(5,LOW);digitalWrite(6,HIGH);}
  else  
     {digitalWrite(3,LOW);digitalWrite(4,LOW);
      digitalWrite(5,LOW);digitalWrite(6,LOW);}
  //влево-вправо
  int lr1=map(abs(50-lr),1,50,1,255);
  int fb1=map(abs(50-fb),1,50,1,255);
  if(lr<50)
    {int left=min(255,max(0,fb1-lr1/2));
     int right=min(255,fb1+lr1/2)}
  else
    {int right=min(255,max(0,fb1-lr1/2));
     int left=min(255,fb1+lr1/2)}
  analogWrite(9, left);
  analogWrite(10, right); 
  }

