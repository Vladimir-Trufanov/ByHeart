/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

//https://stackoverflow.com/questions/13853109/determine-board-type-of-arduino
//https://github.com/backupbrain/ArduinoBoardManager
//https://stackru.com/questions/2305630/opredelit-tip-platyi-arduino
//https://arduino.stackexchange.com/questions/39137/how-does-arduino-ide-get-board-info

#include "ArduinoBoardManager.h";
ArduinoBoardManager arduino = ArduinoBoardManager(); // required if you want to know the board name and specific features

// the setup function runs once when you press reset or power the board
void setup() 
{
   // Инициализируем последовательную связь
   Serial.begin(9600);
   while (!Serial);
   Serial.println("Started");


  Serial.print("Board is compatible with Arduino ");
  Serial.println(arduino.BOARD_NAME);
  Serial.println(arduino.MAX_MHZ);
  
  Serial.println("Speed/SRAM/Flash: ");
  Serial.println(ArduinoBoardManager::MAX_MHZ);
  Serial.println(ArduinoBoardManager::SRAM_SIZE);
  Serial.println(ArduinoBoardManager::FLASH_SIZE);
  //
  // Board features (multiple serial ports on Mega, for example)
  if (arduino.featureExists(ArduinoBoardManager::FEATURE_MULTIPLE_SERIAL)) {
    Serial.println("Your board supports multiple serial connections");
  }

   /*
   #define LED_BUILTIN 13
   #if defined(LED_BUILTIN)
   Serial.println("Установлена LED_BUILTIN");
   #endif
   */

   // https://arduinoprosto.ru/q/21137/arduino-kak-poluchit-tip-platy-v-kode
   
   #ifdef ARDUINO_AVR_UNO
      #define HERE_BOARD_TYPE "UNO"
   #elif defined(ARDUINO_AVR_LEONARDO)       
      #define HERE_BOARD_TYPE "LEONARDO"
   #else
      #define HERE_BOARD_TYPE "UNKNOWN-BOARD"
   #endif
   Serial.print("Установлена плата: "); Serial.println(HERE_BOARD_TYPE);

   /*
   if (!IMU.begin()) 
   {
      Serial.println("Failed to initialize IMU!");
      while (1);
   }
   */

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() 
{
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(200);                       // wait for a second
}
