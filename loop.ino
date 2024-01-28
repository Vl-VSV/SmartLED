void loop() {
  milli = millis();
#if IR_REMOTE
  remoteTick();
#endif

#ifdef ESP8266
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
#endif

  if (timer_int(0, MAIN_LOOP)) {
    animation();

#if IR_REMOTE
    if (!IRLremote.receiving())
#endif
      FastLED.show();
  }
}