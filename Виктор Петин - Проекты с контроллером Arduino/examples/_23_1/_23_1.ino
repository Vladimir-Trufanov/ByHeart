// Краб
// 4 ноги, по 2 степени свободы
// 

#include <Servo.h> 
#include <IRremote.h> 
#include "Ultrasonic.h"

// trig -12, echo - 13
Ultrasonic ultrasonic(12, 13);
//вход ИК приемника
int RECV_PIN = 2;  
IRrecv irrecv(RECV_PIN); 
decode_results results; 
unsigned long ir_dt, old_ir;
long ir_kod;
unsigned long ir_time1, ir_time2;
// коды клавиш ИК пульта 
// lg 6710v00090d
#define FORWARD 32       //  pr +
#define BACK  33         //  pr -
#define CIRCLE_LEFT 17   //  vol-
#define CIRCLE_RIGHT 16  //   vol+
#define STOP 54          //   зеленая
#define SLEEP 55          //  красная
#define AWAKE 37         //  ок
#define EXT 50          //  желтая
#define AUTO 52          //  синяя

// горизонтальные 
Servo myservo11;
Servo myservo12;
Servo myservo13;
Servo myservo14;
// текущие позиции серв
int pos_stop[1][4]={{90,90,90,90}};

int arr_pos[4][6][4]={
    { // forward
    {90,90,90,90},{45,90,90,90},{45,135,90,90},
    {45,135,45,90},{45,135,45,135},{135,45,135,45}
    },
    { // back
    {90,90,90,90},{90,90,90,45},{90,90,135,45},
    {90,45,135,45},{135,45,135,45},{45,135,45,135}
    },
    { // circle_left
    {90,90,90,90},{0,90,90,90},{0,0,90,90},
    {0,0,0,90},{0,0,0,0},{180,180,180,180}
    },
    { // circle_right
    {90,90,90,90},{180,90,90,90},{180,180,90,90},
    {180,180,180,90},{180,180,180,180},{0,0,0,0}
    }
  };
// ir-управление, или робот
int ext=1;
   
void setup() 
  { 
  myservo11.attach(5);myservo12.attach(6); 
  myservo13.attach(7);myservo14.attach(8);  
  // начальные положения
  go_hor_all();
  // последовательный порт 
  Serial.begin(9600); 
  // включить приемник 
  irrecv.enableIRIn(); 
  // прерывания для ИК
  ir_time1=0;ir_time2=0;
  attachInterrupt(0, get_ir_kod, FALLING); 
  } 
 
 
void loop() 
  { 
  delay(1000);
  if(ext==0)
   {
   float dist_cm = ultrasonic.Ranging(CM);
   Serial.print("dist_cm=");Serial.println(dist_cm);
   if(dist_cm<10.0)
     ir_kod=CIRCLE_LEFT;
   else
     ir_kod=FORWARD;
   }
  if(ir_kod!=0)
   {
   Serial.print("ir_kod=");Serial.println(ir_kod);  
   switch(ir_kod)
     {
     case FORWARD :     // вперед
        course(1);
        Serial.print("forward\n");
        break;
     case BACK :     // назад
        course(2);
        Serial.print("back\n");
        break;
     case CIRCLE_LEFT:     // вращение влево
        course(3);
        Serial.print("circle_left\n");
        break;
     case CIRCLE_RIGHT :     // вращение вправо
        Serial.print("circle_right\n");
        course(4);
        break;
     case STOP :     // остановка
        ir_kod=0;
        go_hor_all();
        Serial.print("pause\n");
        break;
     case SLEEP :     // засыпание
        ir_kod=0;
        go_hor_all();
        myservo11.detach();myservo12.detach(); 
        myservo13.detach();myservo14.detach();
        digitalWrite(13,LOW);
        Serial.print("sleep\n");
        break;
     case AWAKE :     // пробуждение
        ir_kod=0;
        myservo11.attach(5);myservo12.attach(6); 
        myservo13.attach(7);myservo14.attach(8);
        digitalWrite(13,HIGH);
        go_hor_all();
        Serial.print("awake\n");
        break;
     case AUTO :     // режим автономный
        //ir_kod=FORWARD;
        ext=0;
        myservo11.attach(5);myservo12.attach(6); 
        myservo13.attach(7);myservo14.attach(8);
        Serial.print("auto\n");
        break;
    default:
        break;
     }
   } 
  
  } 

//
void go_hor_all()
  {
  myservo11.write(pos_stop[0][0]);
  myservo12.write(pos_stop[0][1]);
  myservo13.write(pos_stop[0][2]);
  myservo14.write(pos_stop[0][3]);
  delay(500); 
  }
// 
// вперед
void course(int variant)  
  {int i=0;;
  for(i=1;i<6;i++)
    {
    // горизонтали
    if(arr_pos[variant-1][i][0]!=arr_pos[variant-1][i-1][0])
      {myservo11.write(arr_pos[variant-1][i][0]);}
    if(arr_pos[variant-1][i][1]!=arr_pos[variant-1][i-1][1])
      {myservo12.write(arr_pos[variant-1][i][1]);}
    if(arr_pos[variant-1][i][2]!=arr_pos[variant-1][i-1][2])
      {myservo13.write(arr_pos[variant-1][i][2]);}
    if(arr_pos[variant-1][i][3]!=arr_pos[variant-1][i-1][3])
      {myservo14.write(arr_pos[variant-1][i][3]);}
    delay(200);
    }
 }
 
 // получить код переданный с ИК пульта
void get_ir_kod()
 {
 detachInterrupt(0);    // отключить прерывание 0
 if (irrecv.decode(&results))  
  { 
  //Serial.println(results.value);
  if (results.value > 0 && results.value < 0xFFFFFFFF) 
    { 
    ir_dt = results.value;
    if(ir_dt==EXT && ext==0) 
      {ir_kod = SLEEP;ext=1;} 
    else if(ext==1) 
      {
      if(ir_dt==FORWARD || ir_dt==BACK || ir_dt==CIRCLE_LEFT
         || ir_dt==CIRCLE_RIGHT || ir_dt==STOP || ir_dt==SLEEP
         || ir_dt==AWAKE || ir_dt==AUTO )
       ir_kod = ir_dt;
      } 
    else 
      ;
    //if (old_ir == ir_dt)
    //   {delay(500);ir_kod = ir_dt;}  //Пауза между короткими нажатиями
    //else 
    //   {delay(1000);ir_kod = ir_dt;}// Пауза после первого нажатия и удержания(перед повторами)
    //old_ir = ir_dt;
    /*ir_time2=millis();
    if (ir_time2-ir_time1>1000)
      {ir_kod = ir_dt;ir_time1=ir_time2;}
    else
      ir_kod = 0;*/
    //   {delay(500);ir_kod = ir_dt;}  //Пауза между короткими нажатиями
    //else 
    //   {delay(1000);ir_kod = ir_dt;}// Пауза после первого нажатия и удержания(перед повторами)
    //old_ir = ir_dt;
    } 
    irrecv.resume(); 
    //delay(1000); //пауза между повторами
  } 
  attachInterrupt(0, get_ir_kod, CHANGE); 
 }
