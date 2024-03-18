void loop() {
  milli = millis();

#if USE_BUTTONS
  buttons_tick();
#endif

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (timer_int(0, MAIN_LOOP)) {
    animation();

    FastLED.show();
  }
}