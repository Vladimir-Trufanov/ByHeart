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

#define  EXT 16          //1
#define  LOCAL 1040          //3

int local=0;
// состояние моторов робота
struct POZ    // структура для хранения статусов моторов
{
  int poz1;      // позиция для 1 мотора
  int poz2;      // позиция для 2 мотора
  int direction12;      // направление до поворота
};
// моторы
struct MOTOR    // структура для хранения номеров pin-ов, к которым подключены моторчики
{
  int in1;      // INPUT1
  int in2;      // INPUT2
  int enable;   // ENABLE1
};
// определяем порты, к которым подключены моторчики
MOTOR MOTOR1 = { 13, 12, 5 };
MOTOR MOTOR2 = { 7, 8, 6 };
// начальная позиция робота
// 1,2 мотор - выключены
POZ POZ12={7,7,7};
// массив возможных состояний моторов
// max down -> min down -> stop -> min up -> max up
int arrpoz[9][17]={
 // in1 первого мотора
 {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1},
 // in2 первого мотора
 {1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
 // скорости (enable1) первого мотора
 {250,230,210,190,170,150,130,0,130,150,170,190,210,230,250},
 // in3 второго мотора
 {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1},
 // in4 второго мотора
 {1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
 // скорости (enable2) второго мотора
 {250,230,210,190,170,150,130,0,130,150,170,190,210,230,250},
 // скорость++ 
 {0,-1,-1,-1,-1,-1,-1,0,1,1,1,1,1,1,0},
 // скорость-- 
 {-1,-1,-1,-1,-1,-1,-1,0,1,1,1,1,1,1,1},
 // кружение влево-вправо 
 {14,12,10,8,6,4,2,0,-2,-4,-6,-8,-10,-12,-14}
 };


void setup() 
 { 
  // последовательный порт 
  Serial.begin(9600); 
  // включить приемник 
  irrecv.enableIRIn(); 
  // прерывания для ИК
  ir_time1=0;ir_time2=0;
  attachInterrupt(0, get_ir_kod, FALLING); 
  // настраиваем выводы для моторов
  pinMode(MOTOR1.in1, OUTPUT); 
  pinMode(MOTOR1.in2, OUTPUT); 
  pinMode(MOTOR2.in1, OUTPUT);
  pinMode(MOTOR2.in2, OUTPUT);
  // начальная позиция - робот стоит
  go12(POZ12.poz1,POZ12.poz2);
 } 
  
void loop() 
 { 
 // обработка кода нажатия
 if(ir_kod>0)
   {
   ir_go(ir_kod);  
   //Serial.println(ir_kod);
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
  //attachInterrupt(0, get_ir_kod, CHANGE); 
  attachInterrupt(0, get_ir_kod, FALLING); 
 }
// переустановка моторов
void go12(int poz1,int poz2) 
 {
  digitalWrite(MOTOR1.in1, arrpoz[0][poz1]);
  digitalWrite(MOTOR1.in2, arrpoz[1][poz1]);
  analogWrite(MOTOR1.enable, arrpoz[2][poz1]);
  digitalWrite(MOTOR2.in1, arrpoz[3][poz2]);
  digitalWrite(MOTOR2.in2, arrpoz[4][poz2]);
  analogWrite(MOTOR2.enable, arrpoz[5][poz2]);
Serial.print(arrpoz[0][poz1]);Serial.print(" ");
Serial.print(arrpoz[1][poz1]);Serial.print(" ");
Serial.print(arrpoz[2][poz1]);Serial.print(" ");
Serial.print(arrpoz[3][poz2]);Serial.print(" ");
Serial.print(arrpoz[4][poz2]);Serial.print(" ");
Serial.print(arrpoz[5][poz2]);Serial.print("\n");
 }

// обработка кода нажатия
void ir_go(long kod) 
  { 
   Serial.print(kod);
   Serial.print("\n");
   if(kod!=EXT && local==1)
     return;
   switch(kod)
     {
     case LOCAL : // внешнее управление включить
       Serial.print("external\n");
        POZ12.direction12=8;
        POZ12.poz1=8;
        POZ12.poz2=8;
        go12(8,8);
       local=1;
       break;
     case EXT : // внешнее управление включить
       Serial.print("local\n");
       local=0;
       break;
     //case 1936 : // направление вперед
     case FORWARD : // направление вперед
        Serial.print("forward\n");
        POZ12.direction12=max(POZ12.direction12,8);
        POZ12.poz1=POZ12.direction12;
        POZ12.poz2=POZ12.direction12;
        go12(POZ12.poz1,POZ12.poz2);
       break;
     //case 3984 : // направление назад
     case BACK : // направление назад
        Serial.print("back\n");
        POZ12.direction12=min(POZ12.direction12,6);
        POZ12.poz1=POZ12.direction12;
        POZ12.poz2=POZ12.direction12;
        go12(POZ12.poz1,POZ12.poz2);
        break;
      //case 144 : // скорость++
      case SPEED_UP : // скорость++
        Serial.print("speed++\n");
        POZ12.direction12=POZ12.direction12+arrpoz[6][POZ12.direction12];
        POZ12.poz1=POZ12.direction12;
        POZ12.poz2=POZ12.direction12;
        go12(POZ12.poz1,POZ12.poz2);
        break;
      //case 2192 :  // скорость--
      case SPEED_DOWN :  // скорость--
       Serial.print("speed--\n");
        POZ12.direction12=POZ12.direction12-arrpoz[7][POZ12.direction12];
        POZ12.poz1=POZ12.direction12;
        POZ12.poz2=POZ12.direction12;
        go12(POZ12.poz1,POZ12.poz2);
        break;
      //case 3472 : // влево
      case LEFT : // влево
        Serial.print("left\n");     
        if(POZ12.direction12>6)
          {
          POZ12.poz1=POZ12.poz1-1;POZ12.poz1=max(POZ12.poz1,0);
          POZ12.poz2=POZ12.direction12;
          }
        else
          {
          POZ12.poz1=POZ12.poz1+1;POZ12.poz1=min(POZ12.poz1,14);
          POZ12.poz2=POZ12.direction12;
          }
        go12(POZ12.poz1,POZ12.poz2);
       break;
     //case 1424 : // вправо
     case RIGHT : // вправо
        Serial.print("right\n");
        if(POZ12.direction12>6)
          {
          POZ12.poz2=POZ12.poz2-1;POZ12.poz2=max(POZ12.poz2,0);
          POZ12.poz1=POZ12.direction12;
          }
        else
          {
          POZ12.poz2=POZ12.poz2+1;POZ12.poz2=min(POZ12.poz2,14);
          POZ12.poz1=POZ12.direction12;
          }
        go12(POZ12.poz1,POZ12.poz2);
       break;
     //case 1168 : // кружение вправо
     case CIRCLE_RIGHT : // кружение вправо
        Serial.print("circle_right\n");
        POZ12.poz1=POZ12.direction12;
        POZ12.poz2=POZ12.direction12+arrpoz[8][POZ12.direction12];
        go12(POZ12.poz1,POZ12.poz2);
        break;
     //case 3216 : // кружение влево
     case CIRCLE_LEFT : // кружение влево
        Serial.print("circle_left\n");
        POZ12.poz1=POZ12.direction12+arrpoz[8][POZ12.direction12];
        POZ12.poz2=POZ12.direction12;
        go12(POZ12.poz1,POZ12.poz2);
        break;
     //case 2320 : // стоп
     case STOP : // стоп
        Serial.print("stop\n");
        POZ12.poz1=7;
        POZ12.poz2=7;
        POZ12.direction12=7;
        go12(POZ12.poz1,POZ12.poz2);
        break;
     default:
        break;
     }
  } 
