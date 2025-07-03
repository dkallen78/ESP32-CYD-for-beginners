#include <bb_spi_lcd.h>

BB_SPI_LCD lcd;

void setup() {
  lcd.begin(DISPLAY_CYD); 
  lcd.setTextColor(TFT_WHITE);
  lcd.println("Hello World");
}

void loop() {
  // put your main code here, to run repeatedly:

}
