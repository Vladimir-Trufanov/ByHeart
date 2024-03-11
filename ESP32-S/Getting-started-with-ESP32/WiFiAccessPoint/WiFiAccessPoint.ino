/* ========================================================================= */
/* WiFiAccessPoint.ino                    Created for esp32 on 04 July, 2018 */
/* (c) 2024-02-03 Труфанов Владимир            by Elochukwu Ifediora (fedy0) */
/*                                                                           */
/*             Cоздать точку доступа Wi-Fi и предоставить на ней веб-сервер. */
/* ========================================================================= */

/**
 * Скетч создает локальную сеть WiFi "yourAp" и небольшой сайт для управления 
 * светодиодом. Сеть можно закрыть паролем, можно оставить открытой.
 * 
 * После запуска скетча нужно:
 * 
 * 1. Подсоединиться к сети WiFi "YourAp" на компьютере, смартфоне или планшете.
 * 2. Запустить web-браузер и подключиться к локальному сайту "http://192.168.4.1"
 *    для того, чтобы можно было включать или выключать "лампочку".
 *    
 * Можно точно включить светодиод:   "http://192.168.4.1/H"
 * или выключить светодиод:          "http://192.168.4.1/L"
 * 
 * Можно воспользоваться терминалом PuTTY:
 *                          Run raw TCP "GET /H" and "GET /L" on PuTTY terminal 
 *                                with 192.168.4.1 as IP address and 80 as port
**/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

#define LED_BUILTIN 2   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED

// Назначаем идентификатор и пароль сети 
// (пароль должен быть более 7 символов или не назначаться) 
const char *ssid = "YourAp"; 
const char *password = ""; //"ax93k6kq6wf";

WiFiServer server(80);

void setup() 
{
   Serial.begin(115200);
   Serial.println();
   Serial.println("Configuring access point...");

   pinMode(LED_BUILTIN, OUTPUT);

   // Если пароль не задан, то строим сеть WiFi открытую,
   // иначе строим закрытую сеть
   bool isWiFi;
   //char y = *password;
   //if (*password == "") isWiFi=WiFi.softAP(ssid)
   //if (y == "") 
   
   isWiFi=WiFi.softAP(ssid);
   
   //else isWiFi=WiFi.softAP(ssid, password);

   if (!isWiFi) 
   {
      log_e("Soft AP creation failed.");
      while(1);
   }
   IPAddress myIP = WiFi.softAPIP();
   Serial.print("AP IP address: ");
   Serial.println(myIP);
   server.begin();

   Serial.println("Server started");
}

void loop() 
{
   // Прослушиваем всех клиентов
   WiFiClient client = server.available(); 
   // Если клиент найден, то начинаем с ним работать 
   if (client) 
   {                                      
      Serial.println("Новый клиент.");  // отмечаем нового клиета в мониторе последовательного порта
      String currentLine = "";          // создали строку для хранения входящих данных от клиента   
      // Работаем с клиентом, пока он подключен
      while (client.connected()) 
      {
         // Считываем байты, если они есть, от клиента        
         if (client.available()) 
         {            
            char c = client.read();     // прочитали байт
            Serial.write(c);            // вывели байт в последовательный порт монитора
            // Если пришел символ новой строки ("ПС" - перевод строки)
            if (c == '\n') 
            { 
               // Если текущая строка пуста, значит получили два символа новой строки подряд;
               // это означает, что HTTP-запрос клиента закончен, поэтому отправляем ответ                 
               if (currentLine.length() == 0) 
               {
                  // Отправляем заголовки HTTP, которые всегда начинаются с кода ответа 
                  // (например, HTTP/1.1 200 OK) и content-type, чтобы клиент знал, 
                  // какой будет вид ответа), затем пустая строка:
                  client.println("HTTP/1.1 200 OK");
                  client.println("Content-type:text/html");
                  client.println();
                  // Далее отправляем HTTP-сообщение текущей страницы
                  client.print("Щёлкните <a href=\"/H\">по этой ссылке,</a> чтобы ВКЛЮЧИТЬ светодиод<br>");
                  client.print("Кликните <a href=\"/L\">в этом месте,</a> чтобы выключить светодиод.<br>");
                  // HTTP-ответ заканчиваем еще одной пустой строкой:
                  client.println();
                  // Завершаем работу с клиентом, выходим из цикла
                  break;
               } 
               // Так как получили "ПС", чистим текущую строку
               else 
               {  
                  currentLine = "";
               }
            }
            // Так как пришел очередной символ и это не "ВК" (возврат каретки),
            // то добавляем символ к текущей строке 
            else if (c != '\r') 
            { 
               currentLine += c;    
            }
            // Проверяем, был ли в строке запрос клиента "GET /H" или "GET /L"
            if (currentLine.endsWith("GET /H")) 
            {
               digitalWrite(LED_BUILTIN, HIGH);   // GET /H turns the LED on
            }
            if (currentLine.endsWith("GET /L")) 
            {
               digitalWrite(LED_BUILTIN, LOW);    // GET /L turns the LED off
            }
         }
      }
      // Закрываем соединение
      client.stop();
      Serial.println("Client Disconnected.");
   }
}
