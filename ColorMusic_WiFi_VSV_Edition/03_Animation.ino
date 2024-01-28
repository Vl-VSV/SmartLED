void animation() {
  byte this_mode = led_control_data.mode;
  byte this_submode = led_control_data.submode;

  if (this_mode == 3 || this_mode == 4)
    sound_level();

  switch (this_mode) {
    // 1.*
    case 1:
      switch (this_submode) {
        // 1.1 (Alice main)
        case 1:
          one_color_all_rgb(led_control_data.a_red, led_control_data.a_green, led_control_data.a_blue);
          break;
        // 1.2
        case 2:
          if (timer_int(2)) one_color_all(led_control_data.color++, led_control_data.LIGHT_SAT, 255);
          break;
      }
      break;

    // 2.*
    case 2:
      switch (this_submode) {
        case 1: new_rainbow_loop(); break;
        case 2: confetti(); break;
        case 3: sinelon(); break;
        case 4: Perlin(245, 255, 60, 255, 0, 24, NUM_LEDS, 32); break;
        case 5: Perlin(245, 255, 60, 255, 0, 21, 10, 25); break;
      }
      break;

    // 3.*
    case 3: running_lights(); break;

    // 4.*
    case 4:
      one_color_all(EMPTY_COLOR, 255, EMPTY_BRIGHT);
      if (timer_int(3, 30)) led_control_data.hue += led_control_data.RAINBOW_STEP;

      for (int j = 0; j < 2; j++) {
        for (int i = 0; i < (Slenght * !j + Slenght * j); i++) {
          int XXX = NUM_LEDS / 2 - 1 - i;
          if (j) XXX = NUM_LEDS / 2 + i;
          
          switch (this_submode) {
            case 1: leds[XXX] = ColorFromPalette(myPal, map(i, 0, NUM_LEDS / 2, 0, 241)); break;
            case 2: leds[XXX] = ColorFromPalette(RainbowStripeColors_p, map(i, 0, NUM_LEDS / 2, 0, 241)); break;
            case 3: leds[XXX] = ColorFromPalette(CloudColors_p, map(i, 0, NUM_LEDS / 2, 0, 241)); break;
            case 4: leds[XXX] = ColorFromPalette(PartyColors_p, map(i, 0, NUM_LEDS / 2, 0, 241)); break;
            case 5: leds[XXX] = ColorFromPalette(OceanColors_p, (map(i, 0, NUM_LEDS / 2, 0, 241)) / 2 - led_control_data.hue); break;
            case 6: leds[XXX] = ColorFromPalette(RainbowColors_p, (map(i, 0, NUM_LEDS / 2, 0, 241)) / 2 - led_control_data.hue); break;
            case 7: leds[XXX] = ColorFromPalette(LavaColors_p, (map(i, 0, NUM_LEDS / 2, 0, 241)) / 2 - led_control_data.hue); break;
            case 8: leds[XXX] = ColorFromPalette(ForestColors_p, (map(i, 0, NUM_LEDS / 2, 0, 241)) / 2 - led_control_data.hue); break;
            case 9: leds[XXX] = ColorFromPalette(HeatColors_p, (map(i, 0, NUM_LEDS / 2, 0, 241)) / 2 - led_control_data.hue); break;
          }
        }
      }
      break;
  }
}
//14,15,16,18