/*
  water_sensor_test.ino
  Il programma legge il valore analogico del sensore
  0 se il sensore è asciutto

  Sono utilizzati i seguenti pin
  Pin +5V         -> Alimentazione sensore
  Pin GND         -> GND sensore /led
  Pin Digitale 2  -> Led Rosso
  Pin Digitale 3  -> led Verde
  Pin Analogico 0 -> Segnale sensore

  Creato il 6/5/2017 da Adriano Gandolfo
  Sito web http://www.adrirobot.it
  Blog http://it.emcelettronica.com/author/adrirobot
  Pagina Facebook https://www.facebook.com/Adrirobot-318949048122955
  Istagram https://www.instagram.com/adrirobot/
  This example code is in the public domain.
*/

int sensore   = 0; // Pin analogico a cui è collegato il sensore
int rosso     = 2; //Pin a cui è collegato il led rosso
int verde     = 3; //Pin a cui è collegato il led verde
int soglia    = 200; // Imposta valore soglia

void setup() {
  // Inizializza la comunicazione seriale
  Serial.begin(9600);
  pinMode (rosso, OUTPUT);    // Imposta il pin 2 lede rosso come uscita.
  pinMode (verde, OUTPUT);    // Imposta il pin 3 lede verde come uscita.
  digitalWrite(verde, HIGH);  //Accende led verde
}

void loop() {
  // Lettura valore del sensore
  int lettura = analogRead(sensore);
  // Scruttura del valore letto
  Serial.println(lettura);
  if (lettura >= soglia) {
    digitalWrite(verde, LOW);   //Spegne led verde
    digitalWrite(rosso, HIGH);  //Accende led rosso
  }
  else {
    digitalWrite(verde, HIGH);  //Accende led verde
    digitalWrite(rosso, LOW);   //Spegne led rosso
  }
  // Pausa tra le letture
  delay(100);
}
