#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>
// библиотеки для ESP32Cam и SD Card
#include "esp_camera.h"
#include "FS.h"                // SD Card ESP32
#include "SD_MMC.h"            // SD Card ESP32
#include "soc/soc.h"           
#include "soc/rtc_cntl_reg.h"  
#include "driver/rtc_io.h"

//#include <Adafruit_Sensor.h>
//#include <DHT.h>
//#include <DHT_U.h>

const char* ssid = "linksystve";            // Название WIFI сети
const char* password = "x93k6kq6wf";          // Пароль от WIFI сети

const char* host = "192.168.0.104";       // Локальный адрес
const uint16_t port = 84;                 // Порт

//#define DHTPIN 2 
//#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)
//DHT_Unified dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(115200);
  
  //dht.begin();
  //sensor_t sensor;
  //dht.temperature().getSensor(&sensor);
  
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)   // Ждём пока не соединится
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
}

void loop() {

  delay(2000);
  //sensors_event_t event;
  //dht.temperature().getEvent(&event); 
  float temp = 54.3; //event.temperature;
  //dht.humidity().getEvent(&event);
  int hum = 71; //int(event.relative_humidity);
  

  WiFiClient client;
  if (client.connect(host, port))
  {
    client.print("GET /insert.php?");
    client.print("temp=");
    client.print(temp);
    client.print("&hum=");
    client.print(hum);
    client.println(" HTTP/1.1");
    client.print( "Host: " );
    client.println(host);
    client.println( "Connection: close" );
    client.println();
    client.println();

    
    while (client.connected())                          //Ответ
    {
      if (client.available())
      {
        String line = client.readStringUntil('\n');
      }
    }
    client.stop();                                    // Остановить клиента
  }
  else
  {
    client.stop();                                    // Ошибка подключения
  }
  delay(10000);                         // Ждём 10 cекунд
}
