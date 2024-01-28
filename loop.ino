void loop() {
  milli = millis();

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (timer_int(0, MAIN_LOOP)) {
    animation();

    FastLED.show();
  }
}