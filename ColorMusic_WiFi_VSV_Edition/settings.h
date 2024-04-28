// settings.h

#ifndef SETTINGS_H
#define SETTINGS_H

// Wi-Fi
const char* _ssid = ""; // Название Wi-Fi сети
const char* _password = ""; // Пароль от Wi-Fi сети

// MQTT
const char* _mqtt_server = ""; // Адрес

const int _mqtt_port = 0; // Порт
const char* _mqtt_user = ""; // Пользователь
const char* _mqtt_password = ""; // Пароль

// Subscribe
const String _led_topic = "/home/room/led";

#endif  // SETTINGS_H
