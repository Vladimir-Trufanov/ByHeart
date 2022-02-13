#include <TVout.h>
#include <fontALL.h>
#include "MyBitmap1.h"
#include "TVOlogo.h"

TVout TV;
int pmenu=1;

/////////////////////////////////////////////
//  переменные для игры 1
int MAX_X=31;
int MAX_Y=13;
// структура данных игры
struct GAME  // структура для данных игры
{
  int xk;      // координата x(/4) игрока
  int yk;      // координата y(/6) игрока
  int tekCursor; // текущее значение курсора
  int blinkCursor; // текущее состояние блинка курсора
  int vblink;  // скорость blink в vk 
  
  long vk;      // скорость движения игрока - проверка входов A0,A1
  long vo_10;     // скорость изменения цифры игрока 
  long vo_11;     // скорость появления цифр 
  long vo_12;     // скорость движения цифр 
  
  int count_objects; //кол-во объектов на поле
  int level;   // уровень игры  
  int balls;      // кол-во баллов
};
// создать объект
GAME GAME1 = { 0,0,0,1,5, 50,5000,2000,1000, 0,1,100 };

int MAX_OBJ=30;
int FIGURA[30][3]={{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
                  {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
                  {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
                  {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}, 
                  {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
                  {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}
                  };
long time11,time12,time13,time14;

/////////////////////////////////////////////
// переменные для игры 2 (pacman)

// структура данных игры
struct GAME2  // структура для данных игры
{
  int xk;      // координата x знакоместа игрока
  int yk;      // координата y знакоместа игрока
  int blink; // текущее состояние блинка курсора
  int x[4];  // координаты x знакомест врагов
  int y[4];  // координаты y знакомест врагов
  
  long vk;      // скорость движения игрока
  int  zk;         // текущее направление движения игрока
                // 0 - стоит, 1-вверх, 2-вниз, 3-влево, 4-вправо
  long v;      // скорость движения врагов
  int  z[4];         // текущие направления движения врагов
  
  int count;   // количество крошек
  int lives;   // ставшееся количество жизней на данном уровне 
  int level;   // текущий уровень
};
// создать объект
GAME2 GAME21 = { 10,10,1,{0.0,0,0},{0.0,0,0}, 500,0, 1000,{0.0,0,0}, 50,5,1 };

/*byte FIELD[21*16]={
  '1','5','5','5','5','5','5','5','5','5','5','5','5','5','5','5','5','5','5','5','2',
  '6',' ',' ',' ',' ','6',' ',' ',' ',' ','6',' ','6',' ',' ',' ',' ',' ',' ',' ','6',
  '6',' ','6','5',' ','6',' ','6','5',' ',' ',' ',' ',' ',' ','5',' ','5','5',' ','6',
  '6',' ','6',' ',' ',' ',' ',' ','6',' ','5','5','5',' ','5','6',' ',' ',' ',' ','6',
  '6',' ',' ',' ','6',' ','6',' ',' ',' ',' ',' ','6',' ','5',' ',' ',' ','5',' ','6',
  '6','5','5',' ','6',' ','5','5',' ','5','5',' ',' ',' ',' ',' ','6',' ','5',' ','6',
  ' ',' ',' ',' ',' ',' ',' ',' ',' ','6',' ',' ','5','5','6',' ','6',' ',' ',' ',' ',
  '6','5','5',' ','5',' ','5','5',' ',' ','6',' ',' ',' ','5',' ','5',' ','5','5','6',
  '6',' ',' ',' ',' ',' ',' ','5','5',' ','5',' ','6',' ',' ',' ',' ',' ',' ',' ','6',
  '6',' ','6','6',' ','6',' ',' ',' ',' ',' ',' ','6',' ',' ','5',' ','5','6',' ','6',
  '6',' ',' ','6',' ','6','5','5',' ','6','5',' ','5','5',' ','5',' ',' ',' ',' ','6',
  '6','5',' ','6',' ',' ',' ',' ',' ',' ',' ',' ',' ','6',' ','6',' ','6','6',' ','6',
  '6',' ',' ',' ',' ','6',' ','6',' ','6',' ',' ','6','6',' ',' ',' ',' ','6',' ','6',
  '6',' ','5','5','5','5',' ','6',' ','6','5',' ','6',' ',' ','6','5',' ',' ',' ','6',
  '6',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','5','6',' ',' ','6',' ','6',
  '3','5','5','5','5','5','5','5','5','5','5','5','5','5','5','5','5','5','5','5','4'
   };*/
   
   static byte FIELD[126]={
   49, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 50,
   54, 0 , 0 , 0 , 0 , 54, 0 , 0 , 0 , 0 , 54, 0 , 54, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 54,
   54, 0 , 54, 53, 0 , 54, 0 , 54, 53, 0 , 0 , 0 , 0 , 0 , 0 , 53, 0 , 53, 53, 0 , 54,
   54, 0 , 54, 0 , 0 , 0 , 0 , 0 , 54, 0 , 53, 53, 53, 0 , 53, 54, 0 , 0 , 0 , 0 , 54,
   54, 0 , 0 , 0 , 54, 0 , 54, 0 , 0 , 0 , 0 , 0 , 54, 0 , 53, 0 , 0 , 0 , 53, 0 , 54,
   /*54, 53, 53, 0 , 54, 0 , 53, 53, 0 , 53, 53, 0 , 0 , 0 , 0 , 0 , 54, 0 , 53, 0 , 54,
   0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 54, 0 , 0 , 53, 53, 54, 0 , 54, 0 , 0 , 0 , 0 ,
   54, 53, 53, 0 , 53, 0 , 53, 53, 0 , 0 , 54, 0 , 0 , 0 , 53, 0 , 53, 0 , 53, 53, 54,
   54, 0 , 0 , 0 , 0 , 0 , 0 , 53, 53, 0 , 53, 0 , 54, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 54,
   54, 0 , 54, 54, 0 , 54, 0 , 0 , 0 , 0 , 0 , 0 , 54, 0 , 0 , 53, 0 , 53, 54, 0 , 54,
   54, 0 , 0 , 54, 0 , 54, 53, 53, 0 , 54, 53, 0 , 53, 53, 0 , 53, 0 , 0 , 0 , 0 , 54,
   54, 53, 0 , 54, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 54, 0 , 54, 0 , 54, 54, 0 , 54,
   54, 0 , 0 , 0 , 0 , 54, 0 , 54, 0 , 54, 0 , 0 , 54, 54, 0 , 0 , 0 , 0 , 54, 0 , 54,
   54, 0 , 53, 53, 53, 53, 0 , 54, 0 , 54, 53, 0 , 54, 0 , 0 , 54, 53, 0 , 0 , 0 , 54,
   54, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 53, 54, 0 , 0 , 54, 0 , 54,*/
   51, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 52
   };
                  // шрифт font6x6my
                  // '1' - левый верхний уголок, '2' - правый верхний уголок,
                  // '3' - левый нижний уголок,'4' - правый нижний уголок,
                  // '5' - горизонталь,'6' - вертикаль, 
                  // '7' - горизонталь вниз,'8' - горизонталь вверх, 
                  // '9' - вертикаль влево,'0' - вертикаль вправо,
                  // '+' - крест,
                  // ' ' - пустое место
                  // '!' - добыча, '"' - приз, '#' - враг
                  // '$','%' - игрок
                  

///////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////

void setup() {
  TV.begin(PAL,128,96);
  // вывод логотипа
  TV.clear_screen();
  TV.bitmap(0,0,MyBitmap1);
  TV.bitmap(20,20,TVOlogo);
  TV.select_font(font8x8);
  TV.println(40,60,"GAMES ");
  TV.select_font(font4x6my);
  TV.println(40,80,"V.Petin, 2013");
  
  TV.tone(245,200);TV.delay(400);
  TV.tone(545,300);TV.delay(500);
  TV.tone(245,200);TV.delay(200);
  
  pinMode(12,INPUT);
  while(digitalRead(12)==LOW);
  TV.tone(345,200);TV.delay(400);
  TV.tone(680,300);
  //TV.delay(1000);
  TV.clear_screen();
  // начальная инициализация поля - обнуление  
  // полоса табло
  //TV.draw_line(0,90,128,90,WHITE);
  //TV.draw_rect(0,89,128,6,WHITE,WHITE);
  
  //change_balls(0);
}

void loop() {
   switch(menu(pmenu))
     {
     case 1:start_game();
            while(game1()>0);
            break;
     case 2:  TV.select_font(font6x6my);
            ini_game2();
            while(game2()>0);
            TV.select_font(font4x6my);
            break;
     default:
            break; 
     }
  
  }
  
//*****************************************
//**  
//***************************************
int menu(int poz)
  {
   TV.clear_screen();
   pmenu=max(poz,1);
   int pmenu1=pmenu;
   TV.println(60,30,"Game 1");
   TV.println(60,50,"PacMan");
   TV.println(60,70,"------"); 
   TV.draw_rect(50,5+20*pmenu,40,10,WHITE,INVERT); 
   TV.delay(500);
   while(digitalRead(12)==LOW)
     {
     if(analogRead(A1)<100)
        pmenu=max(pmenu+1,1);
     else if(analogRead(A1)>900)
        pmenu=min(pmenu-1,3);
     else ;
     if(pmenu1!=pmenu)
       {
       TV.delay(500);
       TV.draw_rect(50,5+20*pmenu1,40,10,BLACK,INVERT); 
       TV.draw_rect(50,5+20*pmenu,40,10,WHITE,INVERT); 
       pmenu1=pmenu; 
       }
     }
   return pmenu;  
 }
//**********************************************
//********* Игра 2 - PacMan
//******************************
int ini_game2()
  {
  TV.clear_screen();
  for(int x=0;x<21;x++)
    {
    for(int y=0;y<2;y++)
      {
      //TV.set_cursor(x*6,y*6);
      //if(FIELD[y*21+x]==53)     
         //TV.print(FIELD[y*21+x]);
         TV.print(byte(50));
      }
    }  
  }

int game2()
  {
  delay(5000);  
  return 0;
  }
//**********************************************
//********* Игра 1 - Арифметический ловец
//******************************
int game1()
  {
  //while(GAME1.balls>0 && GAME1.level<6)
   //{  
   long time2=millis();
   //TV.delay(GAME1.xk);
   if(time2-time11>GAME1.vk)
     {set_iam();
     collision();
     time11=time2;
     }
   if(time2-time12>GAME1.vo_12)
     {go_object();time12=time2;}
   if(time2-time13>GAME1.vo_11)
     {set_new_object();time13=time2;}
   if(time2-time14>GAME1.vo_10)
     {set_new_cursor();time14=time2;}
   TV.delay_frame(10);  
   //}
  if(GAME1.balls<0)
     return 0;
  else if(GAME1.level>5)
     return 0;
  else
     return 1;   
  }
//****************** появление нового объекта 
void set_new_object()
  {
  int null_index=0;
  if(GAME1.count_objects<MAX_OBJ)
    {
    for(int i=0;i<MAX_OBJ;i++)
      {
      if(FIGURA[i][0]==0)
        {null_index=i;break;}
      }
    FIGURA[null_index][0]=random(1,9); 
    FIGURA[null_index][1]=random(0,MAX_X); 
    FIGURA[null_index][2]=0; 
    // вывод на доску
    TV.set_cursor(FIGURA[null_index][1]*4,0);
    TV.print(FIGURA[null_index][0]);    
 
    GAME1.count_objects++;
   } 
  }
//****************** движение объекта 
void go_object()
  {
  for(int i=0;i<MAX_OBJ;i++)
    {
    if(FIGURA[i][0]>0) 
      {
      TV.set_cursor(FIGURA[i][1]*4,FIGURA[i][2]*6);
      TV.print(" ");    
      if(FIGURA[i][2]<MAX_Y)
        {
        FIGURA[i][2]++;
        TV.set_cursor(FIGURA[i][1]*4,FIGURA[i][2]*6);
        //TV.print("V");          
        TV.print(FIGURA[i][0]); 
        }
      else
        {
        TV.tone(294,200);
        change_balls(FIGURA[i][0]*(-1)); 
        FIGURA[i][0]=0;
        GAME1.count_objects--;
         } 
      }
    } 
  }
//****************** проверка столкновения
void collision()
  {
  for(int i=0;i<MAX_OBJ;i++)
    {
    if(FIGURA[i][0]>0) 
      {
      if(FIGURA[i][1]==GAME1.xk && FIGURA[i][2]==GAME1.yk)
        {
        TV.tone(740,200);
        if(FIGURA[i][0]==GAME1.tekCursor)
          change_balls(GAME1.tekCursor*GAME1.tekCursor);
        else if(FIGURA[i][0]>GAME1.tekCursor && GAME1.level>3)
          change_balls(FIGURA[i][0]*(-1));
        else 
          change_balls(FIGURA[i][0]+GAME1.tekCursor);        
        FIGURA[i][0]=0;
        GAME1.count_objects--;
        } 
      }
    } 
  }
//****************** установка нового положения курсора
void set_iam()
  {
  TV.set_cursor(min(123,GAME1.xk*4),min(78,GAME1.yk*6));
  TV.print(" ");
    
  GAME1.xk=map(analogRead(A0), 0, 1024, 0, 128);
  GAME1.xk=GAME1.xk/4;
  GAME1.yk=map(analogRead(A1), 0, 1024, 96, 0);
  GAME1.yk=GAME1.yk/6;
  GAME1.vblink--;
  if(GAME1.vblink<0)
    {
    GAME1.blinkCursor=1-GAME1.blinkCursor; 
    GAME1.vblink=5+GAME1.blinkCursor*5;
    }
  TV.set_cursor(min(123,GAME1.xk*4),min(78,GAME1.yk*6));
  if(GAME1.blinkCursor==1)  
    TV.print(GAME1.tekCursor);
  else  
    TV.print("!");   
  }
//****************** установка нового вида курсора
void set_new_cursor()
  {
  GAME1.tekCursor=random(0,10);
  }
//****************** изменение набранных балов
void change_balls(int ball)
  {
  
  GAME1.balls=GAME1.balls+ball;
  if(GAME1.balls<0)
     ;//start_game();
  if(GAME1.balls>(GAME1.level+1)*100) 
    new_level(GAME1.level); 
  set_data_tablo();  
  } 
//****************** изменение уровня игры
void new_level(int tek_level)
  {
  GAME1.level++;
  GAME1.vo_10=5000; 
  GAME1.vo_11=2000-(GAME1.level-1)*100;  
  GAME1.vo_12=1000-(GAME1.level-1)*100;   
  } 
//****************** вывод данных на табло
void set_data_tablo()
  {
  TV.print(20,85," balls=    ");
  TV.print(70,85," level=   ");
  TV.print(48,85,GAME1.balls);
  TV.print(98,85,GAME1.level);
  }
//****************** обнуление данных перед новой игрой
void start_game()
  {
  // игра закончена - очистить экран
  // обнуление массива FIGURA 
  for(int i1=0;i1<30;i1++)
    {
    for(int i2=0;i2<3;i2++)
      FIGURA[i1][i2]=0;
    }
  // установка нач. значений игры
  GAME1.xk=0;
  GAME1.yk=0; 
  GAME1.tekCursor=0; 
  GAME1.vk=50; 
  GAME1.vo_10=5000; 
  GAME1.vo_11=2000;  
  GAME1.vo_12=1000;   
  GAME1.count_objects=0;
  GAME1.level=1; 
  GAME1.balls=100; 
  //
  TV.clear_screen();
  TV.delay(1000);
  TV.draw_line(0,84,128,84,WHITE);
  
  change_balls(0);
  }
