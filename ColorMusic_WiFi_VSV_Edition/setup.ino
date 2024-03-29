void setup() {
  Serial.begin(115200);
  EEPROM.begin(sizeof(LOW_PASS));

  setupLED();

#if AUTO_LOW_PASS_ON_START
  EEPROM.get(LOW_PASS_ADDRESS, LOW_PASS);
  if (LOW_PASS == 0xFFFF) {
    fullLowPass();
    EEPROM.put(LOW_PASS_ADDRESS, LOW_PASS);
    EEPROM.commit();
  }
#endif

  FastLED.clear();

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}