#include <bb_spi_lcd.h>

BB_SPI_LCD lcd, sprite;

void setup() {
  lcd.begin(DISPLAY_CYD); 
  lcd.fillScreen(TFT_BLUE);
  //
  // Notice the extra pixel I added to my virtual display. 
  //  I use this to leave a one-pixel blue rectangle on the 
  //  left of my sprite to do the same job my skinny rectangle
  //  was doing previously, namely, drawing over the remnants 
  //  of my previous render.
  sprite.createVirtual(141, 24);
  sprite.fillScreen(TFT_BLUE);
  //
  // Now when I make my virtual rectangle, I draw it one 
  //  pixel to the right of the origin so it leaves the little
  //  strip of blue to erase the old render as it "moves" 
  //  across the screen.
  sprite.fillRect(1, 0, 140, 24, TFT_YELLOW);
  //
  // This is all the same except for my setCursor() call which
  //  is pushed one pixel to the right to account for the extra
  //  row of pixels on the left.
  sprite.setFont(FONT_12x16);
  sprite.setTextColor(TFT_BLUE, TFT_YELLOW);
  sprite.setCursor(5, 4);
  sprite.print("Hello World");
}

void loop() {
  //
  // Sets a random y position between 0 (top of the screen) 
  //  and 225 (24 pixels less than the bottom row coordinate 
  //  of 239).
  int yPos = random(225);
  //
  // This delay just felt the smoothest to me.
  int delayTime = 3;
  //
  // I offset the initial x position left a number of pixels 
  //  equal to the length of the sprite and advance it until
  //  it's equal to the pixel width of the display.
  for (int xPos = -141; xPos <= 320; xPos++) {
    lcd.drawSprite(xPos, yPos, &sprite);
    delay(delayTime);
  }
}