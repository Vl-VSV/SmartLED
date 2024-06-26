void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    colorWipe(NUM_LEDS / 10);

    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  client.setKeepAlive(60);

  FastLED.clear();
  FastLED.show();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = WiFi.macAddress() + String(random(9999));
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
      Serial.println("connected");

      client.subscribe((led_topic + "/#").c_str());
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  String data;
  for (int i = 0; i < length; i++) {
    data += String((char)payload[i]);
  }
  // DEBUG
  Serial.print("Topic: ");
  Serial.println(topic);
  Serial.print("Data: ");
  Serial.println(data);

  handle_data(data, String(topic));
}

void turn_on_mode(const byte new_mode[]) {
  byte mode = new_mode[0];
  byte submode = new_mode[1];

  Serial.println("New mode: " + String(mode));
  Serial.println("New submode: " + String(submode));

  led_control_data.mode = mode;
  led_control_data.submode = submode;

  update_settings();
}

void update_settings() {
  byte mode = led_control_data.mode;
  byte submode = led_control_data.submode;

  switch (mode) {
    case 1:
      switch (submode) {
        case 1: FastLED.setBrightness(led_control_data.a_bright); break;
        case 2:
          led_control_data.a_delay = led_control_data.a_speed;
          led_control_data.a_sat = led_control_data.a_bright;
          break;
      }
      break;
    case 2:
      led_control_data.a_delay = led_control_data.a_speed;
      switch (submode) {
        case 1: led_control_data.a_rainbow_step = map(led_control_data.a_bright, 0, 255, 32, 1); break;
        case 2:
        case 3: led_control_data.a_sat = led_control_data.a_bright; break;
        case 4:
        case 5: led_control_data.a_hue = RGBtoHue(led_control_data.a_red, led_control_data.a_green, led_control_data.a_blue); FastLED.setBrightness(led_control_data.a_bright); break;
      }
      break;
    case 3:
      led_control_data.a_color = RGBtoHue(led_control_data.a_red, led_control_data.a_green, led_control_data.a_blue);
      led_control_data.a_sat = led_control_data.a_bright;

      break;
    case 4:
      volF.k = map(led_control_data.a_bright, 0, 255, 29, 31);

      if (submode >= 5) {
        led_control_data.a_delay = map(led_control_data.a_speed, 0, 255, 1, 30);
      }
      break;
  }
}

void handle_data(String data, String topic) {
  if (topic.equals(led_topic + "/mode")) {
    if (data == "one") {
      turn_on_mode(favorites_modes[0]);
    } else if (data == "two") {
      turn_on_mode(favorites_modes[1]);
    } else if (data == "three") {
      turn_on_mode(favorites_modes[2]);
    } else if (data == "four") {
      turn_on_mode(favorites_modes[3]);
    } else if (data == "five") {
      turn_on_mode(favorites_modes[4]);
    } else if (data == "six") {
      turn_on_mode(favorites_modes[5]);
    } else if (data == "seven") {
      turn_on_mode(favorites_modes[6]);
    } else if (data == "eight") {
      turn_on_mode(favorites_modes[7]);
    } else if (data == "nine") {
      turn_on_mode(favorites_modes[8]);
    } else if (data == "ten") {
      turn_on_mode(favorites_modes[9]);
    }

    return;
  }

  if (topic.equals(led_topic + "/speed")) {
    if (data == "min") {
      led_control_data.a_speed = 255;
    } else if (data == "slow") {
      led_control_data.a_speed = 192;
    } else if (data == "medium") {
      led_control_data.a_speed = 128;
    } else if (data == "fast") {
      led_control_data.a_speed = 64;
    } else if (data == "max") {
      led_control_data.a_speed = 0;
    }

    update_settings();
    return;
  }

  if (topic.equals(led_topic + "/power")) {
    controlPower(data);
    return;
  }

  if (topic.equals(led_topic + "/color")) {
    led_control_data.a_red = sutil::list::get(data, 0, ',');
    led_control_data.a_green = sutil::list::get(data, 1, ',');
    led_control_data.a_blue = sutil::list::get(data, 2, ',');

    led_control_data.mode = 1;
    led_control_data.submode = 1;

    return;
  }

  if (topic.equals(led_topic + "/brightness")) {
    led_control_data.a_bright = map(data.toInt(), 0, 100, 0, 255);

    update_settings();
    return;
  }
}