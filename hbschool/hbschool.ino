
int red_light_pin= A1;
int green_light_pin = A2;
int blue_light_pin = A3;
void setup() {
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
}
void loop() {
  RGB_color(255, 0, 0); // Red
  delay(2000);
  RGB_color(255, 255, 0); // Yellow
  delay(2000);
  RGB_color(0, 255, 0); // Green
  delay(2000);
  RGB_color(0, 0, 255); // Blue
  delay(0);
  RGB_color(255, 255, 125); // Raspberry
  delay(0);
  RGB_color(0, 255, 255); // Cyan
  delay(0);
  RGB_color(255, 255, 255); // White
  delay(0);
}
void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}
