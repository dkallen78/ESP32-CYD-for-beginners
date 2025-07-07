#include <bb_spi_lcd.h>

BB_SPI_LCD lcd;

void setup() {
  lcd.begin(DISPLAY_CYD); 
  lcd.fillScreen(TFT_BLUE);

  lcd.setTextColor(TFT_BLUE, TFT_YELLOW);
  lcd.setFont(FONT_12x16);
}

void loop() {
  int x = random(180);
  int y = random(216);

  delay(250);

  lcd.fillRect(x, y, 140, 24, TFT_YELLOW);
  
  lcd.setCursor(x + 4, y + 4);
  lcd.println("Hello World");

  delay(250);

  for (int i = 0, j = 140; i <= 70; i++, j--) {
    delay(2);
    lcd.fillRect(x + i, y, 1, 24, TFT_BLUE);
    lcd.fillRect(x + j, y, 1, 24, TFT_BLUE);
  }
}
