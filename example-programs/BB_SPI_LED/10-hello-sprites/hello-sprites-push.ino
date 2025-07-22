#include <bb_spi_lcd.h>

BB_SPI_LCD lcd, virt;

uint16_t buffer[132 * 16];

void setup() {
  lcd.begin(DISPLAY_CYD);

  virt.createVirtual(132, 16, buffer);
  virt.setTextColor(TFT_RED);
  virt.setFont(FONT_12x16);
  virt.print("Hello World");

  lcd.pushImage(0, 0, 132, 16, buffer);
}

void loop() {

}