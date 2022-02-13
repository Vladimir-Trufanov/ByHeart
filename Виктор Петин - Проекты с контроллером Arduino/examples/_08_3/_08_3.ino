// Вопроизведение мелодии, записанной в EEPROM
//
// подключение библиотеки EEPROM
#include <EEPROM.h>
// подключить динамик к pin 8 
int speakerPin = 8;
// подключить кнопку к pin 9 
int buttonPin = 9;
// темп воспроизведения, ноты, длительности
int tempo,notes,beats;
int addr1;
int rand1;
int count=0;
// проиграть ноту
void playNote(char note, int duration)
  {
  // массив для наименований нот (до ре ми ... и т.д. в пределах двух октав)
  char names[] = {  'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C','D','E','F','G','A','B' };
  //int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956, 850, 759, 716, 638, 568, 507 };
  int tones[] = {  3830, 3400, 3038, 2864, 2550, 2272, 2028, 1912, 1700, 1518, 1432, 1276, 1136, 1014 };
  // проиграть тон, соответствующий ноте
  for (int i = 0; i < sizeof(tones); i++)
   {
   if (names[i] == note) 
    {
    tone(speakerPin,tones[i],duration * 1000L);
    }
   }
 }

void setup()
 {
  pinMode(speakerPin, OUTPUT); 
  pinMode(buttonPin, INPUT); 
  Serial.begin(9600);  
  for(int i=0;i<200;i++)
   {
   Serial.print(i);Serial.print(" - ");
   Serial.println(EEPROM.read(i),DEC);  
   }
  int i=0; 
  while(EEPROM.read(i)<255)
   {count++;i++;}
  Serial.print("count=");Serial.println(count);
 }

void loop()
  {
  if(digitalRead(buttonPin)==HIGH)
   {
   Serial.println("click");  
   // получить случайное 
   rand1=random(0,count+1);
   addr1=EEPROM.read(rand1);
   Serial.println(addr1);  
   //
   tempo=EEPROM.read(addr1);
   addr1++;
   Serial.print(tempo,DEC);Serial.println("");  
   tempo=tempo*256+EEPROM.read(addr1);
   addr1++;
   Serial.print(tempo,DEC);Serial.println("");  
   while(EEPROM.read(addr1)>0)
    {
    notes=EEPROM.read(addr1);
    addr1++;
    beats=EEPROM.read(addr1);
    addr1++;  
    Serial.print(notes);Serial.print(" ");  
    Serial.print(beats,DEC);Serial.println(" ");
    if (notes == ' ') 
      tone(speakerPin,0, beats*tempo*1000L); // пауза
    else 
      playNote(notes, beats*tempo);
    // пауза между нотами
    delay(tempo / 2); 
    }
   Serial.println("end");  
   } 
  } 
