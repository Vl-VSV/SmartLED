/*
   Цвето-цветомузыка на ESP8266 и адресной светодиодной ленте
 
   *******************************************************************
   Разработано: vsv070
   Страница проекта: https://github.com/Vl-VSV/SmartLED

   
   Проект основан на идее, представленной AlexGyver
   Страница проекта: http://alexgyver.ru/colormusic/

   Некоторые режимы подсветки были взяты из усовершенствованной версии проекта, созданной Slenk.
   Страница проекта: https://community.alexgyver.ru/threads/cvetomuzyka-na-arduino-fireedition.4683/
   *******************************************************************

   Версия 0.1.0:

Режимы:
+-----+--------------------------------+----------+--------------+------+
| №   | Режим                          | Скорость | Яркость      | Цвет |
+-----+--------------------------------+----------+--------------+------+
| 1.1 | Алиса                          |          | +            | +    |
| 1.2 | Плавная смета цвета            | +        | Насыщенность |      |
+-----+--------------------------------+----------+--------------+------+
| 2.1 | Плавная радуга                 | +        | Шаг радуги   |      |
| 2.2 | Конфетти                       | +        | Насыщенность |      |
| 2.3 | Бегающая точка со следами      | +        | Насыщенность |      |
| 2.4 | Огонь                          | +        | +            | +    |
| 2.5 | Лава                           | +        | +            | +    |
+-----+--------------------------------+----------+--------------+------+
| 3.1 | Многоцветные огоньки из центра |          | Насыщенность |      |
| 3.2 | Многоцветные огоньки с краю    |          | Насыщенность |      |
| 3.3 | Огоньки из центра              |          | Насыщенность | +    |
| 3.4 | Огоньки с краю                 |          | Насыщенность | +    |
+-----+--------------------------------+----------+--------------+------+
| 4.1 | Шкала громкости - Градиент     |          | Плавность    |      |
| 4.2 | Шкала громкости - Полоски      |          | Плавность    |      |
| 4.3 | Шкала громкости - Облака       |          | Плавность    |      |
| 4.4 | Шкала громкости - Вечеринка    |          | Плавность    |      |
| 4.5 | Шкала громкости - Океан        | +        | Плавность    |      |
| 4.6 | Шкала громкости - Радуга       | +        | Плавность    |      |
| 4.7 | Шкала громкости - Лава         | +        | Плавность    |      |
| 4.8 | Шкала громкости - Лес          | +        | Плавность    |      |
| 4.9 | Шкала громкости - Жара         | +        | Плавность    |      |
+-----+--------------------------------+----------+--------------+------+
*/

