#include <bb_spi_lcd.h>
#include <string>

#define TOUCH_MISO 39
#define TOUCH_MOSI 32
#define TOUCH_CLK 25
#define TOUCH_CS 33

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
//
// This is the new exercise data struct. I might have 
//  to put more things in here down the road
struct ExData {
  char *name;
  int count;
};

BB_SPI_LCD lcd;

void setup() {
  lcd.begin(DISPLAY_CYD);
  lcd.setRotation(1);
  lcd.rtInit(TOUCH_MOSI, TOUCH_MISO, TOUCH_CLK, TOUCH_CS);

  lcd.fillScreen(TFT_BLACK);
}

void loop() {
  
  int current = 0;  // This tracks the currently displayed exercise

  ExData exercises[2];  // This is the array of ExData structs
  //
  // Populating my array of structs
  // In the future, I plan to have these either read from an 
  //  external file or input by the user; probably a mix of both
  exercises[0].name = "Pull-ups";
  exercises[0].count = 0;
  exercises[1].name = "Push-ups";
  exercises[1].count = 0;
  //
  // The index of the last item in my array
  // In the future this may not be needed depending on how I 
  //  structure my saved data
  int lastIndex = std::size(exercises) - 1; 

  Button exerciseDisp(320, 60, TFT_BLACK, FONT_12x16);
  exerciseDisp.draw(0, 0, &lcd);
  //
  // Updated the argument from a string literal to a variable
  exerciseDisp.text(exercises[current].name, TFT_BLUE, &lcd);

  Button exerciseLeft(60, 180, TFT_GREY, FONT_12x16);
  exerciseLeft.draw(0, 60, &lcd);
  exerciseLeft.text("<", TFT_BLACK, &lcd);

  Button exerciseRight(60, 180, TFT_GREY, FONT_12x16);
  exerciseRight.draw(259, 60, &lcd);
  exerciseRight.text(">", TFT_BLACK, &lcd);

  Button repUp(160, 80, TFT_GREEN, FONT_12x16);
  repUp.draw(80, 80, &lcd);
  //
  // Updated with new variable
  repUp.text("%d", exercises[current].count, TFT_BLACK, &lcd);

  Button repDown(160, 50, TFT_RED, FONT_12x16);
  repDown.draw(80, 169, &lcd);
  repDown.text("X", TFT_BLACK, &lcd);

  TOUCHINFO ti;
  bool press = false;

  while(true) {

    if (lcd.rtReadTouch(&ti)) {
      if (repUp.click(&ti) && !press) {
        exercises[current].count++;
        repUp.wipeText(&lcd);
        repUp.text("%d", exercises[current].count, TFT_BLACK, &lcd);
        press = true;
      } else if (repDown.click(&ti) && !press) {
        exercises[current].count -= (exercises[current].count > 0) ? 1 : 0;
        repUp.wipeText(&lcd);
        repUp.text("%d", exercises[current].count, TFT_BLACK, &lcd);
        press = true;
      //
      // If the left button is pressed and no press is active ...
      } else if (exerciseLeft.click(&ti) && !press) {
        //
        // Cycle the current index
        // Erase the current exerciseDisplay text
        // Update the exerciseDisplay text
        // Erase the current repUp text
        // Update the repUp text
        // Set press to true
        current = (current > 0) ? (current - 1) : lastIndex;
        exerciseDisp.wipeText(&lcd);
        exerciseDisp.text(exercises[current].name, TFT_BLUE, &lcd);
        repUp.wipeText(&lcd);
        repUp.text("%d", exercises[current].count, TFT_BLACK, &lcd);
        press = true;
      //
      // if the right button is pressed and no press is active ...
      } else if (exerciseRight.click(&ti) && !press) {
        current = (current < lastIndex) ? (current + 1) : 0;
        exerciseDisp.wipeText(&lcd);
        exerciseDisp.text(exercises[current].name, TFT_BLUE, &lcd);
        repUp.wipeText(&lcd);
        repUp.text("%d", exercises[current].count, TFT_BLACK, &lcd);
        press = true;
      }
    } else if (press) {
      press = false;
    }
  }
}
