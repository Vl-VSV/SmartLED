#define CORRECTION 0xFFFFFF  // Корректировка оттенка (что бы белый был БЕЛЫМ). Ниже есть стандартные варианты.
/*  Типовые значения: TypicalSMD5050      = 0xFFB0F
                      Typical8mmPixel     = 0xFFE08C
                      TypicalLEDStrip     = 0xFFB0F0
                      TypicalPixelString  = 0xFFE08C
                      UncorrectedColor    = 0xFFFFFF - этот отменит всякую корректировку (рекомендуется)        
*/

// Функция для начальной настройки ленты
void setupLED() {
  FastLED.addLeds<LED_TYPE, LED_PIN, LED_COLOR_ORDER>(leds, NUM_LEDS).setCorrection(CORRECTION);
  if (CURRENT_LIMIT > 0) FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
  FastLED.setBrightness(255);
}

// Функция изменяет величину value на шаг incr в пределах minimum .. maximum
int smartIncr(int value, int incr_step, int mininmum, int maximum) {
  int val_buf = value + incr_step;
  val_buf = constrain(val_buf, mininmum, maximum);
  return val_buf;
}

// Функция изменяет величину value на шаг incr в пределах minimum .. maximum
float smartIncrFloat(float value, float incr_step, float mininmum, float maximum) {
  float val_buf = value + incr_step;
  val_buf = constrain(val_buf, mininmum, maximum);
  return val_buf;
}

// Функция проверки времени прошедшего с момента последнего срабатывания таймера.
// Возвращает true, если прошло больше времени, чем указанная задержка, иначе false.
bool timer_int(byte timer = 0, int val = led_control_data.a_delay) {
  if (milli - timer_arr_int[timer] > val) {
    timer_arr_int[timer] = milli;
    return true;
  }
  return false;
}

// Функция проверки, является ли переданная строка числом.
// Возвращает true, если все символы в строке - цифры, иначе false.
bool isNum(String str) {
  for (auto c : str) {
    if (!isDigit(c))
      return false;
  }
  return true;
}

byte RGBtoHue(byte red, byte green, byte blue) {
  float r = red / 255.0;
  float g = green / 255.0;
  float b = blue / 255.0;

  byte maximum = max(r, max(g, b));
  byte minimum = min(r, min(g, b));

  if (maximum == r)
    return map(((g - b) / (maximum - minimum)) * 60.0, 0, 360, 0, 255);
  else if (maximum == g)
    return map((2.0 + (b - r) / (maximum - minimum)) * 60.0, 0, 360, 0, 255);
  return map((4.0 + (r - g) / (maximum - minimum)) * 60.0, 0, 360, 0, 255);
}

void controlPower(String data) {
#if USE_RELAY_ENABLED
  if (data == "turnOn") {
    digitalWrite(RELAY_IN, HIGH);
  } else {
    digitalWrite(RELAY_IN, LOW);
  }
#else
  if (data == "turnOn") {
    FastLED.setBrightness(255);
  } else {
    FastLED.setBrightness(0);
  }
#endif
}