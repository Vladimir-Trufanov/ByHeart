// Пример из книги
// Редактор текста
// Ввод - клавиатура PS/2
// Вывод - LCD WinstarWH1604

#include <ps2.h>
// подключение библиотеки LiquidCrystalRus
#include <LiquidCrystal.h>
#include <LiquidCrystalRus.h>
// 9 - RS, 8 - Enable, 7-4 - D4-D7
LiquidCrystalRus lcd(9, 8, 7, 6, 5, 4);

/*
 * Pin 5 is the ps2 data pin, pin 6 is the clock pin
 * Feel free to use whatever pins are convenient.
 */
#define CAPS 0x58
#define NUM 0x77
#define SCROLL 0x7E
#define ESC 0x76
#define F10 0x9
#define ALT 0x11
#define CTRL 0x14
#define L_SHIFT 0x12
#define R_SHIFT 0x59

#define LEFT 0x6B
#define RIGHT 0x74
#define UP 0x75
#define DOWN 0x72
#define PGUP 0x7D
#define PGDOWN 0x7A
#define END 0x69
#define HOME 0x6C
#define NUM5 0x73
#define BACKSPACE 0x66
#define DELETE 0x71
#define INSERT 0x70

PS2 kbd(3, 2);
byte up_down[256];
unsigned char  table1[1024]={
   //0
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','`',' ',
   ' ',' ',' ',' ',' ','q','1',' ',' ',' ','z','s','a','w','2',' ',
   ' ','c','x','d','e','4','3',' ',' ',' ','v','f','t','r','5',' ',
   ' ','n','b','h','g','y','6',' ',' ',' ','m','j','u','7','8',' ',
   ' ',',','k','i','o','0','9',' ',' ','.','/','l',';','p','-',' ',
   ' ',' ','\'',' ','[','=',' ',' ',' ',' ',' ',' ',']','\\',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ','1',' ','4','7',' ',' ',' ',
   '0',' ','2','5','6','8',' ',' ',' ','+','3','-','*','9',' ',' ',
   //0x7f
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','`',' ',
   ' ',' ',' ',' ',' ','Q','1',' ',' ',' ','Z','S','A','W','2',' ',
   ' ','C','X','D','E','4','3',' ',' ',' ','V','F','T','R','5',' ',
   ' ','N','B','H','G','Y','6',' ',' ',' ','M','J','U','7','8',' ',
   ' ','<','K','I','O','0','9',' ',' ','.','/','L',';','P','-',' ',
   ' ',' ','\'',' ','[','=',' ',' ',' ',' ',' ',' ',']','\\',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ','1',' ','4','7',' ',' ',' ',
   '0',' ','2','5','6','8',' ',' ',' ','+','3','-','*','9',' ',' ',
   //0xff
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','~',' ',
   ' ',' ',' ',' ',' ','Q','!',' ',' ',' ','Z','S','A','W','@',' ',
   ' ','C','X','D','E','$','#',' ',' ',' ','V','F','T','R','%',' ',
   ' ','N','B','H','G','Y','^',' ',' ',' ','M','J','U','&','*',' ',
   ' ','<','K','I','O','(',')',' ',' ','.','?','L',':','P','_',' ',
   ' ',' ','"',' ','{','+',' ',' ',' ',' ',' ',' ','}','|',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ','1',' ','4','7',' ',' ',' ',
   '0',' ','2','5','6','8',' ',' ',' ','+','3','-','*','9',' ',' ',
   //0x17f
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','~',' ',
   ' ',' ',' ',' ',' ','q','!',' ',' ',' ','z','s','a','w','@',' ',
   ' ','c','x','d','e','$','#',' ',' ',' ','v','f','t','r','%',' ',
   ' ','n','b','h','g','y','^',' ',' ',' ','m','j','u','&','*',' ',
   ' ','<','k','i','o','(',')',' ',' ','.','?','l',':','p','_',' ',
   ' ',' ','"',' ','{','+',' ',' ',' ',' ',' ',' ','}','|',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ','1',' ','4','7',' ',' ',' ',
   '0',' ','2','5','6','8',' ',' ',' ','+','3','-','*','9',' ',' ',
   //0x1ff
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','ё',' ',
   ' ',' ',' ',' ',' ','й','1',' ',' ',' ','я','ы','ф','ц','2',' ',
   ' ','с','ч','в','у','4','3',' ',' ',' ','м','а','е','к','5',' ',
   ' ','т','и','р','п','н','6',' ',' ',' ','ь','о','г','7','8',' ',
   ' ','б','л','ш','щ','0','9',' ',' ','.','.','д','ж','з','-',' ',
   ' ',' ','э',' ','х','=',' ',' ',' ',' ',' ',' ','ъ','\\',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ','1',' ','4','7',' ',' ',' ',
   '0',' ','2','5','6','8',' ',' ',' ','+','3','-','*','9',' ',' ',
   //0x27f
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','ё',' ',
   ' ',' ',' ',' ',' ','Й','1',' ',' ',' ','Я','Ы','Ф','Ц','2',' ',
   ' ','С','Ч','В','У','4','3',' ',' ',' ','М','А','Е','К','5',' ',
   ' ','Т','И','Р','П','Н','6',' ',' ',' ','Ь','О','Г','7','8',' ',
   ' ','Б','Л','Ш','Щ','0','9',' ',' ','.',',','Д','Ж','З','-',' ',
   ' ',' ','Э',' ','Х','=',' ',' ',' ',' ',' ',' ','Ъ','\\',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ','1',' ','4','7',' ',' ',' ',
   '0',' ','2','5','6','8',' ',' ',' ','+','3','-','*','9',' ',' ',
   //0x2ff
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','~',' ',
   ' ',' ',' ',' ',' ','Q','!',' ',' ',' ','Z','S','A','W','@',' ',
   ' ','C','X','D','E','$','#',' ',' ',' ','V','F','T','R','%',' ',
   ' ','N','B','H','G','Y','^',' ',' ',' ','M','J','U','&','*',' ',
   ' ','<','K','I','O','(',')',' ',' ','.','?','L',':','P','_',' ',
   ' ',' ','"',' ','{','+',' ',' ',' ',' ',' ',' ','}','|',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ','1',' ','4','7',' ',' ',' ',
   '0',' ','2','5','6','8',' ',' ',' ','+','3','-','*','9',' ',' ',
   //0x31f
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','~',' ',
   ' ',' ',' ',' ',' ','q','!',' ',' ',' ','z','s','a','w','@',' ',
   ' ','c','x','d','e','$','#',' ',' ',' ','v','f','t','r','%',' ',
   ' ','n','b','h','g','y','^',' ',' ',' ','m','j','u','&','*',' ',
   ' ','<','k','i','o','(',')',' ',' ','.','?','l',':','p','_',' ',
   ' ',' ','"',' ','{','+',' ',' ',' ',' ',' ',' ','}','|',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ','1',' ','4','7',' ',' ',' ',
   '0',' ','2','5','6','8',' ',' ',' ','+','3','-','*','9',' ',' '
   
   };
