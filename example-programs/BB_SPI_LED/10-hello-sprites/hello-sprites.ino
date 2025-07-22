#include <bb_spi_lcd.h>

BB_SPI_LCD lcd, virt;

void setup() {
  lcd.begin(DISPLAY_CYD);

  virt.createVirtual(132, 16);
  virt.setTextColor(TFT_RED);
  virt.setFont(FONT_12x16);
  virt.print("Hello World");

  lcd.drawSprite(0, 0, &virt);
}

void loop() {

}