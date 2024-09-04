// C++ code
//
#define pinButton 8
void setup()
{
  pinMode(pinButton, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{
  Serial.println("Time="+String(millis())+' '+
                "Status="+String(!digitalRead(8)));
}