byte f0=0;
byte e0=0;
byte leds=0;
byte lang=0;
byte ins=0;
byte l_shift=0;
byte r_shift=0;
byte alt=0;

int lcd_cols=16;
int lcd_rows=4;
char txt_buffer[100];
int txt_end_pos=0;
int txt_tek_pos=0;
int offset=0;
//int addr;

void kbd_init()
{
  char ack;
  Serial.println("write");
  kbd.write(0xff);  // send reset code
  Serial.println("writeok");
  Serial.println("read");
  ack = kbd.read();  // byte, kbd does self test
  Serial.println("readok");
  Serial.println("read");
  ack = kbd.read();  // another ack when self test is done
  Serial.println("readok");
}
void set_leds()
 {
  kbd.write(0xED);  // send reset code
  kbd.write(leds);  // send reset code
 }
void insert()
 {
 ins=1-ins;
 if(ins==1) lcd.blink();
 else lcd.noBlink();
 }
void pos_cursor(byte change)
 {
 switch(change)
  {
  case LEFT: new_cursor(-1);
            Serial.println("left");
       break; 
  case RIGHT: new_cursor(1); 
            Serial.println("right");
       break; 
  case UP:  new_cursor(lcd_cols*(-1));
           Serial.println("up");
   break; 
   case DOWN:new_cursor(lcd_cols); 
           Serial.println("down");
      break; 
   case PGUP: Serial.println("pgup");
      break; 
   case PGDOWN: Serial.println("pgdn");
      break; 
   case HOME: Serial.println("home");
      break; 
   case END: Serial.println("end");
      break; 
   default: break;
  }
}

