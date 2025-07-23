#include <bb_spi_lcd.h>

BB_SPI_LCD lcd, sprite1, sprite2;

void setup() {
  //
  // Initialize the display and fill it with black
  lcd.begin(DISPLAY_CYD);
  lcd.fillScreen(TFT_BLACK);
  //
  // Initialize our first virtual display, fill it with
  //  black, and virtually render the text in the center
  //  of it.
  sprite1.createVirtual(132, 132);
  sprite1.fillScreen(TFT_BLACK);
  sprite1.setTextColor(TFT_RED);
  sprite1.setFont(FONT_12x16);
  sprite1.setCursor(0, 58);
  sprite1.print("Hello World");
  //
  // Initialize our second virtual display
  sprite2.createVirtual(132, 132);
}

void loop() {
  //
  // Count from 0 to 359, incrementing the angle by one degree
  //  each loop. Then rotate the first virtual display by that 
  //  angle, rendering the output on the second virtual display. 
  //  Finaly, draw the second virtual display to the screen.
  for (int angle = 0; angle < 360; angle++) {
    sprite1.rotateSprite(&sprite2, 66, 66, angle);
    lcd.drawSprite(94, 54, &sprite2);
  }
}