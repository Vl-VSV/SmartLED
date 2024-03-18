void setup() {
  Serial.begin(115200);

  setupLED();

#if AUTO_LOW_PASS
  fullLowPass();
#endif

#if USE_BUTTONS
  setupButtons();
#endif

  FastLED.clear();

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}