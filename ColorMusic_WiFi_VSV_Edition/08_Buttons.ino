#if USE_BUTTONS
void buttons_tick() {
  ok_button.tick();
  up_button.tick();
  down_button.tick();

  if (ok_button.click()) {
    fullLowPass();
    EEPROM.put(LOW_PASS_ADDRESS, LOW_PASS);
    EEPROM.commit();
  }

  if (up_button.click()) {
    if (led_control_data.submode == led_control_data.submodes_count[led_control_data.mode]) {
      led_control_data.mode = led_control_data.mode == 4 ? 1 : led_control_data.mode + 1;
      led_control_data.submode = 1;
    } else
      led_control_data.submode += 1;
  }

  if (down_button.click()) {
    if (led_control_data.submode == 1) {
      led_control_data.mode = led_control_data.mode == 1 ? 4 : led_control_data.mode - 1;
      led_control_data.submode = led_control_data.submodes_count[led_control_data.mode];
    } else
      led_control_data.submode -= 1;
  }
}
#endif