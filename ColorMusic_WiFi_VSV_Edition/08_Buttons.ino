void buttons_tick() {
  ok_button.tick();
  up_button.tick();
  down_button.tick();

  if (ok_button.isHold()) {
    fullLowPass();
  }
}