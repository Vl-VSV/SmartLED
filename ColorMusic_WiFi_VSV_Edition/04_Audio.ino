void autoLowPass() {
  delay(10); // ждём инициализации АЦП

  int thisMax = 0;  // максимум
  int thisLevel;

  for (byte i = 0; i < 200; i++) {  // делаем 200 измерений
    thisLevel = analogRead(SOUND_MIC);
    if (thisLevel > thisMax) thisMax = thisLevel;  // ищем максимумы и запоминаем
  }
  LOW_PASS = thisMax + LOW_PASS_ADD;  // нижний порог как максимум тишины + некая величина
}

// TODO: Edit this effect
void fullLowPass() {
  FastLED.setBrightness(0);
  FastLED.show();

  delay(100);
  autoLowPass();
  delay(100);

  FastLED.setBrightness(255);
}

//--- Analyze ---------------------------------------------------------------------------------------------------------
#define _volMin 0
#define _volMax 255
#define _window 2
#define _pulseMin 40
#define _pulseMax 60
#define _trsh 0

int _min = 30000, _max = 0, _ampli = 0, _raw = 0;
byte count;

bool _pulse = 0, _pulseState = 0;

struct FFilter {
  bool compute(bool force = false) {
    if (force || milli - tmr >= dt) {
      tmr = milli;
      uint8_t kk = (raw < fil) ? k : (k >> 1);
      fil = (kk * fil + (32 - kk) * raw) >> 5;
      return 1;
    }
    return 0;
  }
  uint8_t k = 20;
  int16_t dt = 0, fil = 0, raw = 0;
  uint16_t tmr = 0;
};
FFilter volF, ampF;

void sound_level() {
  if (tick(smartIncr(analogRead(SOUND_MIC), -LOW_PASS, 0, 1023)))
    Slenght = map(volF.fil, 0, 255, 0, EFFECT_DIRECTION_FROM_START ? NUM_LEDS : NUM_LEDS / 2);
}

bool tick(int read) {
  volF.compute();
  if (ampF.compute()) _ampli = 0;  // сглаживание амплитуды, сброс максимума

  _max = max(_max, read);  // поиск макс за выборку
  _min = min(_min, read);  // поиск мин за выборку

  if (++count >= _window) {      // выборка завершена
    _raw = _max - _min;          // сырая громкость
    _ampli = max(_ampli, _raw);  // амплитудная огибающая
    ampF.raw = _ampli;           // передаём в фильтр

    if (_raw > ampF.fil) ampF.compute(true);                    // форсируем фильтр
    if (_raw > _trsh && ampF.fil > _trsh) {                     // если звук громкий + в map не будет 0
      volF.raw = map(_raw, _trsh, ampF.fil, _volMin, _volMax);  // от порога _trsh до сглаженной амплитуды в (_volMin, _volMax)
      volF.raw = constrain(volF.raw, _volMin, _volMax);
      volF.compute(true);  // форсируем фильтр

      timer_arr_int[3] = milli;

    } else volF.raw = 0;

    if (!_pulseState) {
      if (volF.raw <= _pulseMin) _pulseState = 1;
    } else {
      if (volF.raw > _pulseMax) {
        _pulseState = 0;
        _pulse = 1;
      }
    }

    _max = count = 0;
    _min = 30000;
    return true;
  }
  return false;
}