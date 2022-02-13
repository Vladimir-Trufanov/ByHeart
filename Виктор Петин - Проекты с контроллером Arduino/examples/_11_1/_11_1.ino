#include <OneWire.h>
OneWire  ds(10);  // на  digital pin 10

#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

#include <EEPROM.h>
int count_keys=0;
int address = 0;
byte value;
int count=0;
int admin=0;
//
int type1=0; // 0-view;1-prog;2-del
int click11=0;
int click12=0;
int pos11=2;
long endmillis11=0;
long endmillis12=0;
//
int address1=0;
int address2=8;
byte addr[8];
byte door=1;

// ноты мелодии (пробел - это пауза)
char notes1[]="GECgabCaCg "; // пробел - это пауза
char notes2[]="EFEDGEDC"; 
// длительность для каждой ноты и паузы
int beats1[] = { 4, 4, 4, 4, 1, 1, 1, 2, 1, 4, 2, 4, 4, 4, 4, 1, 1, 1, 2, 
        1,4, 2, 1, 1, 1, 1, 2, 1, 1, 4, 2, 1, 2, 1, 2, 1, 1, 4, 2, 1,
        2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 4, 4, 4} ;
int beats2[] = { 4, 4, 4, 4, 1, 1, 1, 2, 1, 4, 2, 4, 4, 4, 4, 1, 1, 1, 2, 
        1,4, 2, 1, 1, 1} ;

// подключить динамик к pin 17
int speakerPin = 17;
// темп воспроизведения
int tempo1 = 50;
int tempo2 =50;
// подключить реле к pin 19
int relayPin = 18;

void setup(void) {
  int i1;byte val1;
  pinMode(8, INPUT);           // назначить выводу порт ввода
  pinMode(9, INPUT);           // назначить выводу порт ввода
  
  //
  for(i1=8;i1<512;)
    { val1=EEPROM.read(i1);
    Serial.println(val1,HEX);
    if(val1==0xFF)
      break;
    else  
      count++;;
    i1=i1+8;}
  EEPROM.write(address1,count);
  if(count==0)
    {admin=2;type1=1;}
  
  Serial.begin(9600);
  for(i1=8;i1<count*8+8;i1++)
    { Serial.print(EEPROM.read(i1),HEX);
      Serial.print(" ");
    }

  
   lcd.begin(16, 2);
   lcd.clear();
  // Print a message to the LCD.
  lcd.print("iButton v0.1");
  lcd.setCursor(0,7);
  lcd.print("act_keys=");
  lcd.print(EEPROM.read(address1));
  
  pinMode(speakerPin, OUTPUT);
  playYES();
  
   pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin,HIGH);

}

void loop(void) {
  
  byte i;   
  int res1;  
  
   // чтение pin8
   if(digitalRead(8)!=click11)  // изменение положения кнопки
    {click11=1-click11;
    endmillis11=millis();}
   // чтение pin9
   if(digitalRead(9)!=click12) // изменение положения кнопки
    {click12=1-click12;
    endmillis12=millis();}
   if(click11==1 && millis()-endmillis11>5000) // нажата более 5 сек
    {
    clear_EEPROM();
    lcd.clear();
    lcd.print("iButton v0.1");
    lcd.setCursor(0,7);
    lcd.print("act_keys=0");
    admin=1;type1=1;
    }
  if(admin==1)
   {// режим программирования - проверяем кнопки
   // чтение pin8
   if(click11==1 && millis()-endmillis11>1000 && count>0) // нажата более 1 сек
    {type1=0;
    endmillis11=millis();
    pos11++;
    if(pos11>count)
      pos11=min(2,count);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" tekkey= ");   
    view_key1(pos11);
    }
   else
    ;
   // чтение pin9
    // нажата более 1 сек
   if(click12==1 && millis()-endmillis12>1000 && type1==2) // подтверждение удаления
    {if(pos11>1)
      delete_key(pos11);
     else
      admin_display(" empty   ",0);
    type1=0;
    endmillis12=millis();
    admin_display("admin = ",0);
    view_key1(1);
    }
   else if(click12==1 && millis()-endmillis12>1000 && type1==1) // режим - удалить?
    {
    type1=2;
    endmillis12=millis();
    admin_display("delete ? ",0);
    view_key1(pos11);
    }
   else if(click12==1 && millis()-endmillis12>1000 && type1==0) // вход в режим программирования
    {
    type1=1;
    endmillis12=millis();
    admin_display("add key  ",0);}
   else
    ;
  }
  //
  byte present = 0;
  //byte data[12];
  //byte addr[8];
  
  if ( !ds.search(addr)) {
      Serial.print("empty");
      ds.reset_search();
      delay(1000);
     return;
  }
res1=prov_key();  
if(res1==1)
  {admin=1-admin;view_key(res1);playYES();
      digitalWrite(relayPin, 1-door);}

