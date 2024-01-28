void one_color_all(byte hue, byte sat, byte val) {
  for (int i = 0; i < NUM_LEDS; i++) leds[i].setHSV(hue, sat, val);
}

void one_color_all_rgb(byte red, byte green, byte blue) {
  for (int i = 0; i < NUM_LEDS; i++) leds[i].setRGB(red, green, blue);
}

void colorWipe(byte num) {
  FastLED.clear();
  
  for(int i = 0; i < num; i++) {
    leds[i] = CRGB::Blue;
    FastLED.show();
  }
}

void new_rainbow_loop() {
  if (timer_int(2)) {
    led_control_data.color -= 1;
    fill_rainbow(leds, NUM_LEDS, led_control_data.color, led_control_data.RAINBOW_STEP);
  }
}

void confetti() {
  if (timer_int(2)) {
    led_control_data.color++;
    fadeToBlackBy(leds, NUM_LEDS, 10);
    int pos = random16(NUM_LEDS);
    leds[pos] += CHSV(led_control_data.color, led_control_data.LIGHT_SAT, 192);
  }
}

void sinelon() {
  if (timer_int(2)) {
    led_control_data.color++;
  }
  fadeToBlackBy(leds, NUM_LEDS, 20);
  int pos = beatsin16(13, 0, NUM_LEDS - 1);
  leds[pos] += CHSV(led_control_data.color, led_control_data.LIGHT_SAT, 192);
}

int counter = 0;
void Perlin(byte MIN_SAT, byte MAX_SAT, byte MIN_BRIGHT, byte MAX_BRIGHT, byte HUE_START1, char HUE_GAP, byte STEP, char plus_delay) {
  if (timer_int(2)) {
    for (int i = 0; i < NUM_LEDS; i++) {
      byte getColor = inoise8(i * STEP, counter);
      leds[i] = CHSV(HUE_START1 + led_control_data.HUE_EFFECT + map(getColor, 0, 255, 0, HUE_GAP),
                     map(getColor, 0, 255, MAX_SAT, MIN_SAT),
                     map(getColor, 0, 255, MIN_BRIGHT, MAX_BRIGHT));
    }
    counter += plus_delay;
  }
}

void running_lights() {
  if (led_control_data.submode < 3)
    led_control_data.color++;

  if (_pulse) {
    _pulse = false;

    for (byte i = 0; i < NUM_LEDS / 5; i++) {
      if (magnitude(i) == 0) {
        age(i) = 0;
        magnitude(i) = map(volF.fil, 40, 255, 0, 255);
        baseColor(i) = led_control_data.color;
        break;
      }
    }
  }

  one_color_all();

  if (led_control_data.submode == 1 || led_control_data.submode == 3)
    dance_party(NUM_LEDS / 2 + NUM_LEDS / 8);
  else
    dance_party(NUM_LEDS + NUM_LEDS / 4);
}

void dance_party(int MAX_AGE) {
  int pos;
  int age_full;

  for (byte i = 0; i < NUM_LEDS / 5; i++) {
    age_full = (age(i) + 256 * rnd(i));

    if (magnitude(i) > 0) {
      if (magnitude(i) > 200) pos = age_full;
      else pos = ((127 + (magnitude(i) / 2)) / 255.0) * age_full;

      if (led_control_data.submode == 1 || led_control_data.submode == 3) {
        leds[NUM_LEDS / 2 + pos] = CHSV(baseColor(i), led_control_data.LIGHT_SAT, map(age_full, 0, MAX_AGE, 255, 0));
        leds[NUM_LEDS / 2 - pos - 1] = CHSV(baseColor(i), led_control_data.LIGHT_SAT, map(age_full, 0, MAX_AGE, 255, 0));
      } else
        leds[pos] = CHSV(baseColor(i), led_control_data.LIGHT_SAT, map(age_full, 0, MAX_AGE, 255, 0));

      if (age(i) == 255) rnd(i)++;
      age(i)++;

      if ((age_full + 1 > MAX_AGE) || ((pos + 1 >= NUM_LEDS / 2) && (led_control_data.submode == 1 || led_control_data.submode == 3)) || (pos + 1 >= NUM_LEDS)) {
        magnitude(i) = 0;
        rnd(i) = 0;
      }
    }
  }
}