// Использование библиотеки EEPROM
// запись мелодий в EEPROM
// и вывод на динамик
// и дисплей WH1604

// подключение библиотеки EEPROM
#include <EEPROM.h>

 // Загрузка мелодий во флеш-память 
 // адреса  0-10
 // addr1,addr2,addr3....
 // 10- ......
 // addr1 (мелодия1)  tempo1,нота1,длит1,нота2,длит2...нотаN1,длитN1,0
 // addr2 (мелодия2)  tempo2,нота1,длит1,нота2,длит2...нотаN2,длитN2,0
 // addr3 (мелодия3)  tempo3,нота1,длит1,нота2,длит2...нотаN3,длитN3,0
 //  ....
 /* нота            частота               период timeHigh
 * c            261 Hz          3830    1915    
 * d            294 Hz          3400    1700    
 * e            329 Hz          3038    1519    
 * f            349 Hz          2864    1432    
 * g            392 Hz          2550    1275    
 * a            440 Hz          2272    1136    
 * b            493 Hz          2028    1014    
 * C            523 Hz          1912    956
 */
// ноты мелодии
String notes[] ={ "ccggaagffeeddc ",
  "GECgabCaCg DGECabCDED EFEDGEDC CECaCag gCEDgCEDEFGECDgC "}; 
// пробел - это пауза
// длительность для каждой ноты и паузы
String beats[]={"1,1,1,1,1,1,2,1,1,1,1,1,1,2,4",
   "4,4,4,4,1,1,1,2,1,4,2,4,4,4,4,1,1,1,2,1,4,2,1,1,1,1,2,1,1,4,2,1,2,1,2,1,1,4,2,1,2,1,2,1,2,1,2,1,1,1,1,1,2,1,4,4,4"} ;
int tempo[]= {300,400};
// 
int speakerPin = 8;
//
int addr1=0;
int addr2=10;

void write_melody(int num) 
 {
 //byte arr1=notes[num];  
 EEPROM.write(addr1,addr2);
 Serial.print(addr2);Serial.println(""); 
 EEPROM.write(addr2,tempo[num]>>8);
 addr2++; 
 EEPROM.write(addr2,tempo[num]);
 addr2++; 
 Serial.print("size=");Serial.println(notes[num].length());
 for(int j=0;j<notes[num].length();j++)
   {
   EEPROM.write(addr2,notes[num][j]);
   addr2++; 
   EEPROM.write(addr2,beats[num][j*2]-48);
   addr2++; 
   Serial.print(notes[num][j]);Serial.print(" "); 
   Serial.print(beats[num][j*2]);Serial.println(" "); 
   }
 // записать 0 - end  
 EEPROM.write(addr2,0);
 addr2++; 
 addr1++;    
 }


void setup()
 {
  // размерность индикатора 
  lcd.begin(16, 4);
  // Начальное сообщение
  lcd.setCursor(0, 0);
  lcd.print("Демо к книге");
  lcd.setCursor(0, 1);
  lcd.print("Arduino");
  lcd.setCursor(0, 2);
  lcd.print("- EEPROM");
  lcd.setCursor(0, 3);
  lcd.print("");
  lcd.noCursor();
  Serial.begin(9600);  
  Serial.println("start...");  
  pinMode(speakerPin, OUTPUT);  
  delay(10000);
  Serial.print("size=");Serial.println(sizeof(tempo));
  for(int i=0;i<sizeof(tempo)/2;i++)
    {write_melody(i);}
  lcd.clear();
  lcd.print("Загрузка-OK!");
  Serial.println("end..."); 
  Serial.println("control..."); 
  for(int i=0;i<200;i++)
   {
   Serial.print(i);Serial.print(" - ");
   Serial.println(EEPROM.read(i),DEC);  
   }
 }

void loop()
 {
 ;
 } 
