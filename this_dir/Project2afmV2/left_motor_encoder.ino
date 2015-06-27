void doLeftEncoder()
{
  (digitalRead(left_encoder_pin_a)==digitalRead(left_encoder_pin_b) ? left_clicks--:left_clicks++);
}
