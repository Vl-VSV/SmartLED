// ============================== ОБЯЗАТЕЛЬНЫЕ НАСТРОЙКИ ==============================================================================================
// Настройки брокера и WiFi
#include "settings.h"

// Лента
#define LED_TYPE WS2812  // Тип ленты
#define NUM_LEDS 138     // Количество светодиодов
#define CURRENT_LIMIT 0  // Лимит по току, 0 - нет лимита

// Автонастройка нижнего порога шумов
#define AUTO_LOW_PASS 1

#define LED_COLOR_ORDER GRB // Если цвета на ленте перепутаны

#define EFFECT_DIRECTION_FROM_START 1  // 1 - Эффекты от начала к краю, 0 - От центра к краям

#define USE_BUTTONS 1 // 1 - Использование кнопок для управления, 0 - не используются

// ============================== Пины =================================================================================================================
#define LED_PIN 0     // Пин ленты
#define SOUND_MIC A0  // Пин микрофона

#if USE_BUTTONS
#define OK_BTN_PIN 12 // Пин кнопки OK
#define UP_BTN_PIN 13 // Пин кнопки UP
#define DOWN_BTN_PIN 14 // Пин кнопки DOWN
#endif
// =====================================================================================================================================================

// Избранные режимы, используются для управления режимами в Алисе
const byte favorites_modes[][2] = {{1, 2}, {2, 1}, {2, 2}, {2, 4}, {3, 1}, {3, 3}, {4, 6}, {4, 7}, {4, 8}, {4, 9}};

// Wi-Fi
const char* ssid = _ssid;
const char* password = _password;

// MQTT
const char* mqtt_server = _mqtt_server;
const int mqtt_port = _mqtt_port;
const char* mqtt_user = _mqtt_user;
const char* mqtt_password = _mqtt_password;

//Subscribe
const String led_topic = _led_topic;
// =====================================================================================================================================================

// ============================== ВТОРИЧНЫЕ НАСТРОЙКИ ==================================================================================================
// Нижний порог шумов
uint16_t LOW_PASS = 70;      // Нижний порог шумов режим VU, ручная настройка
#define LOW_PASS_ADD 13      // "Добавочная" величина к нижнему порогу, для надёжности
// =====================================================================================================================================================

// ============================== ДЛЯ РАЗРАБОТЧИКОВ ====================================================================================================
// ---------------- Библиотеки --------------------------------------------------------------------------
#include <FastLED.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <StringUtils.h>

#if USE_BUTTONS
#include <EncButton.h>
#endif
// ------------------------------------------------------------------------------------------------------

// ---------------- Объявление переменных ---------------------------------------------------------------
CRGB leds[NUM_LEDS];
LEDControlData led_control_data;

WiFiClient espClient;
PubSubClient client(espClient);

#define EMPTY_COLOR HUE_PURPLE
byte EMPTY_BRIGHT = 40;

// Градиент палитра для режима 4.1
const TProgmemRGBPalette16 myPal PROGMEM = {
  0x00FF00, 0x00FF00, 0x6fff00, 0x9eff00,
  0xc3ff00, 0xe3ff00, 0xffff00, 0xffe000,
  0xffc000, 0xff9f00, 0xff7b00, 0xff5200,
  0xff0000, 0xff0000, 0xff0000, 0xFF0000
};

#define MAIN_LOOP 5

unsigned int milli;
unsigned int timer_arr_int[4];

#if USE_BUTTONS
Button ok_button(OK_BTN_PIN);
Button up_button(UP_BTN_PIN);
Button down_button(DOWN_BTN_PIN);
#endif

byte heat[NUM_LEDS + ((NUM_LEDS / 2) / 3 * 2) + 1];
#define age(x) (heat[x])
#define magnitude(x) (heat[x + (NUM_LEDS / 5)])
#define baseColor(x) (heat[x + (NUM_LEDS / 5) * 2])
#define rnd(x) (heat[x + (NUM_LEDS / 5) * 3])

byte Slenght;
// =====================================================================================================================================================

// === Объявление всех использующихся функций для более быстрой и беспроблемной компиляции (на конечный размер скетча никак не влияет)==================

// --- Utility Functions --------------------------------------------------------------------------------------------------------------
void setupLED();
int smartIncr(int value, int incr_step, int mininmum, int maximum);
float smartIncrFloat(float value, float incr_step, float mininmum, float maximum);
bool timer_int(byte timer, int val);
bool isNum(String str);
byte RGBtoHue(byte red, byte green, byte blue);
void controlPower(String data);

// --- Animation ---------------------------------------------------------------------------------------------------------------------
void animation();

// --- Audio -----------------------------------------------------------------------------------------------------------------------
void autoLowPass();
void fullLowPass();
void sound_level();
bool tick(int read);

// --- Remote -----------------------------------------------------------------------------------------------------------------------
void remoteTick();
void RemoteFunc(uint32_t IRdata);

// --- Effects -----------------------------------------------------------------------------------------------------------------------
void one_color_all(byte hue = 0, byte sat = 0, byte val = 0);

// --- Network -----------------------------------------------------------------------------------------------------------------------
void setup_wifi();
// =====================================================================================================================================================