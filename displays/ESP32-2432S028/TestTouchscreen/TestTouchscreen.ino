/*  
 *   TestTouchscreen.ino
 *   
 *   Rui Santos & Sara Santos - Random Nerd Tutorials
    THIS EXAMPLE WAS TESTED WITH THE FOLLOWING HARDWARE:
    1) ESP32-2432S028R 2.8 inch 240×320 also known as the Cheap Yellow Display (CYD): https://makeradvisor.com/tools/cyd-cheap-yellow-display-esp32-2432s028r/
      SET UP INSTRUCTIONS: https://RandomNerdTutorials.com/cyd/
    2) REGULAR ESP32 Dev Board + 2.8 inch 240x320 TFT Display: https://makeradvisor.com/tools/2-8-inch-ili9341-tft-240x320/ and https://makeradvisor.com/tools/esp32-dev-board-wi-fi-bluetooth/
      SET UP INSTRUCTIONS: https://RandomNerdTutorials.com/esp32-tft/
    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*/

#include <SPI.h>

/*  Install the "TFT_eSPI" library by Bodmer to interface with the TFT Display - https://github.com/Bodmer/TFT_eSPI
    *** IMPORTANT: User_Setup.h available on the internet will probably NOT work with the examples available at Random Nerd Tutorials ***
    *** YOU MUST USE THE User_Setup.h FILE PROVIDED IN THE LINK BELOW IN ORDER TO USE THE EXAMPLES FROM RANDOM NERD TUTORIALS ***
    FULL INSTRUCTIONS AVAILABLE ON HOW CONFIGURE THE LIBRARY: https://RandomNerdTutorials.com/cyd/ or https://RandomNerdTutorials.com/esp32-tft/   */
#include <TFT_eSPI.h>

// Install the "XPT2046_Touchscreen" library by Paul Stoffregen to use the Touchscreen - https://github.com/PaulStoffregen/XPT2046_Touchscreen
// Note: this library doesn't require further configuration
#include <XPT2046_Touchscreen.h>

TFT_eSPI tft = TFT_eSPI();

// c:\Users\tve\Documents\Arduino

// Touchscreen pins
#define XPT2046_IRQ 36   // T_IRQ
#define XPT2046_MOSI 32  // T_DIN
#define XPT2046_MISO 39  // T_OUT
#define XPT2046_CLK 25   // T_CLK
#define XPT2046_CS 33    // T_CS

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define FONT_SIZE 2

// Touchscreen coordinates: (x, y) and pressure (z)
int x, y, z;

// Print Touchscreen info about X, Y and Pressure (Z) on the Serial Monitor
void printTouchToSerial(int touchX, int touchY, int touchZ) {
  Serial.print("X = ");
  Serial.print(touchX);
  Serial.print(" | Y = ");
  Serial.print(touchY);
  //Serial.print(" | Pressure = ");
  Serial.print(" | Нажми Place");
  Serial.print(touchZ);
  Serial.println();
}

// Print Touchscreen info about X, Y and Pressure (Z) on the TFT Display
void printTouchToDisplay(int touchX, int touchY, int touchZ) {
  // Clear TFT screen
  tft.fillScreen(TFT_WHITE);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);

  int centerX = SCREEN_WIDTH / 2;
  int textY = 80;
 
  String tempText = "X = " + String(touchX);
  tft.drawCentreString(tempText, centerX, textY, FONT_SIZE);

  textY += 20;
  tempText = "Y = " + String(touchY);
  tft.drawCentreString(tempText, centerX, textY, FONT_SIZE);

  textY += 20;
  tempText = "Pressure = " + String(touchZ);
  tft.drawCentreString(tempText, centerX, textY, FONT_SIZE);
}

void setup() {
  Serial.begin(115200);

  // Start the SPI for the touchscreen and init the touchscreen
  touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  touchscreen.begin(touchscreenSPI);
  // Set the Touchscreen rotation in landscape mode
  // Note: in some displays, the touchscreen might be upside down, so you might need to set the rotation to 3: touchscreen.setRotation(3);
  touchscreen.setRotation(1);

  // Start the tft display
  tft.init();
  // Set the TFT display rotation in landscape mode
  tft.setRotation(1);

  // Clear the screen before writing to it
  tft.fillScreen(TFT_WHITE);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  
  // Set X and Y coordinates for center of display
  int centerX = SCREEN_WIDTH / 2;
  int centerY = SCREEN_HEIGHT / 2;

  tft.drawCentreString("Hello, world!", centerX, 30, FONT_SIZE);
  //tft.drawCentreString("Привет, world!", centerX, 30, FONT_SIZE);
  tft.drawCentreString("Touch screen to test", centerX, centerY, FONT_SIZE);
}

