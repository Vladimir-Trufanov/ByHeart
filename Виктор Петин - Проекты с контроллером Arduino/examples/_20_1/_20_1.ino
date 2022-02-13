// подключение библиотеки
#include <IRremote.h> 
//вход ИК приемника
int RECV_PIN = 2;  
IRrecv irrecv(RECV_PIN); 
decode_results results; 
unsigned long ir_dt, old_ir;
long ir_kod;
unsigned long ir_time1, ir_time2;
// коды клавиш ИК пульта (marmitek)
#define FORWARD 1936
#define BACK  3984
#define SPEED_UP 144       //ch+
#define SPEED_DOWN 2192    //ch-
#define LEFT 3472
#define RIGHT 1424
#define CIRCLE_LEFT 3216   //vol+
#define CIRCLE_RIGHT 1168  //vol-
#define STOP 2320          //0


void setup() 
 { 
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
 // обработка кода нажатия
 if(ir_kod>0)
   {
   Serial.println(ir_kod);
   ir_go(ir_kod);  
   ir_kod=0;  
   } 
      
 }

// получить код переданный с ИК пульта
void get_ir_kod()
 {
 detachInterrupt(0);    // отключить прерывание 0
 if (irrecv.decode(&results))  
  { 
  if (results.value > 0 && results.value < 0xFFFFFFFF) 
    { 
    ir_dt = results.value; 
    ir_time2=millis();
    if (ir_time2-ir_time1>1000)
      {ir_kod = ir_dt;ir_time1=ir_time2;}
    else
      ir_kod = 0;
    } 
    irrecv.resume(); 
  } 
  attachInterrupt(0, get_ir_kod, CHANGE); 
 }
void ir_go(long kod)
 {
   switch(kod)
     {
     case FORWARD : // направление вперед
        Serial.print("forward\n");
        break;
     case BACK :    // направление назад
        Serial.print("back\n");
        break;
      case SPEED_UP : // скорость++
        Serial.print("speed++\n");
        break;
      case SPEED_DOWN :  // скорость--
        Serial.print("speed--\n");
        break;
      case LEFT : // влево
        Serial.print("left\n");     
        break;
     case RIGHT : // вправо
        Serial.print("right\n");
       break;
     case CIRCLE_RIGHT : // кружение вправо
        Serial.print("circle_right\n");
        break;
     case CIRCLE_LEFT : // кружение влево
        Serial.print("circle_left\n");
        break;
     case STOP : // стоп
        Serial.print("stop\n");
        break;
     default:
        break;
     }
   
 }
 
