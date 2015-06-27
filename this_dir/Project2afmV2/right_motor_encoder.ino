void doRightEncoder()
{
  (digitalRead(right_encoder_pin_a)==digitalRead(right_encoder_pin_b) ? right_clicks--:right_clicks++);
}
