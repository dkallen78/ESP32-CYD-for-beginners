#include <bb_spi_lcd.h>
#include "Calligraffitti_Regular_16.h"

BB_SPI_LCD lcd;

void getOffset(char *text, int *x, int *y) {
  int scrMidX = lcd.width() / 2;
  int scrMidY = lcd.height() / 2;

  int16_t x1, y1;
  uint16_t w, h;
  lcd.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);

  *x = scrMidX - (w / 2);
  *y = scrMidY + (h / 2);
}

void setup() {
  lcd.begin(DISPLAY_CYD); 
  lcd.fillScreen(TFT_BLACK);

  lcd.setFreeFont(&Calligraffitti_Regular_16);
  lcd.setTextColor(TFT_BLUE);
  char text[] = "Hello World";
  int x, y;
  getOffset(text, &x, &y);
  lcd.setCursor(x, y);
  lcd.println(text);
}

void loop() {

}
