// Структура для хранения данных управления лентой.
struct LEDControlData {
  byte mode = 1;
  byte submode = 1;

  byte submodes_count[5] = { 0, 2, 5, 4, 9 };

  // Цвет
  byte a_red = 255;
  byte a_green = 255;
  byte a_blue = 255;

  // Настройки для режимов
  byte a_speed = 255;
  byte a_rainbow_step = 1;
  byte a_delay = 30;
  byte a_bright = 255;
  byte a_sat = 255;
  byte a_hue = 0;
  byte a_color = 0;
};