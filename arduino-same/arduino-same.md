## arduino-same - замечания по программированию в IDE Arduino

### Массивы символов

#### Поиск в массиве char с помощью функций C

Для работы с массивами символов, заканчивающимися нулём, можно использовать стандартные функции C, например:

- ***strchr*** - ищет символ в строке и возвращает указатель на него. Если символ не найден, возвращается нулевой указатель.

- ***strstr*** - ищет подстроку в строке и возвращает указатель на её начало. Если подстрока не найдена, возвращается нулевой указатель.

Пример использования ***strchr***:
```
char buf = "hello world";
char* p = strchr(buf, 'w'); // p == "world", (p - buf) == 6
```

Также можно реализовать поиск вручную с помощью цикла, сравнивая каждый символ массива с искомым. 

[Пример приложения:](makefilename/makefilename.ino)

```
// По строке символов принятой информации с часов контроллера SIM900:
'+CCLK: "26/05/28,11:23:13+12"'
// сформировать имя для формирования файла с данными GPS/GSM:
"gps260518_1123.txt"

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
  Serial.print("fcclk="); Serial.println(fcclk);
   makefilename();
  Serial.print("fname="); Serial.println(fname);
}

void loop() 
{
}

```

###### [к содержанию](#soderzhanie)
