// C++ code
// объявляем и инициализируем целочисленную переменную
int incomingByte = 0;  

void setup() 
{
 Serial.begin(9600);  
}

void loop() 
{
  // если в последовательном интерфейсе присутствуют данные передать их в консоль 
  if (Serial.available() > 0) 
  {
     // читаем даннные из последовательного интерфейса и присваиваем целочисленной переменнной 
     incomingByte = Serial.read();
     // выводи переменную в консоль 
     Serial.print("Received:  ");
     Serial.write(incomingByte);
    // выводим переменную в консоль в разных кодировках 
     Serial.print("    INT:  ");
     Serial.print(incomingByte);
     Serial.print("    DEC:  ");
     Serial.print(incomingByte, DEC);
     Serial.print("    HEX:  ");
     Serial.print(incomingByte, HEX);
     Serial.print("    OCT:  ");
     Serial.print(incomingByte, OCT);
     Serial.print("    BIN:  ");
     Serial.print(incomingByte, BIN);
     Serial.println(" ");
                              }
}