void loop() {
  // Checks if Touchscreen was touched, and prints X, Y and Pressure (Z) info on the TFT display and Serial Monitor
  if (touchscreen.tirqTouched() && touchscreen.touched()) {
    // Get Touchscreen points
    TS_Point p = touchscreen.getPoint();
    // Calibrate Touchscreen points with map function to the correct width and height
    x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
    y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);
    z = p.z;

    printTouchToSerial(x, y, z);
    printTouchToDisplay(x, y, z);

    delay(100);
  }
}

/*
что за функция x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
--------------------------------------------------------

Это не какая-то встроенная стандартная функция — так часто делают в проектах с микроконтроллерами (например, на Arduino, ESP32) при работе с сенсорным экраном. Я объясню, что тут происходит. 
voltiq.ru
kafkar.com
wokwi.com
Суть в калибровке. Сенсорный экран при касании выдаёт «сырые» значения (например, от контроллера). Но эти значения не совпадают с реальными пикселями на экране — у сенсора своя специфика. Функция map() как раз переводит «сырые» показания в координаты, подходящие для отображения на экране. 
voltiq.ru
wokwi.com
Разберу синтаксис:
p.x — это значение по оси X, которое сенсор отдал при касании.
200, 3700 — эмпирические границы. Их находят экспериментально: касаются крайне левой точки экрана и фиксируют минимальное значение (200), а при касании крайне правой точки — максимальное (3700).
1, SCREEN_WIDTH — диапазон, в который нужно отобразить данные. Если экран имеет ширину SCREEN_WIDTH пикселей, то результат map() должен лежать в пределах от 1 до SCREEN_WIDTH.
 
voltiq.ru
wokwi.com
Пример: если сенсор при касании дал p.x = 3000, то map(3000, 200, 3700, 1, SCREEN_WIDTH) вернёт значение, пропорциональное положению внутри экрана (например, 1.7, которое можно округлить или использовать как индекс).
Аналогично часто встречается и вторая строка: y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT). Для оси Y тоже определяют свои границы (240 и 3800). 
voltiq.ru
wokwi.com
Почему такие числа? Они зависят от конкретной модели сенсора, способа подключения и возможной нелинейности. Иногда у сенсора есть «мёртвая зона» у края, или АЦП контроллера имеет смещение. 
voltiq.ru
Что делать, если калибровка «плывёт»? Можно вывести на экран маркеры крайних точек, записать реальные значения p.x при касании этих точек и подставить новые границы в map(). 
voltiq.ru
Так что эта строчка — просто удобный способ «подстроить» сырые данные сенсора под логику вашего графического интерфейса. 


Как проверить точность калибровки функции map()?
------------------------------------------------

Разберу подробно, как проверить и улучшить точность калибровки функции map() для сенсорного экрана.

Пошаговая инструкция по проверке
Шаг 1. Визуальная проверка по ключевым точкам

Создайте тестовую программу, которая:

выводит на экран маркеры в ключевых точках (углы и центр);
при касании маркера отображает сырые (p.x, p.y) и преобразованные (x, y) координаты.
Пример кода (Arduino/ESP32):

cpp
void loop() {
  if (ts.touched()) {
    TS_Point p = ts.getPoint();
    int x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
    int y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);

    Serial.print("Raw: ");
    Serial.print(p.x);
    Serial.print(", ");
    Serial.println(p.y);
    Serial.print("Mapped: ");
    Serial.print(x);
    Serial.print(", ");
    Serial.println(y);
  }
  delay(100);
}
Шаг 2. Количественная оценка ошибки

Для каждой тестовой точки рассчитайте ошибку по формуле:

Ошибка
𝑥
=
∣
𝑥
фактическая
−
𝑥
ожидаемая
∣
Ошибка 
x
​
 =∣x 
фактическая
​
 −x 
ожидаемая
​
 ∣
Ошибка
𝑦
=
∣
𝑦
фактическая
−
𝑦
ожидаемая
∣
Ошибка 
y
​
 =∣y 
фактическая
​
 −y 
ожидаемая
​
 ∣
Типичные тестовые точки:

углы экрана (0,0), (SCREEN_WIDTH, 0), (0, SCREEN_HEIGHT), (SCREEN_WIDTH, SCREEN_HEIGHT);
центр экрана (SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
середины сторон.
Шаг 3. Построение карты ошибок

Разбейте экран на сетку (например, 3×3 или 5×5) и:

Коснитесь каждой точки сетки.
Запишите фактическую и ожидаемую координаты.
Рассчитайте ошибку для каждой точки.
Визуализируйте результаты в виде таблицы или графика.
Пример таблицы:

Позиция	Ожидаемые (X,Y)	Фактические (X,Y)	Ошибка X	Ошибка Y
Левый верх	(10,10)	(8,12)	2	2
Центр	(160,120)	(158,119)	2	1
Правый низ	(310,230)	(305,225)	5	5
Шаг 4. Статистический анализ

Рассчитайте метрики точности:

средняя ошибка:
Средняя ошибка
𝑥
=
∑
Ошибка
𝑥
𝑁
Средняя ошибка 
x
​
 = 
N
∑Ошибка 
x
​
 
​
 
максимальное отклонение;
стандартное отклонение (показывает стабильность калибровки).
Методы улучшения точности
Метод 1. Уточнение границ калибровки

Если ошибка систематическая (везде смещена в одну сторону):

Коснитесь крайних точек экрана.
Запишите новые сырые значения (p.x_min, p.x_max, p.y_min, p.y_max).
Обновите параметры в map().
Метод 2. Многоточечная калибровка

Используйте более сложную функцию преобразования вместо map():

cpp
int calibratedX(int rawX) {
  // Линейная интерполяция между несколькими точками
  // или полиномиальная аппроксимация
}
Метод 3. Усреднение значений

Устраняет дрожание сенсора:

cpp
int getStableX() {
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += ts.getPoint().x;
    delay(10);
  }
  return map(sum / 5, 200, 3700, 1, SCREEN_WIDTH);
}
Метод 4. Коррекция нелинейности

Если ошибка неравномерна по экрану, разделите экран на зоны и используйте разные коэффициенты калибровки для каждой зоны.

Практические советы
Повторяемость. Проводите тесты при одинаковых условиях (температура, освещение).
Инструмент. Используйте стилус вместо пальца для точных касаний.
Границы. Не калибруйте по самым краям — там часто «мёртвые зоны».
Проверка. После изменений повторите тесты по всей сетке.
Сохранение. Записывайте лучшие параметры калибровки в EEPROM или файл.
Критерии хорошей калибровки
максимальная ошибка < 10 пикселей;
средняя ошибка < 5 пикселей;
отсутствие систематических смещений;
стабильность при повторных тестах.


Пример полного кода с фильтрацией
---------------------------------

#define CALIB_SAMPLES 5

int getFilteredValue(int raw, int minVal, int maxVal, int screenSize) {
  static int samples[CALIB_SAMPLES];
  static int index = 0;
  samples[index] = raw;
  index = (index + 1) % CALIB_SAMPLES;

  long sum = 0;
  for (int i = 0; i < CALIB_SAMPLES; i++) {
    sum += samples[i];
  }
  int avg = sum / CALIB_SAMPLES;
  return map(avg, minVal, maxVal, 0, screenSize - 1);
}

// В основном цикле:
int x = getFilteredValue(p.x, 200, 3700, SCREEN_WIDTH);
int y = getFilteredValue(p.y, 240, 3800, SCREEN_HEIGHT);
Этот код усредняет 5 последних значений перед применением map(), что снижает влияние шумов.


Источники
Источник видео: VK Видео · Смотрите онлайн «Урок №12 Настройка диапазонов видимости в MapInfo Professional» от автора Surveyor. Хорошее качество видео без регистрации в бесплатном видеокаталоге VK Видео.
Статья автора «Герман Геншин» в Дзене ✍:
Я
что за функция x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
Алиса
Это не какая-то встроенная функция языка, а использование стандартной функции map() из среды разработки для микроконтроллеров (например, Arduino). Я поясню, зачем она тут нужна — обычно так калибруют сенсорный экран. 
voltiq.ru +2

Что делает эта строка:

cpp
x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
Она преобразует «сырые» значения, которые получает сенсор, в координаты пикселей для экрана. 
voltiq.ru +2

Разберу параметры:

p.x — значение по оси X, которое сенсор отдаёт в момент касания (это «сырой», необработанный сигнал).
200 и 3700 — эмпирически найденные границы диапазона. Их определяют экспериментально: при касании крайних левых и правых точек экрана фиксируются минимальные и максимальные значения p.x.
1 и SCREEN_WIDTH — диапазон, в который нужно отобразить результат. 1 — минимальная координата (левый край экрана), SCREEN_WIDTH — максимальная (правый край).
 
voltiq.ru +1

Проще говоря, функция «растягивает» или «сжимает» диапазон значений сенсора (200–3700) до нужного диапазона пикселей экрана (1–SCREEN_WIDTH). 
voltiq.ru +1

Важное замечание: числа 200 и 3700 не универсальны. Они зависят от конкретной модели сенсора, способа подключения, калибровки и возможной нелинейности. Если у вас сенсор работает неточно, нужно заново снять показания (записать p.x при касании крайних точек) и подставить новые границы в map(). 

Аналогично часто встречается строка для оси Y:

cpp
y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);
(здесь 240 и 3800 — границы для оси Y). 
voltiq.ru +1

Такой подход часто встречается в проектах с ESP32 и TFT-экраном (например, на платах вроде Cheap Yellow Display, CYD). 
voltiq.ru +2

Итог: эта строчка — способ сделать так, чтобы точка касания на физическом экране точно отображалась на экране микроконтроллера в виде координат (x, y). 
voltiq.ru +1

Я
Как правильно настроить границы диапазона в map()?
Алиса
Разберу пошагово, как правильно настроить границы диапазона в функции map() — например, для калибровки сенсорного экрана.

Пошаговая инструкция
Шаг 1. Подготовьте тестовую программу

Создайте простой скетч, который выводит «сырые» значения сенсора в Serial-порт при касании экрана:

cpp
void loop() {
  if (touch.touched()) {
    TS_Point p = touch.getPoint();
    Serial.print("X: ");
    Serial.print(p.x);
    Serial.print(" | Y: ");
    Serial.println(p.y);
  }
  delay(100);
}
Шаг 2. Запустите сбор данных

Загрузите скетч на плату.
Откройте Serial Monitor (скорость — 115200).
Коснитесь экрана в крайних точках:
левый верхний угол;
правый верхний угол;
левый нижний угол;
правый нижний угол.
Запишите полученные значения p.x и p.y.
Шаг 3. Определите границы

На основе собранных данных найдите:

для оси X: минимальное (minX) и максимальное (maxX) значение;
для оси Y: минимальное (minY) и максимальное (maxY) значение.
Пример:

при касании слева p.x = 200;
при касании справа p.x = 3700;
при касании сверху p.y = 240;
при касании снизу p.y = 3800.
Шаг 4. Примените функцию map()

Используйте найденные границы в вызове функции:

cpp
int x = map(p.x, minX, maxX, 0, SCREEN_WIDTH - 1);
int y = map(p.y, minY, maxY, 0, SCREEN_HEIGHT - 1);
Где:

p.x, p.y — текущие «сырые» показания сенсора;
minX, maxX — минимальные и максимальные значения по X;
minY, maxY — минимальные и максимальные значения по Y;
0 и SCREEN_WIDTH - 1 — диапазон координат экрана по X (от 0 до ширины экрана минус 1);
0 и SCREEN_HEIGHT - 1 — диапазон координат экрана по Y (от 0 до высоты экрана минус 1).
Шаг 5. Проверьте и уточните

Протестируйте работу: коснитесь разных точек экрана и убедитесь, что курсор следует за пальцем.
Если есть расхождения (например, курсор смещён), повторите сбор данных, уделив внимание:
точности касания в крайних точках;
возможным нелинейностям сенсора (особенно по краям);
стабильности показаний (сделайте несколько замеров для каждой точки).
Важные нюансы
Порядок осей. У некоторых сенсоров оси могут быть инвертированы или перепутаны. Если при касании слева курсор появляется справа, попробуйте поменять местами minX и maxX.
Нелинейность. Сенсор может давать неравномерные значения. Если калибровка точная в центре, но плохая по краям, рассмотрите:
кусочно‑линейную аппроксимацию (разбейте экран на зоны);
полиномиальную коррекцию (используйте квадратичную функцию вместо map()).
Шумы. Добавляйте фильтрацию, если показания «скачут»:
усреднение нескольких измерений;
проверка на минимальную разницу между соседними значениями.
Инверсия осей. Если ось Y работает наоборот (верх = большое число, низ = малое), поменяйте местами minY и maxY.
Границы экрана. Используйте SCREEN_WIDTH - 1 и SCREEN_HEIGHT - 1, чтобы не выйти за пределы массива пикселей (индексация от 0).
Пример полного кода с фильтрацией
cpp
#define CALIB_SAMPLES 5

int getFilteredValue(int raw, int minVal, int maxVal, int screenSize) {
  static int samples[CALIB_SAMPLES];
  static int index = 0;
  samples[index] = raw;
  index = (index + 1) % CALIB_SAMPLES;

  long sum = 0;
  for (int i = 0; i < CALIB_SAMPLES; i++) {
    sum += samples[i];
  }
  int avg = sum / CALIB_SAMPLES;
  return map(avg, minVal, maxVal, 0, screenSize - 1);
}

// В основном цикле:
int x = getFilteredValue(p.x, 200, 3700, SCREEN_WIDTH);
int y = getFilteredValue(p.y, 240, 3800, SCREEN_HEIGHT);

*/
