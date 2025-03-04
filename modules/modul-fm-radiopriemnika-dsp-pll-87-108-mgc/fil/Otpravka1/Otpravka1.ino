// C++ code

void setup() 
{
  // скорость передачи данных через последовательный интерфейс 9600 бит/сек  
  Serial.begin(9600);
}

int thisByte = 33;  // целочисленная переменная

void loop() 
{
  // передаём значение переменной в последовательный интерфейс передачи данных
  Serial.write(thisByte);  
  // если целочисленная переменная равняется 126, прекратить передачу данных
  if (thisByte == 126)  
  {    
    while (true) 
    {
      continue;
    }
  }
  // увеличиваем значение целочисленной переменной
  thisByte ++; 
  // пауза 1000 миллисекунд 
  delay(1000);
}
