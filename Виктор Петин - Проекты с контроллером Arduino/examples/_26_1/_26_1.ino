// передатчик - HK-T6A
// приемник :
// Ch1 - Rudder (руль направления, рыскание, YAW)
// Ch2 - Elevator (тангаж, PITCH)
// Ch3 - Throttle (газ)
// Ch4 - Aileron (элероны, ROLL)


unsigned long Ch1Value,Ch2Value,Ch3Value,Ch4Value;
unsigned long last1,last2,last3,last4;
int pinCh1=11;
int pinCh2=10;
int pinCh3=9;
int pinCh4=8;

void setup()
 {
  Serial.begin(9600);
  Serial.println("Ready");
  pinMode (pinCh1, INPUT); // вход Rx channel 1 на чтение 
  pinMode (pinCh2, INPUT); // вход Rx channel 2 на чтение
  pinMode (pinCh3, INPUT); // вход Rx channel 3 на чтение
  pinMode (pinCh4, INPUT); // вход Rx channel 4 на чтение
  last1 = pulseIn (pinCh1, HIGH); //чтение данных RC channel 1
  last2 = pulseIn (pinCh2, HIGH); //чтение данных RC channel 2
  last3 = pulseIn (pinCh3, HIGH); //чтение данных RC channel 3
  last4 = pulseIn (pinCh4, HIGH); //чтение данных RC channel 4
  }

void loop()
 {
  //
  Ch1Value = pulseIn (pinCh1, HIGH, 20000); //чтение данных RC channel 1
  if (Ch1Value == 0) {Ch1Value = last1;} 
  else {last1 = Ch1Value;}
  Serial.print ("  Ch1: ");Serial.print (Ch1Value);
  //
  Ch2Value = pulseIn (pinCh2, HIGH, 20000); //чтение данных RC channel 2
  if (Ch2Value == 0) {Ch2Value = last2;} 
  else {last2 = Ch2Value;}
  Serial.print("  Ch2: ");Serial.print (Ch2Value);
  //
  Ch3Value = pulseIn (pinCh3, HIGH, 20000); //чтение данных RC channel 3
  if (Ch3Value == 0) {Ch3Value = last3;} 
  else {last3 = Ch3Value;}
  Serial.print("  Ch3: ");Serial.print (Ch3Value);
  //
  Ch4Value = pulseIn (pinCh4, HIGH, 20000); //чтение данных RC channel 4
  if (Ch4Value == 0) {Ch4Value = last4;} 
  else {last4 = Ch4Value;}
  Serial.print("  Ch4: ");Serial.print (Ch4Value);
  Serial.println("");
  
}



