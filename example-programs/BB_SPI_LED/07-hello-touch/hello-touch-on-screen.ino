#include <bb_spi_lcd.h>

BB_SPI_LCD lcd;

#define TOUCH_MISO 39
#define TOUCH_MOSI 32
#define TOUCH_CLK 25
#define TOUCH_CS 33

void setup() {
  lcd.begin(DISPLAY_CYD);
  lcd.rtInit(TOUCH_MOSI, TOUCH_MISO, TOUCH_CLK, TOUCH_CS);
  lcd.fillScreen(TFT_BLACK);
  lcd.setTextColor(TFT_GREEN, TFT_BLACK);
  lcd.setFont(FONT_16x32);
}

bool onScreen = false;

void loop() {
  TOUCHINFO ti;

  if (lcd.rtReadTouch(&ti) && !onScreen) {
    lcd.println("Hello World");
    onScreen = true;
  } else if (!lcd.rtReadTouch(&ti) && onScreen) {
    lcd.fillScreen(TFT_BLACK);
    onScreen = false;
  }
} 