void get_char()
 {
 unsigned char code;int ledsb=0;
 detachInterrupt(1);    // отключить прерывание 0
 code = kbd.read();
 Serial.print("code=");Serial.println(code,HEX);
 switch(code)
  {
  case 0: break;
  case 0xF0: f0=1; break;
  case 0xFA: break;
  case 0xE0: e0=1-e0;Serial.print("e0=**=");Serial.println(e0,HEX);break;
  case ALT:  if(f0==0)alt=1-alt; else f0=0; break; //
  case NUM: //NumLock
             if(bitRead(leds,1)==1 && f0<1) 
               {bitClear(leds,1);set_leds();}
             else if(bitRead(leds,1)==0 && f0<1) 
               {bitSet(leds,1);set_leds();} 
             else f0=0; 
       break;
  case CAPS: // CapsLock
             if(bitRead(leds,2)==1 && f0<1) 
               {bitClear(leds,2);set_leds();}
             else if(bitRead(leds,2)==0 && f0<1) 
               {bitSet(leds,2);set_leds();} 
             else f0=0; 
       break;
  case SCROLL: // ScrollLock
             if(bitRead(leds,0)==1 && f0<1) 
               {bitClear(leds,0);set_leds();lang=0;}
             else if(bitRead(leds,0)==0 && f0<1) 
               {bitSet(leds,0);set_leds();lang=1;} 
             else f0=0; 
       break;
  // l_shift, r_shift , delete, backspace
  case L_SHIFT:  if(e0==1){e0=0;break;} 
             if(f0==0) l_shift=1; else {l_shift=0;f0=0;} 
             break;
  case R_SHIFT: if(f0==0) r_shift=1; else {r_shift=0;f0=0;} 
             break;
  case DELETE: if(f0==0){del_from_buffer();}
                  else(f0=0);
                  Serial.println("delete");
              break;
  case BACKSPACE: if(f0==0){delete_from_buffer();}
                  else(f0=0);
                  Serial.println("backspace");
              break;
  // Insert,Delete,Home,End,PgUp,PgDown,L,R,U,D
  case LEFT: Serial.print("e0==left==");Serial.println(e0,HEX);
             if(e0==1)
               {pos_cursor(LEFT); break;} 
             else if(bitRead(leds,1)==0)
              {if(f0<1)pos_cursor(LEFT);else f0=0; break;}
  case RIGHT:  if(e0==1)
               {pos_cursor(RIGHT); break;} 
              if(bitRead(leds,1)==0)
               {if(f0<1)pos_cursor(RIGHT);else f0=0; break;}
  case UP: if(e0==1)
               {pos_cursor(UP); break;} 
              if(bitRead(leds,1)==0)
              {if(f0<1)pos_cursor(UP);else f0=0; break;}
  case DOWN: if(e0==1)
               {pos_cursor(DOWN); break;} 
              if(bitRead(leds,1)==0)
              {if(f0<1)pos_cursor(DOWN);else f0=0; break;}
  case PGUP: if(e0==1)
               {pos_cursor(PGUP); break;} 
              if(bitRead(leds,1)==0)
              {if(f0<1)pos_cursor(PGUP);else f0=0; break;}
  case PGDOWN: if(e0==1)
               {pos_cursor(PGDOWN); break;} 
              if(bitRead(leds,1)==0)
              {if(f0<1)pos_cursor(PGDOWN);else f0=0; break;}
  case HOME: if(e0==1)
               {pos_cursor(HOME); break;} 
              if(bitRead(leds,1)==0)
              {if(f0<1)pos_cursor(HOME);else f0=0; break;}
  case END: if(e0==1)
               {pos_cursor(END); break;} 
              if(bitRead(leds,1)==0)
              {if(f0<1)pos_cursor(END);else f0=0; break;}
  case NUM5: if(bitRead(leds,1)==0)
              {if(f0<1);else f0=0; break;}
  case INSERT: if(e0==1)
               {insert(); break;} 
              if(bitRead(leds,1)==0)
              {if(f0<1)insert();else f0=0;break;}
             
  //           
  default: if(f0==1)
            {f0=0;up_down[code]=0;
             Serial.print("down-");Serial.println(code,HEX);}
           else  
            {up_down[code]=1;
            int addr=bitRead(leds,2)*128+min(1,l_shift+r_shift)*256+alt*512+code;
            //int addr=bitRead(leds,2)*128+code;
            //Serial.print("addr=");Serial.print(addr,HEX);
            //Serial.print("  code=");Serial.println(table1[addr]);
            ////lcd.write(table1[addr]);
            add_buffer(table1[addr]);
            //Serial.print("up-");Serial.println(table1[addr]);
            }
           break; 
  }
 //Serial.println(code,HEX);
 attachInterrupt(1, get_char, FALLING);
 }