else if(res1>1)
  {view_key(res1); playYES();door=1-door;
  if(door==1)
    digitalWrite(relayPin, HIGH);
  else
    digitalWrite(relayPin, LOW);
   }
else if(admin>0 && type1==1)
  {add_new_key(count+1);type1=0;admin =1;playYES();}
else
  {admin_display("bad key !  ",0);
  for( i = 0; i < 8; i++) {
    lcd.setCursor((7-i)*2,1);
    lcd.print(addr[i],HEX);
      playNO(); 
    }    
  }
 
}
// ********************* проверка наличия ключа в EEPROM
int prov_key()
 {
  byte i1;  byte i2;   
  int count11;
  for( i1 = 1; i1 <= count; i1++) 
   {count11=0;
   for( i2 = 0; i2 < 8; i2++) {
    if(addr[i2]==EEPROM.read(i1*8+i2))
      count11++;
   }
  if(count11==8) 
    return i1;
  } 
  return 0;
 }
 // ********************* добавление ключа в EEPROM
 void add_new_key(int nnew)
  {
  byte i1;    
  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.print("CRC is not valid!\n");
      return;
  }
  
  if ( addr[0] != 0x01) {
      Serial.print("Device is not a DS1990A family device.\n");
      return;
  }
  count++;
  lcd.setCursor(0,0);
  lcd.print("key_new = ");
  lcd.print(count,HEX);
  for( i1 = 0; i1 < 8; i1++) {
    lcd.setCursor((7-i1)*2,1);
    lcd.print(addr[i1],HEX);
    EEPROM.write(nnew*8+i1, addr[i1]);
  }
  ds.reset();  
  delay(1000);   
 } 
  // *********************  вывод прислоненного ключа в lcd
 void view_key(int rr)
  {
  byte i;  
  Serial.print(" nkey = ");
  lcd.clear();
  lcd.setCursor(0,0);
  if(admin==1 && rr==1)
     lcd.print("admin =");
  else
     lcd.print(" user = ");   
  lcd.setCursor(8,0);
  lcd.print(rr);
  for( i = 0; i < 8; i++) {
    lcd.setCursor((7-i)*2,1);
    lcd.print(addr[i],HEX);
    //EEPROM.write(i1*8+i, addr[i]);
  }
  ds.reset();  
  delay(1000);   
  return;
 } 
 // ********************* вывод ключа из EEPROM
 void view_key1(int rr)
  {
  byte i;  
  lcd.setCursor(8,0);
  lcd.print(rr);
  for( i = 0; i < 8; i++) {
    lcd.setCursor((7-i)*2,1);
    lcd.print(EEPROM.read(rr*8+i),HEX);
  }
  delay(1000);   
  return;
 } 
 // ********************* индикация режимов админа
 void admin_display(String str1,int stroke)
  {
  Serial.print(str1);
  lcd.clear();
  lcd.setCursor(0,stroke);
  lcd.print(str1);   
  //delay(1000);   
  }
  // удаление ключа из EEPROM
  void delete_key(int nn)
   {
   byte val1;
   for(int i1=nn;i1<=count;i1++)
     {
     for(int i2=0;i2<8;i2++)
        {
        val1=EEPROM.read((i1+1)*8+i2);
        Serial.print(i1*8+i2,DEC);
        Serial.print(" ");
        Serial.print(val1,HEX);
        Serial.println();       
        EEPROM.write(i1*8+i2,val1);
        }
     }
     count--;
   }
// ********************* очистка EEPROM
void clear_EEPROM()
 {
  for (int i1 = 8; i1 < 512; i1++)
   EEPROM.write(i1, 0xFF);
  EEPROM.write(address1,0);
  count=0;
 }

// мелодия YES
void playYES()
 {
 for (int i = 0; i < sizeof(notes1); i++) 
  {
  if (notes1[i] == ' ') 
    //tone(speakerPin,0, beats1[i]*tempo1* 1000L);  // пауза
    delay(beats1[i] * tempo1); // пауза
  else 
    playNote(notes1[i], beats1[i] * tempo1);
  }
 }
// мелодия NO
void playNO()
 {
 for (int i = 0; i < sizeof(notes2); i++) 
  {
  if (notes2[i] == ' ') 
    //tone(speakerPin,0, beats1[i]*tempo2* 1000L);  // пауза
    delay(beats2[i] * tempo2); // пауза
  else 
    playNote(notes2[i], beats2[i] * tempo2);
  } }
// проиграть ноту
void playNote(char note, int duration)
 {
 // массив для наименований нот (до ре ми ... и т.д. в пределах двух 
 //  октав)
 char names[]={'c','d','e','f','g','a','b','C','D','E','F','G','A','B'};
 int tones[]={3830,3400,3038,2864,2550,2272,2028,1912,1700,
              1518,1432,1276,1136,1014 }; 
 // проиграть тон, соответствующий ноте
for (int i = 0; i < sizeof(tones); i++)
 {
 if (names[i] == note)
   playTone(tones[i], duration);
 }
}
void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}
   
   
