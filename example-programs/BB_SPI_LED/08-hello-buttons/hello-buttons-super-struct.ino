#include <bb_spi_lcd.h>

BB_SPI_LCD lcd;

#define TOUCH_MISO 39
#define TOUCH_MOSI 32
#define TOUCH_CLK 25
#define TOUCH_CS 33

struct Button {
  // I still have my x and y values because they're useful in 
  // other methods, but I've added w, h, and color
  int w, h, x1, y1, x2, y2, color;
  // The constructor parameters use the underscore so they
  // can be similar to the Button attributes, but different
  // enough that there's no naming conflicts
  Button(int _w, int _h, int _color) {
    w = _w;
    h = _h;
    color = _color;
  }
  // Only takes coordinates for the top-left corner, but I still
  // calculate the top-left and bottom-right coordinates so 
  // that they're available to the text() method. 
  // This isn't ideal because calling the text() or click() 
  // methods before draw() will cause unintended consequences :(
  void draw(int x, int y) {
    x1 = x;
    y1 = y;
    x2 = x + w;
    y2 = y + h;
    lcd.fillRect(x1, y1, w, h, color);
  }
  // This finds the midpoint of the button and offsets the text so
  // that it displays in the center
  void text(String txt, int chr) {
    int x = ((x1 + x2) / 2) - ((txt.length() * chr) / 2);
    int y = ((y1 + y2) / 2) - (lcd.fontHeight() / 2);
    lcd.setTextColor(TFT_BLACK, color);
    lcd.setCursor(x, y);
    lcd.println(txt);
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
}

void loop() {
  TOUCHINFO ti;
  // onScreen, show, and hide can now be in the loop() function
  // because our main logic is inside another loop. If they weren't, 
  // onScreen would always be false except for whenever the show 
  // button was touched, and even then it would flicker. There would
  // be a lot of flicker because the buttons would also be redrawn 
  // every time the loop cycled
  bool onScreen = false;

  Button show(152, 84, TFT_GREEN);
  show.draw(4, 4);
  show.text("Reveal", 12);

  Button hide(152, 84, TFT_RED);
  hide.draw(164, 4);
  hide.text("Obscure", 12);
  // Everything that was in the loop() function before, is now
  // inside this while statement. while (true) just ensures that
  // it loops forever
  while (true) {
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
  
}
