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
MOTOR MOTOR1 = { 4, 5, 6 };
MOTOR MOTOR2 = { 7, 8, 9 };
// начальная позиция робота
// 1,2 мотор - выключены
POZ POZ12={5,5,5};
// массив возможных состояний моторов
// max down -> min down -> stop -> min up -> max up
int arrpoz[9][11]={
 // in1 первого мотора
 {0,0,0,0,0,0,1,1,1,1,1},
 // in2 первого мотора
 {1,1,1,1,1,0,0,0,0,0,0},
 // скорости (enable1) первого мотора
 {250,230,210,190,170,0,170,190,210,230,250},
 // in3 второго мотора
 {0,0,0,0,0,0,1,1,1,1,1},
 // in4 второго мотора
 {1,1,1,1,1,0,0,0,0,0,0},
 // скорости (enable2) второго мотора
 {250,230,210,190,170,0,170,190,210,230,250},
 // скорость++ 
 {0,-1,-1,-1,-1,0,1,1,1,1,0},
 // скорость-- 
 {0,-1,-1,-1,-1,0,1,1,1,1,0},
 // кружение влево-вправо 
 {10,8,6,4,2,0,-2,-4,-6,-8,-10}
 };

//************** bluetootrh
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // указываем пины rx и tx соответственно
// rx-tx hc05 и tx-rx-rx hc05 соответственно
// для перевода строки в число
int pows[]={1,10,100,1000,10000};
int nums[10];
int index_nums=0;
int number=0;

void setup() 
 { 
  // последовательный порт 
  pinMode(2,INPUT);
  pinMode(3,OUTPUT);
  Serial.begin(38400);
  mySerial.begin(38400);
  Serial.println("38400");
  Serial.println("ok");
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
  while(mySerial.available())
  {
    int c = mySerial.read(); // читаем из software-порта
    if(c=='\n')
      {convert_to_number();
       index_nums=0;number=0;
       break;}
    else if(48<=int(c) && int(c)<=57)
      {
      nums[index_nums]=int(c)-48;
      index_nums++;
      }
    else
      {index_nums=0;number=0;
      Serial.println("error");
      break;}  
    }
      
 }

// получить число из массива цифр
void convert_to_number()
 {
 for(int i=index_nums;i>0;i--)
   //{number=number+nums[i-1]*10*(index_nums-i);} 
   {number=number+nums[i-1]*pows[index_nums-i];
   } 
 Serial.println(number,DEC);
 ir_go(number); 
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
        POZ12.direction12=10;
        POZ12.poz1=10;
        POZ12.poz2=10;
        go12(10,10);
       local=1;
       break;
     case EXT : // внешнее управление включить
       Serial.print("local\n");
       local=0;
       break;
     //case 1936 : // направление вперед
     case FORWARD : // направление вперед
        Serial.print("forward\n");
        POZ12.direction12=max(POZ12.direction12,10);
        POZ12.poz1=POZ12.direction12;
        POZ12.poz2=POZ12.direction12;
        go12(POZ12.poz1,POZ12.poz2);
       break;
     //case 3984 : // направление назад
     case BACK : // направление назад
        Serial.print("back\n");
        POZ12.direction12=min(POZ12.direction12,0);
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
        //POZ12.poz1=POZ12.direction12;
        //POZ12.poz2=POZ12.direction12+arrpoz[8][POZ12.direction12];
     POZ12.direction12=10;
     POZ12.poz1=POZ12.direction12;
     POZ12.poz2=POZ12.direction12+arrpoz[8][POZ12.direction12];
        go12(POZ12.poz1,POZ12.poz2);
        break;
     //case 3216 : // кружение влево
     case CIRCLE_LEFT : // кружение влево
        Serial.print("circle_left\n");
        //POZ12.poz1=POZ12.direction12+arrpoz[8][POZ12.direction12];
        //POZ12.poz2=POZ12.direction12;
     POZ12.direction12=0;
     POZ12.poz1=POZ12.direction12+arrpoz[8][POZ12.direction12];
     POZ12.poz2=POZ12.direction12;
        go12(POZ12.poz1,POZ12.poz2);
        break;
     //case 2320 : // стоп
     case STOP : // стоп
        Serial.print("stop\n");
        POZ12.poz1=5;
        POZ12.poz2=5;
        POZ12.direction12=5;
        go12(POZ12.poz1,POZ12.poz2);
        break;
     default:
        break;
     }
  } 
