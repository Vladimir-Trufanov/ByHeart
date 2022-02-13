const int moneyPin=2;

int money=0;

unsigned long timeAllPulse=2000; // макс. время приема купюры
unsigned long timeCount=0;

void setup()
{
  Serial.begin(9600);
  pinMode(moneyPin,INPUT);
  attachInterrupt(0,count_pulse,FALLING);
  Serial.println("ready");
}

void loop()
{
  // прошло максимальное время приема купюры?
  if(money>0 && (millis()-timeCount)>timeAllPulse) 
    {
    Serial.print("money=");  
    Serial.println(10*money);
    money=0;  
    }
}

// обработка прерывания - получить кол-во импульсов
//  
void count_pulse()
  {
  detachInterrupt(0);
  money++;
  if(money==1)
    timeCount=millis();
  attachInterrupt(0,count_pulse,FALLING);
  }

