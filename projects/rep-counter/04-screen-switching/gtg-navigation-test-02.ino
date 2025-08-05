#include <bb_spi_lcd.h>
#include <string>
#include "Aclonica_Regular_16.h"
#include "Aclonica_Regular_32.h"

#define TOUCH_MISO 39
#define TOUCH_MOSI 32
#define TOUCH_CLK 25
#define TOUCH_CS 33

BB_SPI_LCD lcd;
TOUCHINFO ti;

struct Block {
  int w, h;
  int x1, y1, x2, y2;
  int tw, th;
  int tx, ty;
  int color, font;
  const GFXfont* gfx;
  BB_SPI_LCD sprite;
  BB_SPI_LCD* dest;

  Block(int _w, int _h, int _color) {
    w = _w;
    h = _h;
    color = _color;
    font = 0;
    tw = -1;
    sprite.createVirtual(w, h);
    sprite.fillScreen(color);

    //Serial.println("Block initialized ...");
  }

  void setFont(int _font) {
    font = _font;

    //Serial.println("font set ...");
  }

  void setFont(const GFXfont* _gfx) {
    gfx = _gfx;
    font = -1;

    //Serial.println("GFX font set ...");
  }

  void text(char *text, int _textColor) {

    if (tw > -1) {
      sprite.fillRect(tx, ty, tw, th, color);
    }

    if (font > -1) {
      sprite.setFont(font);
    } else {
      sprite.setFreeFont(gfx);
    }

    int16_t _x1, _y1;
    uint16_t _tw, _th;
    sprite.getTextBounds(text, 0, 0, &_x1, &_y1, &_tw, &_th);

    int offset = (_y1 == 0) ? 0 : _th + _y1;

    int x = (w / 2) - (_tw / 2);
    int y = (_y1 == 0) ? (h / 2) - (_th / 2) : (h / 2) + (_th / 2) - (offset / 2);

    tw = _tw;
    th = _th;
    tx = x;
    ty = (_y1 == 0) ? y : (y - th) + offset;

    sprite.setTextColor(_textColor, color);
    sprite.setCursor(x, y);
    sprite.println(text);

    //Serial.println("text set ...");
    //Serial.println(text);
  }

  void text(char *text, int val, int _textColor) {

    if (tw > -1) {
      sprite.fillRect(tx, ty, tw, th, color);
    }

    if (font > -1) {
      sprite.setFont(font);
    } else {
      sprite.setFreeFont(gfx);
    }

    std::string valString = std::to_string(val);
    std::string textString(text);
    textString.pop_back();
    textString.pop_back();

    std::string wholeString = textString + valString;

    int16_t _x1, _y1;
    uint16_t _tw, _th;
    sprite.getTextBounds(wholeString.c_str(), 0, 0, &_x1, &_y1, &_tw, &_th);

    int offset = (_y1 == 0) ? 0 : _th + _y1;

    int x = (w / 2) - (_tw / 2);
    int y = (_y1 == 0) ? (h / 2) - (_th / 2) : (h / 2) + (_th / 2) - (offset / 2);

    tw = _tw;
    th = _th;
    tx = x;
    ty = (_y1 == 0) ? y : (y - th) + offset;

    sprite.setTextColor(_textColor, color);
    sprite.setCursor(x, y);
    sprite.printf(text, val);
  }

  void textOutline(int pad, int xOff, int yOff, int rad, int color) {
    int bw = tw + (pad * 2);
    int bh = th + (pad * 2);
    int bx = tx - pad + xOff;
    int by = ty - pad + yOff;
    sprite.drawRoundRect(bx, by, bw, bh, rad, color);

    //Serial.println("outline drawn ...");
  }

  void draw(int x, int y, BB_SPI_LCD *_dest) {
    x1 = x;
    y1 = y;
    x2 = x + w;
    y2 = y + h;
    dest = _dest;
    _dest->drawSprite(x1, y1, &sprite);

    Serial.print("drawn to lcd at ");
    Serial.print(x);
    Serial.print(", ");
    Serial.println(y);
  }

  void draw() {
    dest->drawSprite(x1, y1, &sprite);

    Serial.println("drawn to lcd ...");
  }

  void clearVirt() {
    sprite.freeVirtual();
  }

  bool click(TOUCHINFO *ti) {
    return (ti->x[0] >= x1 && ti->x[0] <= x2) && (ti->y[0] >= y1 && ti->y[0] <= y2);
  }
};

void setup() {
  Serial.begin(115200);
  lcd.begin(DISPLAY_CYD);
  lcd.setRotation(1);
  lcd.rtInit(TOUCH_MOSI, TOUCH_MISO, TOUCH_CLK, TOUCH_CS);

  Serial.println("started...");
}

bool loopInit = false;
void loop() {

  int currentMode = 0;

  char *modeList[4] = {"Tracking", "Exercises", "Alarm", "Wi-Fi"};

  int lastIndex = std::size(modeList) - 1;

  lcd.fillScreen(TFT_BLACK);

  Block title(320, 60, TFT_BLACK);
  title.setFont(&Aclonica_Regular_16);
  title.text("Grease the Groove", TFT_BLUE);
  title.textOutline(8, 0, 1, 10, TFT_BLUE);
  title.textOutline(9, 0, 1, 11, TFT_BLUE);
  title.draw(0, 0, &lcd);

  Block mode(200, 180, TFT_BLACK);
  mode.setFont(&Aclonica_Regular_32);
  mode.text(modeList[currentMode], TFT_BLUE);
  mode.draw(60, 60, &lcd);

  Block modeLeft(60, 180, TFT_BLACK);
  modeLeft.setFont(FONT_16x32);
  modeLeft.text("<", TFT_BLUE);
  modeLeft.draw(0, 60, &lcd);

  Block modeRight(60, 180, TFT_BLACK);
  modeRight.setFont(FONT_16x32);
  modeRight.text(">", TFT_BLUE);
  modeRight.draw(259, 60, &lcd);

  bool press = false;
  bool inputLoop = true;

  while (inputLoop) {
    if (lcd.rtReadTouch(&ti)) {
      if (modeLeft.click(&ti) && !press) {
        currentMode = (currentMode > 0) ? (currentMode - 1) : lastIndex;
        mode.text(modeList[currentMode], TFT_BLUE);
        mode.draw();
        press = true;
      } else if (modeRight.click(&ti) && !press) {
        currentMode = (currentMode < lastIndex) ? (currentMode + 1) : 0;
        mode.text(modeList[currentMode], TFT_BLUE);
        mode.draw();
        press = true;
      } else if (mode.click(&ti) && !press) {
        inputLoop = false;
      }
    } else if (press) {
      press = false;
    }// if (lcd.rtReadTouch(&ti))
  } // while()
  title.clearVirt();
  mode.clearVirt();
  modeLeft.clearVirt();
  modeRight.clearVirt();
  switch(currentMode) {
    case 0:
      exercises();
      break;
    case 1:
      exercises();
      break;
    case 2:
      exercises();
      break;
    case 3:
      exercises();
      break;
  } // switch(currentMode)
} // loop()

void exercises() {
  lcd.fillScreen(TFT_BLACK);

  Block endLoop(50, 50, TFT_RED);
  endLoop.text("end", TFT_WHITE);
  endLoop.draw(0, 50, &lcd);

  bool inputLoop = true;

  while (inputLoop) {
    if (lcd.rtReadTouch(&ti)) {
      if (endLoop.click(&ti)) {
        inputLoop = false;
      }
    }
  }
  endLoop.clearVirt();
} // exercises()
