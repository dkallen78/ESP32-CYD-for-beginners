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
  
  // This if statement works because x1 and y1 are where the top-left
  // corner of the text would be if it were rendered with the cursor
  // position at the given coordinates (in this case 0, 0). Since the 
  // BB_SPI_LCD typeface draws from the top-left, the y1 value should 
  // also equal 0. But because the GFX typefaces draw up from the 
  // bottom-left, y1 (the top left corner of the rectangle that would
  // encompass the text) is offset by the height of the typeface. In 
  // this case, that would be less than 0.
  if (y1 == 0) {
    *y = scrMidY - (h / 2);
  } else {
    *y = scrMidY + (h / 2);
  }
  
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
