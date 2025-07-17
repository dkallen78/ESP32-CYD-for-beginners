#include <bb_spi_lcd.h>
#include "Calligraffitti_Regular_16.h"

BB_SPI_LCD lcd;

void setup() {
  lcd.begin(DISPLAY_CYD); 
  lcd.fillScreen(TFT_BLACK);
  lcd.setFreeFont(&Calligraffitti_Regular_16);
  lcd.setTextColor(TFT_BLUE);
  lcd.setCursor(0, 16);
  lcd.println("Hello World");
}

void loop() {

}
