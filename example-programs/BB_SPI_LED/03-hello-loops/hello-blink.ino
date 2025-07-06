#include <bb_spi_lcd.h>

BB_SPI_LCD lcd;

void setup() {
  lcd.begin(DISPLAY_CYD); 
  lcd.fillScreen(TFT_BLUE);

  lcd.fillRect(90, 108, 140, 24, TFT_YELLOW);

  lcd.setTextColor(TFT_BLUE, TFT_YELLOW);
  lcd.setFont(FONT_12x16);
  lcd.setCursor(94, 112);
  
  lcd.println("Hello World");
}

void loop() {
  delay(250);

  lcd.fillScreen(TFT_BLUE);

  delay(250);

  lcd.fillRect(90, 108, 140, 24, TFT_YELLOW);
  
  lcd.setCursor(94, 112);
  lcd.println("Hello World");
}
