void setup() {
#ifdef ESP8266
  Serial.begin(115200);
#else
  Serial.begin(9600);
#endif

  setupLED();

#if IR_REMOTE
  IRLremote.begin(IR_PIN);
#endif

#if AUTO_LOW_PASS
  fullLowPass();
#endif

  FastLED.clear();

#ifdef ESP8266
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
#endif
}