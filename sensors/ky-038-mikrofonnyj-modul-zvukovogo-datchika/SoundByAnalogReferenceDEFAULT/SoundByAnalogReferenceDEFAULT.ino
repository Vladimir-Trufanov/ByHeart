// Скетч снятия звука с модулей KY-037, KY-038 и
// вывода на плоттер

#define buzzerPin 8   // контакт для подключения зуммера
int btnPin = 2;       // контакт кнопки включения зуммера

void setup()
 {
    pinMode(buzzerPin, OUTPUT);
    pinMode(btnPin, INPUT_PULLUP);

    Serial.begin(9600);
    pinMode(A0, INPUT);
    // analogReference() нужно так
    analogReference(DEFAULT);
    // а можно и так
    //Serial.println("DEFAULT");

 }
void loop()
 {
    int btnState = digitalRead(btnPin);
    if (btnState == HIGH) tone(buzzerPin, 100);
    else noTone(buzzerPin); 
    Serial.println(analogRead(A0));
    delay(100);
 }
