## ByHeart

### Страницы-шпаргалки для помощи при программировании Arduino и примеры последовательного изучения материала различных микроконтроллеров.


###### soderzhanie

### [Arduino UNO, как программатор](arduino-uno-kak-programmator/arduino-uno-kak-programmator.md)

### [DISPLAYS, OLED и другие дисплеи](displays/displays.md)

### [ESP32-CAM, библиотека и примеры для версии 1.0.6](esp32v106/ESP32v106.md)

### [FRITZING, как пользоваться, примеры и библиотеки](fritzing/Fritzing.md)

### [MYHEART, примеры и эксперименты для души, для сердца](myheart/MyHeart.md)

### [LEDS, светодиоды и ленты](leds/leds.md)

### [SENSORS, материалы по датчикам](sensors/Sensors.md)

### [TRANSISTORS, всё про транзисторы](transistors/Transistors.md)

### [UNIVERSALTELEGRAMBOT, Universal Telegram Bot Library](universaltelegrambot/Universaltelegrambot.md)

### [Пример ссылки внутри документа](#zastavlyaem-migat-lampochkami-esp32-cam)

### [САМОДЕЛКИ, что можно сделать для дома, для семьи -DDS](homemade/HomeMade.md)

###### [к содержанию](#soderzhanie)

<style>
razdel{color:#ab4a16; font-weight:700; font-size:1.3rem}
cod{color:#ab4a16;}
red { color: red }
yellow { color: yellow }
</style>

###### zastavlyaem-migat-lampochkami-esp32-cam

### <razdel>Способы окрашивания текста не для Markdown GitHub</razdel>

<red>Дистрибутивы и их тестирование (каталог Https)</red>

<span style="color:yellow">Содержимое каталога:</span>

<span style="color:green;">Your text here</span>

<cod>This is a paragraph.</cod>

### <razdel>Создание эффектов блочного различия в Markdown GitHub</razdel>

Одним из популярных синтаксисов для создания эффектов блочного сравнения в Markdown является синтаксис «GitHub-flavored Markdown», который использует тройные обратные кавычки для окружения измененного текста и добавляет строку текста, содержащую слово «diff», чтобы указать, что содержимое является diff. Измененный текст затем заключен в блок кода с соответствующим языковым тегом, таким как «diff» или «bash». Вот пример:

```diff
diff --git a/file.txt b/file.txt
index 62c73f1..ef5b7f9 100644
--- a/file.txt
+++ b/file.txt
@@ -1,+4 +4 @@
-Hello, world!
+Hello, Markdown!
 This is a sample file.
-It's in plain text format.
+It's in Markdown format.
```
В этом примере мы видим, что diff содержится в блоке кода, окруженном тройными обратными кавычками. Ключевое слово «diff» в первой строке указывает, что блок содержит diff. Затем изменения перечислены ниже, причем каждый раздел указывает на изменение в файле. Символы «-» и «+» указывают, была ли строка удалена или добавлена ​​соответственно.

###### [к содержанию](#soderzhanie)
