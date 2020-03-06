//www.diyusthad.com
#include <LiquidCrystal.h>

const int rs = 2, en = 3, d4 = 7, d5 = 8, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  lcd.print("Hallo Anton du");
  lcd.setCursor(0,1);
  lcd.print("hast heute M SA");
}

void loop() {
}
