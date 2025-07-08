#include <bb_spi_lcd.h>

BB_SPI_LCD lcd;

void setup() {
  lcd.begin(DISPLAY_CYD); 
  lcd.fillScreen(TFT_BLUE);

  lcd.setTextColor(TFT_BLUE, TFT_YELLOW);
  lcd.setFont(FONT_12x16);
}

void loop() {
  
  int wipe;
  
  for (int i = -216; i <= 216; i++) {
    lcd.fillRect(90, abs(i), 140, 24, TFT_YELLOW);
    lcd.setCursor(94, abs(i) + 4);
    lcd.println("Hello World");
    delay(1);
    wipe = (i >= 0) ? 0 : 24;
    lcd.fillRect(90, abs(i) + wipe, 140, 1, TFT_BLUE);
  }
}