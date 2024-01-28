#include "settings.h"

// ============================== ОБЯЗАТЕЛЬНЫЕ НАСТРОЙКИ ==============================================================================================

// Лента
#define NUM_LEDS 226  // Количество светодиодов
#define CURRENT_LIMIT 0 // Лимит по току, 0 - нет лимита

// Управление
// НАДО ФИКСИТЬ НА ESP8266
// #include <IRremoteESP8266.h>
#define IR_REMOTE 0  // ИК управление. 1 - включено, 0 - отключено

// Автонастройка нижнего порога шумов
#define AUTO_LOW_PASS 1

#ifdef ESP8266
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
#endif

const byte favorites_modes[][2] = {{1, 3}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {3, 1}, {3, 2}, {3, 3}, {3, 4}};
// =====================================================================================================================================================


// ============================== ВТОРИЧНЫЕ НАСТРОЙКИ ==================================================================================================

#define REMOTE_STEP 16

// Нижний порог шумов
uint16_t LOW_PASS = 70;      // Нижний порог шумов режим VU, ручная настройка
byte SPEKTR_LOW_PASS = 50;   // Нижний порог шумов режим спектра, ручная настройка
#define LOW_PASS_ADD 13      // "Добавочная" величина к нижнему порогу, для надёжности (режим VU)
#define LOW_PASS_FREQ_ADD 3  // "Добавочная" величина к нижнему порогу, для надёжности (режим частот)

// =====================================================================================================================================================


// ============================== Пины =================================================================================================================

#ifdef ESP8266
#define LED_PIN 2  // Пин DI светодиодной ленты D4
#define IR_PIN 5   // Пин ИК приёмника D1
#else
#define LED_PIN 12  // Пин DI светодиодной ленты
#define IR_PIN 2    // Пин ИК приёмника
#endif

#ifdef ESP8266
#define SOUND_MIC A0  // Пин микрофона на wemos mini
#else
#define SOUND_MIC A2  // Пин микрофона
#endif

// =====================================================================================================================================================


// ==================================Кнопки Пульта======================================================================================================

#if (IR_REMOTE)
#define BUTT_UP 0xA087E061
#define BUTT_DOWN 0xF4CC3E61
#define BUTT_LEFT 0xD97A3061
#define BUTT_RIGHT 0x6D266E61
#define BUTT_OK 0xD6656B61
#define BUTT_1 0x9251CA61
#define BUTT_2 0x8F3D0561
#define BUTT_3 0x25FE0861
#define BUTT_4 0xC82F5561
#define BUTT_5 0xC51A9061
#define BUTT_6 0x5BDB9361
#define BUTT_7 0xE6962861
#define BUTT_8 0xE3816361
#define BUTT_9 0x7A426661
#define BUTT_0 0x195EEE61
#define BUTT_STAR 0x1C73B361  // *
#define BUTT_HASH 0xB01FF161  // #
#endif

// =====================================================================================================================================================


// ============================== ДЛЯ РАЗРАБОТЧИКОВ ====================================================================================================

// ---------------- Библиотеки --------------------------------------------------------------------------

#include <FastLED.h>
CRGB leds[NUM_LEDS];

#if IR_REMOTE
#include <IRLremote.h>
CHashIR IRLremote;
volatile uint32_t IRdata;  // Переменная для ИК команд
#endif

#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <StringUtils.h>

WiFiClient espClient;
PubSubClient client(espClient);
#endif

// ---------------- Объявление переменных ---------------------------------------------------------------
LEDControlData led_control_data;

#define EMPTY_COLOR HUE_PURPLE
byte EMPTY_BRIGHT = 40;

// Градиент палитра
const TProgmemRGBPalette16 myPal PROGMEM = {
  0x00FF00, 0x00FF00, 0x6fff00, 0x9eff00,
  0xc3ff00, 0xe3ff00, 0xffff00, 0xffe000,
  0xffc000, 0xff9f00, 0xff7b00, 0xff5200,
  0xff0000, 0xff0000, 0xff0000, 0xFF0000
};

#define MAIN_LOOP 5

unsigned int milli;
unsigned int timer_arr_int[4];

#define WHITE_TEMP settings[0]
#define LIGHT_COLOR settings[0]
#define EFFECT_DELAY settings[0]

#define LIGHT_SAT settings[1]
#define RAINBOW_STEP settings[1]
#define HUE_EFFECT settings[1]


byte heat[NUM_LEDS + ((NUM_LEDS / 2) / 3 * 2) + 1];
#define age(x) (heat[x])
#define magnitude(x) (heat[x + (NUM_LEDS / 5)])
#define baseColor(x) (heat[x + (NUM_LEDS / 5) * 2])
#define rnd(x) (heat[x + (NUM_LEDS / 5) * 3])

byte Slenght;
// =====================================================================================================================================================


// =====================================================================================================================================================

// === Объявление всех использующихся функций для более быстрой и беспроблемной компиляции (на конечный размер скетча никак не влияет)==================

// --- Utility Functions --------------------------------------------------------------------------------------------------------------
void setupLED();
int smartIncr(int value, int incr_step, int mininmum, int maximum);
float smartIncrFloat(float value, float incr_step, float mininmum, float maximum);

// --- Animation ---------------------------------------------------------------------------------------------------------------------
void animation();

// --- Audio -----------------------------------------------------------------------------------------------------------------------
void analyzeAudio();
void autoLowPass();

// --- Remote -----------------------------------------------------------------------------------------------------------------------
void remoteTick();
void RemoteFunc(uint32_t IRdata);

// --- Effects -----------------------------------------------------------------------------------------------------------------------
void one_color_all(byte hue = 0, byte sat = 0, byte val = 0);

// --- Network -----------------------------------------------------------------------------------------------------------------------
void setup_wifi();

// =====================================================================================================================================================