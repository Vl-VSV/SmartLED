#if IR_REMOTE
void remoteTick() {
  if (IRLremote.available()) {
    auto data = IRLremote.read();
    IRdata = data.command;

    RemoteFunc(IRdata);
  }
}
#endif

#if IR_REMOTE
void RemoteFunc(uint32_t IRdata) {
  byte last_mode = led_control_data.mode;
  byte last_submode = led_control_data.submode;

  switch (IRdata) {

    case BUTT_0: fullLowPass(); break;

    case BUTT_1:
      led_control_data.mode = 1;
      led_control_data.submode = 1;
      led_control_data.WHITE_TEMP = 90;
      led_control_data.LIGHT_SAT = 255;
      break;
    case BUTT_2:
      led_control_data.mode = 2;
      led_control_data.submode = 1;
      led_control_data.RAINBOW_STEP = 255;
      break;
    case BUTT_3:
      led_control_data.mode = 3;
      led_control_data.submode = 1;
      break;
    case BUTT_4:
      led_control_data.mode = 4;
      led_control_data.submode = 1;
      volF.k = 30;
      led_control_data.settings[1] = 1;
      break;

    case BUTT_UP:
      switch (last_mode) {
        case 1: led_control_data.settings[1] = smartIncr(led_control_data.settings[1], REMOTE_STEP, 0, 255); break;
        case 2:
          if (last_submode == 1)
            led_control_data.RAINBOW_STEP = smartIncr(led_control_data.RAINBOW_STEP, 1, 1, 255);
          else if (last_submode == 2)
            led_control_data.LIGHT_SAT = smartIncr(led_control_data.LIGHT_SAT, REMOTE_STEP, 0, 255);
          else
            led_control_data.HUE_EFFECT += REMOTE_STEP;
          break;
        case 3: led_control_data.LIGHT_SAT = smartIncr(led_control_data.LIGHT_SAT, REMOTE_STEP, 0, 255); break;
        case 4: led_control_data.settings[1] = smartIncr(led_control_data.settings[1], 1, 1, 20); break;
      }
      break;

    case BUTT_DOWN:
      switch (last_mode) {
        case 1: led_control_data.settings[1] = smartIncr(led_control_data.settings[1], -REMOTE_STEP, 0, 255); break;
        case 2:
          if (last_submode == 1)
            led_control_data.RAINBOW_STEP = smartIncr(led_control_data.RAINBOW_STEP, -1, 1, 255);
          else if (last_submode == 2)
            led_control_data.LIGHT_SAT = smartIncr(led_control_data.LIGHT_SAT, -REMOTE_STEP, 0, 255);
          else
            led_control_data.HUE_EFFECT -= REMOTE_STEP;
          break;
        case 3: led_control_data.LIGHT_SAT = smartIncr(led_control_data.LIGHT_SAT, -REMOTE_STEP, 0, 255); break;
        case 4: led_control_data.settings[1] = smartIncr(led_control_data.settings[1], -1, 1, 20); break;
      }
      break;

    case BUTT_RIGHT:
      switch (last_mode) {
        case 1:
          switch (last_submode) {
            case 1: led_control_data.WHITE_TEMP = smartIncr(led_control_data.WHITE_TEMP, -15, 0, 180); break;
            case 2: led_control_data.LIGHT_COLOR = led_control_data.LIGHT_COLOR - 8; break;
            default: led_control_data.EFFECT_DELAY = smartIncr(led_control_data.EFFECT_DELAY, -10, 80, 255); break;
          }
          break;
        case 2: led_control_data.EFFECT_DELAY = smartIncr(led_control_data.EFFECT_DELAY, -5, 1, 255); break;
        case 3: led_control_data.color -= REMOTE_STEP; break;
        case 4: volF.k = smartIncr(volF.k, -1, 10, 31); break;
      }
      break;

    case BUTT_LEFT:
      switch (last_mode) {
        case 1:
          switch (last_submode) {
            case 1: led_control_data.WHITE_TEMP = smartIncr(led_control_data.WHITE_TEMP, 15, 0, 180); break;
            case 2: led_control_data.LIGHT_COLOR = led_control_data.LIGHT_COLOR + 8; break;
            default: led_control_data.EFFECT_DELAY = smartIncr(led_control_data.EFFECT_DELAY, 10, 80, 255); break;
          }
          break;
        case 2: led_control_data.EFFECT_DELAY = smartIncr(led_control_data.EFFECT_DELAY, 5, 1, 255); break;
        case 3: led_control_data.color += REMOTE_STEP; break;
        case 4: volF.k = smartIncr(volF.k, 1, 10, 31); break;
      }
      break;

    case BUTT_HASH:
      led_control_data.submode = smartIncr(last_submode, 1, 1, led_control_data.maxSubmode[last_mode - 1]);
      break;

    case BUTT_STAR:
      led_control_data.submode = smartIncr(last_submode, -1, 1, led_control_data.maxSubmode[last_mode - 1]);
      break;
  }
}
#endif