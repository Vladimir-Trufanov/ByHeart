// Вопроизведение мелодии
// через динамик
 /* Пример использования динамика для проигрывания мелодии.  
 * Для этого  подаётся сигнал соответствующей частоты.
 *      Расчет тонов производится следующим образом:
 *       timeHigh = period / 2 = 1 / (2 * toneFrequency)
 *
 * таблица различных тонов:
 *
 * нота            частота               период timeHigh
 * c            261 Hz          3830    1915    
 * d            294 Hz          3400    1700    
 * e            329 Hz          3038    1519    
 * f            349 Hz          2864    1432    
 * g            392 Hz          2550    1275    
 * a            440 Hz          2272    1136    
 * b            493 Hz          2028    1014    
 * C            523 Hz          1912    956
 ...
 */
 
// ноты мелодии
char notes[] = "GECgabCaCg DGECabCDED EFEDGEDC CECaCag gCEDgCEDEFGECDgC "; // пробел - это пауза
// длительность для каждой ноты и паузы
int beats[] = { 4, 4, 4, 4, 1, 1, 1, 2, 1, 4,
        2, 4, 4, 4, 4, 1, 1, 1, 2, 1,
        4, 2, 1, 1, 1, 1, 2, 1, 1, 4,
        2, 1, 2, 1, 2, 1, 1, 4, 2, 1,
        2, 1, 2, 1, 2, 1, 2, 1, 1, 1,
        1, 1, 2, 1, 4, 4, 4} ;
// подключить динамик к pin 8 
int speakerPin = 8;
int length = sizeof(beats);  // число нот
// темп воспроизведения
int tempo = 400;

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
 }

void loop()
  {
  for (int i = 0; i < length; i++)
    {
    if (notes[i] == ' ') 
      tone(speakerPin,0, beats[i]*tempo* 1000L); // пауза
    else 
      playNote(notes[i], beats[i] * tempo);
     // пауза между нотами
    delay(tempo / 2); 
    }
  delay(3000);
  } 
