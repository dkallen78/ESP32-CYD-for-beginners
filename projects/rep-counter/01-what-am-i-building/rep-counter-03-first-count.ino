#include <bb_spi_lcd.h>
#include <string>

#define TOUCH_MISO 39
#define TOUCH_MOSI 32
#define TOUCH_CLK 25
#define TOUCH_CS 33
//
// I added in the font declaration into the constructor
struct Button {
  int w, h;
  int x1, y1, x2, y2;
  int tw, th;
  int tx, ty;
  int color, font;
  BB_SPI_LCD virt;

  Button(int _w, int _h, int _color) {
    w = _w;
    h = _h;
    color = _color;
    virt.createVirtual(w, h);
    virt.fillScreen(color);
  }
  //
  // I made a separate constructor to include the font
  //  because I might want to omit it for some buttons 
  //  that I want to draw in instead of using a typeface
  Button(int _w, int _h, int _color, int _font) {
    w = _w;
    h = _h;
    color = _color;
    font = _font;
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
    dest->setFont(font);
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
    dest->setFont(font);
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
  lcd.rtInit(TOUCH_MOSI, TOUCH_MISO, TOUCH_CLK, TOUCH_CS);

  lcd.fillScreen(TFT_BLACK);
}

void loop() {

  int pullUpCount = 0;

  Button exerciseDisp(320, 60, TFT_BLACK, FONT_12x16);
  exerciseDisp.draw(0, 0, &lcd);
  exerciseDisp.text("Pull-ups", TFT_BLUE, &lcd);

  Button exerciseRight(60, 180, TFT_GREY, FONT_12x16);
  exerciseRight.draw(259, 60, &lcd);
  exerciseRight.text(">", TFT_BLACK, &lcd);

  Button exerciseLeft(60, 180, TFT_GREY, FONT_12x16);
  exerciseLeft.draw(0, 60, &lcd);
  exerciseLeft.text("<", TFT_BLACK, &lcd);

  Button repUp(160, 80, TFT_GREEN, FONT_12x16);
  repUp.draw(80, 80, &lcd);
  repUp.text("0", TFT_BLACK, &lcd);

  Button repDown(160, 50, TFT_RED, FONT_12x16);
  repDown.draw(80, 169, &lcd);
  repDown.text("X", TFT_BLACK, &lcd);

  TOUCHINFO ti;
  bool press = false;

  while(true) {
    //
    // If there is a touch ...
    if (lcd.rtReadTouch(&ti)) {
      // If the touch is in the repUp button and  
      //  nothing is currently being pressed ...
      if (repUp.click(&ti) && !press) {
        //
        // update the rep count, 
        // clear the displayed text
        // update with the new value
        // and set press to true
        pullUpCount++;
        repUp.wipeText(&lcd);
        repUp.text("%d", pullUpCount, TFT_BLACK, &lcd);
        press = true;
      //
      // if the touch is in the repDown button and
      //  nothing is currently being pressed ...
      } else if (repDown.click(&ti) && !press) {
        //
        // update the rep count (but not lower than 0),
        // clear the displayed text
        // update with the new value
        // and set press to true
        pullUpCount -= (pullUpCount > 0) ? 1 : 0;
        repUp.wipeText(&lcd);
        repUp.text("%d", pullUpCount, TFT_BLACK, &lcd);
        press = true;
      }
    //
    // If the screen is not being pressed ...
    } else if (press) {
      //
      // Set press to false
      press = false;
    }
  }
}