// ****************** добавление в буфер символа
void add_buffer(char char1)
 {
 if(txt_end_pos==txt_tek_pos)
   {txt_end_pos++;}
 else
   {txt_end_pos=txt_end_pos+(1-ins);shift_buffer_right();} 
 txt_buffer[txt_tek_pos]=char1;
 if(txt_end_pos!=txt_tek_pos)
  shift_lcd_right();
 txt_tek_pos=min(txt_tek_pos+1,lcd_cols*lcd_rows-1);
 txt_tek_pos=max(txt_tek_pos,0);
 //txt_buffer[txt_tek_pos]=char1;
 set_cursor(txt_tek_pos-offset);    
 }
// сдвиг  буфера текста
void shift_buffer_right()
 {
 if(ins==1)
   return;
 for(int i=txt_end_pos;i>=txt_tek_pos;i--)
   txt_buffer[i]=txt_buffer[i-1];
 } 
// сдвиг на дисплее вправо
void shift_lcd_right()
 {;
 for(int j=txt_tek_pos;j<min(txt_end_pos,lcd_cols*lcd_rows);j++)
   {set_cursor(j);lcd.write(txt_buffer[j]);} 
 }
// ****************** удаление из буфера backspace
void delete_from_buffer()
 {
 if(txt_tek_pos>0)
  {
  txt_buffer[txt_end_pos]=' ';  
  txt_end_pos--;
  txt_tek_pos--;
  shift_buffer_left();
  shift_lcd_left();
  }
 set_cursor(txt_tek_pos);    
 }
// сдвиг  буфера текста
void shift_buffer_left()
 {
 for(int i=txt_tek_pos;i<=txt_end_pos;i++)
   txt_buffer[i]=txt_buffer[i+1];
 } 
// сдвиг на дисплее влево
void shift_lcd_left()
 {;
 for(int j=txt_tek_pos;j<=min(txt_end_pos,lcd_cols*lcd_rows);j++)
   {set_cursor(j);lcd.write(txt_buffer[j]);} 
 } 
// ****************** удаление из буфера delete
void del_from_buffer()
 {
 if(txt_tek_pos<txt_end_pos)
  {
  txt_buffer[txt_end_pos]=' ';  
  txt_end_pos--;
  //txt_tek_pos--;
  shift_buffer_left();
  shift_lcd_left();
  }
 ////---------------
 //lcd.setCursor(0,2);
 //for(int i=0;i<txt_end_pos;i++)
 //  lcd.write(txt_buffer[i]);
 //-------------------   
 set_cursor(txt_tek_pos);    
 }
 
// установка курсора
void set_cursor(int pos)
 {
 int col;int row;  
 col=max(0,pos%lcd_cols);
 if(pos==lcd_cols*lcd_rows)
   col=lcd_cols-1;
 row=min(3,pos/lcd_cols);
        Serial.print("pos=");Serial.print(pos);
        Serial.print("txt_end_pos=");Serial.print(txt_end_pos);
        Serial.print("  col=");Serial.print(col);
        Serial.print("  row=");Serial.println(row);


 lcd.setCursor(col,row);
 }
// рассчитать для нового положения курсора
void new_cursor(int to)
 {
 //txt_tek_pos=min(txt_tek_pos+to,lcd_cols*lcd_rows-1);
 txt_tek_pos=min(txt_tek_pos+to,txt_end_pos);
 txt_tek_pos=max(txt_tek_pos,0);
 set_cursor(txt_tek_pos);    
 }


void setup()
{
  Serial.begin(9600);
  Serial.println("start-ok");
  kbd_init();
  Serial.println("keyboard-ok");
  for(int i=0;i<256;i++)
    up_down[i]=0;
  lcd.begin(16, 4);
  // Начальное сообщение
  lcd.clear();
  lcd.print("Клава PS/2");
  lcd.cursor();
  delay(5000);
  lcd.clear();
  attachInterrupt(1, get_char, FALLING);
}

//
void loop()
{
;
}
