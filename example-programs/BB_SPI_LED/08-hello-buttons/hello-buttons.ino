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

  lcd.setFont(FONT_12x16);

  lcd.fillRect(4, 4, 152, 84, TFT_GREEN);

  lcd.setTextColor(TFT_BLACK, TFT_GREEN);
  lcd.setCursor(56, 40);
  lcd.println("Show");

  lcd.fillRect(164, 4, 152, 84, TFT_RED);

  lcd.setTextColor(TFT_BLACK, TFT_RED);
  lcd.setCursor(216, 40);
  lcd.println("Hide");
}

bool onScreen = false;

void loop() {
  TOUCHINFO ti;
  if (lcd.rtReadTouch(&ti)) {
    if ((ti.x[0] >= 4 && ti.x[0] <= 156) && (ti.y[0] >= 4 && ti.y[0] <= 88) && !onScreen) {
      lcd.setTextColor(TFT_GREEN, TFT_BLACK);
      lcd.setCursor(94, 160);
      lcd.println("Hello World");
      onScreen = true;
    } else if ((ti.x[0] >= 164 && ti.x[0] <= 316) && (ti.y[0] >= 4 && ti.y[0]<= 88) && onScreen) {
      lcd.fillRect(94, 160, 132, 16, TFT_BLACK);
      onScreen = false;
    }
  }
}
