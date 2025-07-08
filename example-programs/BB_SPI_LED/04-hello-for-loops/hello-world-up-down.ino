#include <bb_spi_lcd.h>

BB_SPI_LCD lcd;

void setup() {
  lcd.begin(DISPLAY_CYD); 
  lcd.fillScreen(TFT_BLUE);

  lcd.setTextColor(TFT_BLUE, TFT_YELLOW);
  lcd.setFont(FONT_12x16);
}

void loop() {
  
  for (int i = 0; i <= 216; i++) {
    lcd.fillRect(90, i, 140, 24, TFT_YELLOW);
    lcd.setCursor(94, i + 4);
    lcd.println("Hello World");
    delay(1);
    lcd.fillRect(90, i, 140, 1, TFT_BLUE);
  }

  for (int i = 216; i >= 0; i--) {
    lcd.fillRect(90, i, 140, 24, TFT_YELLOW);
    lcd.setCursor(94, i + 4);
    lcd.println("Hello World");
    delay(1);
    lcd.fillRect(90, i + 24, 140, 1, TFT_BLUE);
  }
}