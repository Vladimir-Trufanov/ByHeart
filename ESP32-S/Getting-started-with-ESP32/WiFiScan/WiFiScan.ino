/* ========================================================================= */
/*   WiFiScan.ino                                                            */
/*   (c) 2024-02-03 Труфанов Владимир                                        */
/*                                                    Cканировать сети Wi-Fi */
/* ========================================================================= */

/**
 * 2024-02-03. После запуска программы сканирования WiFi-сети (а затем при 
 * создании точки доступа) на ESP32-S при подключении платы по USB и 
 * одновременном использовании кабеля USB для последовательного обмена с 
 * монитором на компьютере возникало сообщение:
 * "Brownout detector was triggered" [Сработал детектор аварийного отключения]
 * и сканер не запускался, выдавая ошибки.
 * 
 * После подключения внешнего питания к схеме сообщение было устранено 
 * и схема заработала, как от неё требовалось.
**/

#include "WiFi.h"
 
void setup()
{
   Serial.begin(115200);
   // Set WiFi to station mode and disconnect from an AP if it was previously connected
   WiFi.mode(WIFI_STA);
   WiFi.disconnect();
   delay(100);
   Serial.println("Setup done");
}
 
void loop()
{
   Serial.println("scan start");
   // WiFi.scanNetworks will return the number of networks found
   int n = WiFi.scanNetworks();
   Serial.println("scan done");
   if (n == 0) 
   {
      Serial.println("Сети WiFi не найдены");
   } 
   else 
   {
      Serial.print("Найдено ");
      Serial.print(n);
      Serial.println(" сетей WiFi:");
      for (int i = 0; i < n; ++i) 
      {
         // Print SSID and RSSI for each network found
         Serial.print(i + 1);
         Serial.print(": ");
         Serial.print(WiFi.SSID(i));
         Serial.print(" (");
         Serial.print(WiFi.RSSI(i));
         Serial.print(")");
         Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
         delay(10);
      }
   }
   Serial.println("");
   // Wait a bit before scanning again
   delay(10000);
}

