void setup() {
  Serial.begin(115200);

  setupLED();

#if USE_RELAY_ENABLED
  pinMode(RELAY_IN, OUTPUT);
#endif

#if AUTO_START_ENABLED
  controlPower("turnOn");
#endif

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