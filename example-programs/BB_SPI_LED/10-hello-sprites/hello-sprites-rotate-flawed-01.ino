#include <bb_spi_lcd.h>

BB_SPI_LCD lcd, sprite1, sprite2;

void setup() {
  lcd.begin(DISPLAY_CYD);

  sprite1.createVirtual(132, 16);
  sprite1.setTextColor(TFT_RED);
  sprite1.setFont(FONT_12x16);
  sprite1.print("Hello World");

  sprite2.createVirtual(132, 16);

  sprite1.rotateSprite(&sprite2, 66, 8, 45);

  lcd.drawSprite(0, 0, &sprite2);
}

void loop() {

}