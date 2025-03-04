# Universal Telegram Bot Library


![License](https://img.shields.io/github/license/witnessmenow/Universal-Arduino-Telegram-Bot)
![Release stable](https://badgen.net/github/release/witnessmenow/Universal-Arduino-Telegram-Bot/stable)

An Arduino IDE library for using Telegram Bot API. It's designed to be used with multiple Arduino architectures.

Join the [Arduino Telegram Library Group Chat](https://t.me/arduino_telegram_library) if you have any questions/feedback or would just like to be kept up to date with the library's progress.

## Help support what I do!

I have created a lot of different Arduino libraries that I hope people can make use of. [If you enjoy my work, please consider becoming a Github sponsor!](https://github.com/sponsors/witnessmenow/)

## Introduction

This library provides an interface for [Telegram Bot API](https://core.telegram.org/bots/api).

Telegram is an instant messaging service that allows for the creation of bots. Bots can be configured to send and receive messages. This is useful for Arduino projects as you can receive updates from your project or issue it commands via your Telegram app from anywhere.

Telegram - это сервис мгновенных сообщений, который позволяет создавать ботов. Боты могут быть настроены для отправки и получения сообщений. Это полезно для проектов Arduino, так как вы можете получать обновления от своего проекта или отдавать ему команды через приложение Telegram из любого места.

This is a library forked from [one library](https://github.com/Gianbacchio/ESP8266-TelegramBot) and inspired by [another](https://github.com/CasaJasmina/TelegramBot-Library)

Each library only supported a single type of Arduino and had different features implemented. The only thing that needs to be different for each board is the actual sending of requests to Telegram so I thought a library that additional architectures or boards could be configured easily would be useful, although this springs to mind:

Каждая библиотека поддерживала только один тип Arduino и имела реализованные различные функции. Единственное, что должно отличаться для каждой платы, - это фактическая отправка запросов в Telegram, поэтому я подумал, что была бы полезна библиотека, в которой можно было бы легко настроить дополнительные архитектуры или платы, хотя это приходит на ум:

![](https://imgs.xkcd.com/comics/standards.png "standards")

## Installing

The downloaded code can be included as a new library into the IDE selecting the menu:

```
 Sketch / include Library / Add .Zip library
```

You also have to install the ArduinoJson library written by [Benoît Blanchon](https://github.com/bblanchon). Search for it on the Arduino Library manager or get it from [here](https://github.com/bblanchon/ArduinoJson).

## Getting Started

To generate your new Bot, you need an Access Token. Talk to [BotFather](https://telegram.me/botfather) and follow a few simple steps described [here](https://core.telegram.org/bots#botfather).

Include UniversalTelegramBot in your project:

```ino
#include <UniversalTelegramBot.h>
```

and pass it a Bot token and a SSL Client (See the [examples](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot/tree/master/examples) for more details)

```ino
// Telegram BOT Token (Get from Botfather)
#define BOT_TOKEN "XXXXXXXXX:XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
```

## Features

Here is a list of features that this library covers. (Note: The examples link to the ESP8266 versions)

| Feature                      | Description                                                                                                                                                                                                                                                                                                                  | Usage                                                                                                                                                                                                                                                                                                        | Example                                                                                                                                                                                                                                                                                                                                                                                                                                                                     |
| ---------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| _Receiving Messages_         | Ваш бот может читать отправляемые ему сообщения. Это полезно для отправки команд на ваш arduino, таких как переключение светодиода | `int getUpdates(long offset)` <br><br> Gets any pending messages from Telegram and stores them in **bot.messages** . Offset should be set to **bot.last_message_received** + 1. Returns the numbers new messages received.                                                                                   | [FlashLED](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot/blob/master/examples/ESP8266/FlashLED/FlashLED.ino) or any other example                                                                                                                                                                                                                                                                                                                          |
| _Sending messages_           | Ваш бот может отправлять сообщения в любой Telegram или группу. Это может быть полезно, чтобы заставить arduino уведомлять вас о событии, например, о нажатии кнопки и т.д. (Примечание: боты могут отправлять вам сообщения только в том случае, если вы отправили их первыми) | `bool sendMessage(String chat_id, String text, String parse_mode = "")` <br><br> Sends the message to the chat_id. Returns if the message sent or not.                                                                                                                                                       | [EchoBot](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot/blob/master/examples/ESP8266/EchoBot/EchoBot.ino#L51) or any other example                                                                                                                                                                                                                                                                                                                         |
| _Reply Keyboards_            |  Ваш бот может отправлять  [ответные клавиши](https://camo.githubusercontent.com/2116a60fa614bf2348074a9d7148f7d0a7664d36/687474703a2f2f692e696d6775722e636f6d2f325268366c42672e6a70673f32), которые можно использовать как своего рода меню.                                                                                                        | `bool sendMessageWithReplyKeyboard(String chat_id, String text, String parse_mode, String keyboard, bool resize = false, bool oneTime = false, bool selective = false)` <br><br> Send a keyboard to the specified chat_id. parse_mode can be left blank. Will return true if the message sends successfully. | [ReplyKeyboard](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot/blob/master/examples/ESP8266/CustomKeyboard/ReplyKeyboardMarkup/ReplyKeyboardMarkup.ino)                                                                                                                                                                                                                                                                                                     |
| _Inline Keyboards_           | Your bot can send [inline keyboards](https://camo.githubusercontent.com/55dde972426e5bc77120ea17a9c06bff37856eb6/68747470733a2f2f636f72652e74656c656772616d2e6f72672f66696c652f3831313134303939392f312f324a536f55566c574b61302f346661643265323734336463386564613034). <br><br>Note: URLS & callbacks are supported currently | `bool sendMessageWithInlineKeyboard(String chat_id, String text, String parse_mode, String keyboard)` <br><br> Send a keyboard to the specified chat_id. parse_mode can be left blank. Will return true if the message sends successfully.                                                                   | [InlineKeyboard](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot/blob/master/examples/ESP8266/CustomKeyboard/InlineKeyboardMarkup/InlineKeyboardMarkup.ino)                                                                                                                                                                                                                                                                                                  |
| _Send Photos_                | Можно отправлять фотографии с вашего бота. Вы можете отправлять изображения из Интернета или непосредственно с arduino (была протестирована только отправка с SD-карты, но она должна быть способна отправлять с модуля камеры). | Check the examples for more info                                                                                                                                                                                                                                                                             | [From URL](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot/blob/master/examples/ESP8266/SendPhoto/PhotoFromURL/PhotoFromURL.ino)<br><br>[Binary from SD](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot/blob/master/examples/ESP8266/SendPhoto/PhotoFromSD/PhotoFromSD.ino)<br><br>[From File Id](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot/blob/master/examples/ESP8266/SendPhoto/PhotoFromFileID/PhotoFromFileID.ino) |
| _Chat Actions_               | Ваш бот может отправлять действия в чате, такие как ввод текста или отправка фотографии, чтобы пользователь знал, что бот что-то делает. | `bool sendChatAction(String chat_id, String chat_action)` <br><br> Send a the chat action to the specified chat_id. There is a set list of chat actions that Telegram support, see the example for details. Will return true if the chat actions sends successfully.                                         |
| _Location_                   | Ваш бот может получать данные о местоположении либо из одной точки данных о местоположении, либо из данных о реальном местоположении. | Check the example.                                                                                                                                                                                                                                                                                           | [Location](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot/tree/master/examples/ESP8266/Location/Location.ino)                                                                                                                                                                                                                                                                                                                                               |
| _Channel Post_               | Reads posts from channels.                                                                                                                                                                                                                                                                                                   | Check the example.                                                                                                                                                                                                                                                                                           | [ChannelPost](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot/tree/master/examples/ESP8266/ChannelPost/ChannelPost.ino)                                                                                                                                                                                                                                                                                                                                      |
| _Long Poll_                  | Можно указать, как долго бот будет проверять и ждать наличия нового сообщения, прежде чем возвращать своё сообщения.<br>Это уменьшит количество запросов и данных, используемых ботом, но это приведет к зависанию arduino во время ожидания сообщений| `bot.longPoll = 60;` <br><br> Where 60 is the amount of seconds it should wait                                                                                                                                                                                                                               | [LongPoll](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot/tree/master/examples/ESP8266/LongPoll/LongPoll.ino)                                                                                                                                                                                                                                                                                                                                               |
| _Update Firmware and SPIFFS_ | Вы можете обновить встроенное ПО и область spiffs с помощью отправки файлов в виде обычного файла с определенным заголовком.                                                                                                                                                                                                                         | `update firmware` <br>or<br>`update spiffs`<br> These are captions for example.                                                                                                                                                                                                                              | [telegramOTA](https://github.com/solcer/Universal-Arduino-Telegram-Bot/blob/master/examples/ESP32/telegramOTA/telegramOTA.ino)                                                                                                                                                                                                                                                                                                                                              | ``` |
| _Set bot's commands_         | You can set bot commands programmatically from your code. The commands will be shown in a special place in the text input area                                                                                                                                                                                               | `bot.setMyCommands("[{\"command\":\"help\", \"description\":\"get help\"},{\"command\":\"start\",\"description\":\"start conversation\"}]");`. See examples                                                                                                                                                  | [SetMyCommands](examples/ESP8266/SetMyCommands/SetMyCommands.ino)                                                                                                                                                                                                                                                                                                                                                                                                           |

The full Telegram Bot API documentation can be read [here](https://core.telegram.org/bots/api). Если есть функция, которую вы хотели бы добавить в библиотеку, пожалуйста, либо поднимите проблему на Github, либо, не стесняйтесь отправить запрос на извлечение.

## Other Examples

Some other examples are included you may find useful:

- BulkMessages : sends messages to multiple subscribers (ESP8266 only).

- UsingWifiManager : Same as FlashLedBot but also uses WiFiManager library to configure WiFi (ESP8266 only).

## License

![License](https://img.shields.io/github/license/witnessmenow/Universal-Arduino-Telegram-Bot)
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

Настоящим бесплатно предоставляется разрешение любому лицу, получающему копию данного программного обеспечения и связанные с ним файлы документации (“Программное обеспечение”), на работу с Программным обеспечением без ограничений, включая, без ограничений, права на использование, копирование, модификацию, объединение, публикацию, распространение, сублицензирование и/или продажу копии Программного обеспечения и разрешает лицам, которым предоставляется Программное обеспечение, делать это при соблюдении следующих условий: Вышеуказанное уведомление об авторских правах и данное уведомление о разрешении должны быть включены во все копии или существенные части программного обеспечения.

###### [к содержанию](../README.md)
