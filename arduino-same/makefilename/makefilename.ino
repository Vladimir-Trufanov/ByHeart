// makefilename.ino 
//
// По строке символов принятой информации с часов контроллера SIM900: '+CCLK: "26/05/28,11:23:13+12"'
// сформировать имя для формирования файла с данными GPS/GSM:         "gps260518_1123.txt"

// Определяем макрос для размещения массива символов в программной памяти:
// const char pstr[] PROGMEM = "Массив символов pgm в программной памяти, Flash вместо RAM";
#define _DS(name,value) const char name[] PROGMEM = value;

// Объявляем массив принятых символов с часов SIM900
char fcclk[]="\n\n+CCLK: \"26/05/28,11:23:13+12\""; 
// Резервируем массив для формирования имени файла "gps260518_1123"
#define fnamesize 16            
char fname[fnamesize]="tesyGPS"; 

// Проскочить разделитель в принятой информации и
// перенести 2 символа в имя файла
void move2chars(int &Point, int &j)
{
  Point++;
  fname[j]=fcclk[Point]; j++; Point++;
  fname[j]=fcclk[Point]; j++; Point++;
}
// Определить префикс файла и сформировать его имя
_DS(pref_gps,"gps")    
void makefilename() 
{
  int i,j,Point;
  memset(fname,'\0',fnamesize); 
  strcat_P(fname,pref_gps); 
  j=3; // отметили позицию для следующего символа в имени файла
  // Ищем год (позиция первых кавычек)
  for (int i = 0; i < sizeof(fcclk)-1; i++) 
  {
    if (fcclk[i] == '"') 
    {
      Point=i;
      break;
    }
  }
  // Переносим год в имя файла
  Serial.print("Point="); Serial.println(Point);
  move2chars(Point,j);
  // Переносим месяц и день в имя файла
  move2chars(Point,j);
  move2chars(Point,j);
  // Переносим час и минуту
  fname[j]='_'; j++; 
  move2chars(Point,j);
  move2chars(Point,j);
}

void setup() 
{
  Serial.begin(9600);
  Serial.print("fcclk."); Serial.print(fcclk); Serial.println(".fcclk");
  Serial.print("fname."); Serial.print(fname); Serial.println(".fname");
  makefilename();
  Serial.print("fname."); Serial.print(fname); Serial.println(".fname");
}

void loop() 
{
}

