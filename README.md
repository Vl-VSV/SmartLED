# Smart LED

## Описание проекта

Smart LED представляет собой систему светомузыки на базе Esp8266 и адресной светодиодной ленты. Также предусмотрены
статичные режимы подсветки. Для связи с умным домом используется MQTT брокер.

Для дополнительной информации читайте статью на [Habr](https://habr.com/ru/articles/811337/), где описан процесс создания и настройки проекта
подробнее.

## Cхемы

Основная схема подключения 5v ленты
![SmartLED_5v.jpg](Schemes%2FSmartLED_5v.jpg)
Также схемы подключения можно найти [тут](Schemes).

## Материалы и компоненты

### Обязательные

* WeMos D1 Mini
* Адресная лента
* PNP транзистор
* Источник питания
* Резисторы
* Конденсаторы

### Опциональные

* Кнопки для управления

## Настройки

Настройки находятся в файле `01_Settings.ino`

### Настройки брокера и WiFi

Для настройки брокера и WiFi в директории `ColorMusic_WiFi_VSV_Edition` откройте файл `settings.h`.  В нем нужно изменить:
* `ssid` - Название Wi-Fi сети
* `password` - Пароль от Wi-Fi сети
* `mqtt_server`, `mqtt_port`, `mqtt_user`, `mqtt_password` нужно взять с вкладки **"Брокер"** на [WQTT](https://www.wqtt.ru/)
    * `mqtt_server` - Адрес
    * `mqtt_port` - Порт
    * `mqtt_user` - Пользователь
    * `mqtt_password` - Пароль
*  *`led_topic` - это топик, который ведёт ко всем настройкам вашей ленты. Если вы следовали инструкции и скопировали все топики управления, то у вас он должен быть `"/home/room/led"` и изменять его не нужно.*

### Обязательные настройки

Обязательные настройки находятся в разделах «Обязательные настройки» и «Пины». Например `NUM_LEDS` - количество
светодиодов в ленте. 

У каждой настройки есть комментарий, объясняющий её использование.

### Настройки режимов

Список всех режимов можно найти в [таблицe](Mode_Table). Каждый режим имеет свои настройки.

Одновременно можно выбрать не более 10 режимов. Вы можете выбрать определённые режимы или изменить их порядок, настроив
массив `favorites_modes`.

```c++
const byte favorites_modes[][2] = {{1, 2}, {2, 1}, {2, 2}, {2, 4}, {3, 1}, {3, 3}, {4, 6}, {4, 7}, {4, 8}, {4, 9}};
```

## Макетная плата

Вы можете создать печатную плату для вашего проекта. [На сайте](https://oshwlab.com/voronins/backlight-small-2) можно
клонировать проект и изменить плату. Там представлена универсальная плата для одного из источников питания 12V или 5V.

При использовании 12V ленты потребуется источник питания 12V и стабилизатор напряжения.

## Планы

* Смоделировать корпус
* Добавить больше функций на кнопки

## Поддержка и Обратная связь

Вы можете связаться с автором проекта, используя любой способ, указанный в
его [аккаунте на GitHub](https://github.com/Vl-VSV).

Если у вас есть замечания, предложения или обнаружены проблемы с проектом, не стесняйтесь
открывать новые **Issues** на странице проекта на **GitHub**.
