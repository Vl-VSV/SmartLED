// Структура для хранения данных управления светодиодами.
struct LEDControlData {
  byte mode = 1;
  byte submode = 1;
  // Количество подрежимов для каждого из четырех основных режимов.
  byte maxSubmode[4] = { 4, 6, 4, 9 };

  byte color = 0;
  byte bright = 255;
  byte hue = 0;

  // Для хранения цвета режимов работы с Алисой
  byte a_red = 255;
  byte a_green = 255;
  byte a_blue = 255;

  byte a_bright = 255;
  byte a_speed = 255;

  byte settings[2] = { 90, 255 };
};