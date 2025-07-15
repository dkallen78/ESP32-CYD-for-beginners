#include <bb_spi_lcd.h>

BB_SPI_LCD lcd;

#define TOUCH_MISO 39
#define TOUCH_MOSI 32
#define TOUCH_CLK 25
#define TOUCH_CS 33

struct Button {
  int x1, y1, x2, y2;
  Button(int xa, int ya, int xb, int yb) {
    x1 = xa;
    y1 = ya;
    x2 = xb;
    y2 = yb;
  }
  bool click(int x, int y) {
    return (x >= x1 && x <= x2) && (y >= y1 && y <= y2);
  }
};

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
Button show(4, 4, 156, 88);
Button hide(164, 4, 316, 88);

void loop() {
  TOUCHINFO ti;
  
  if (lcd.rtReadTouch(&ti)) {
    if (show.click(ti.x[0], ti.y[0]) && !onScreen) {
      lcd.setTextColor(TFT_GREEN, TFT_BLACK);
      lcd.setCursor(94, 160);
      lcd.println("Hello World");
      onScreen = true;
    } else if (hide.click(ti.x[0], ti.y[0]) && onScreen) {
      lcd.fillRect(94, 160, 132, 16, TFT_BLACK);
      onScreen = false;
    }
  }
}
