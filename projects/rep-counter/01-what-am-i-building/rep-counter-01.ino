#include <bb_spi_lcd.h>
#include <string>
//
// My button structure that I made to make it easier to
//  draw boxes and put stuff in them
struct Button {
  int w, h;
  int x1, y1, x2, y2;
  int tw, th;
  int tx, ty;
  int color;
  BB_SPI_LCD virt;

  Button(int _w, int _h, int _color) {
    w = _w;
    h = _h;
    color = _color;
    virt.createVirtual(w, h);
    virt.fillScreen(color);
  }

  void draw(int x, int y, BB_SPI_LCD *dest) {
    x1 = x;
    y1 = y;
    x2 = x + w;
    y2 = y + h;
    dest->drawSprite(x1, y1, &virt);
  }

  void wipe(int _color, BB_SPI_LCD *dest) {
    dest->fillRect(x1, y1, w, h, _color);
  }

  void wipeText(BB_SPI_LCD *dest) {
    //tw = (tw + tx >= dest->width()) ? dest->width() - tx - 1 : tw;
    dest->fillRect(tx, ty, tw, th, color);
  }

  void text(char *text, int _color, BB_SPI_LCD *dest) {
    int16_t _x1, _y1;
    uint16_t _w, _h;
    dest->getTextBounds(text, 0, 0, &_x1, &_y1, &_w, &_h);

    int x = ((x1 + x2) / 2) - (_w / 2);
    int y = (_y1 == 0) ? ((y1 + y2) / 2) - (_h / 2) : ((y1 + y2) / 2) + (_h / 2);

    tw = _w;
    th = _h;
    tx = x;
    ty = y;

    dest->setTextColor(_color, color);
    dest->setCursor(x, y);
    dest->println(text);
  }

  void text(char *text, int val, int _color, BB_SPI_LCD *dest) {
    //
    // Convert our integer val to a string
    std::string valString = std::to_string(val);
    // 
    // Convert our char array into a string and 
    //  pop off the int placeholder (%d)
    std::string textString(text);
    textString.pop_back();
    textString.pop_back();
    //
    // Concatenate our new strings
    std::string wholeString = textString + valString;

    int16_t _x1, _y1;
    uint16_t _w, _h;
    //
    // wholeString.c_str() makes a char array out
    //  of the strings we made
    dest->getTextBounds(wholeString.c_str(), 0, 0, &_x1, &_y1, &_w, &_h);

    int x = ((x1 + x2) / 2) - (_w / 2);
    int y = (_y1 == 0) ? ((y1 + y2) / 2) - (_h / 2) : ((y1 + y2) / 2) + (_h / 2);

    tw = _w;
    th = _h;
    tx = x;
    ty = y;

    dest->setTextColor(_color, color);
    dest->setCursor(x, y);
    dest->printf(text, val);
  }

  bool click(TOUCHINFO *ti) {
    return (ti->x[0] >= x1 && ti->x[0] <= x2) && (ti->y[0] >= y1 && ti->y[0] <= y2);
  }
};

BB_SPI_LCD lcd;

void setup() {
  lcd.begin(DISPLAY_CYD);
  lcd.setRotation(1);

  lcd.fillScreen(TFT_BLACK);
  //
  // I'll probably incorporate this into the Button struct
  //  in a future iteration since I don't think I'll be 
  //  printing any text outside of my button/display paradigm
  lcd.setFont(FONT_12x16);
  //
  // The buttons/displays
  Button exerciseDisp(320, 60, TFT_BLACK);
  exerciseDisp.draw(0, 0, &lcd);
  exerciseDisp.text("Pull-ups", TFT_BLUE, &lcd);

  Button exerciseRight(60, 180, TFT_GREY);
  exerciseRight.draw(259, 60, &lcd);
  exerciseRight.text(">", TFT_BLACK, &lcd);

  Button exerciseLeft(60, 180, TFT_GREY);
  exerciseLeft.draw(0, 60, &lcd);
  exerciseLeft.text("<", TFT_BLACK, &lcd);

  Button increment(160, 80, TFT_GREEN);
  increment.draw(80, 80, &lcd);
  increment.text("0", TFT_BLACK, &lcd);

  Button decrement(160, 50, TFT_RED);
  decrement.draw(80, 169, &lcd);
  decrement.text("X", TFT_BLACK, &lcd);
}

void loop() {

}
