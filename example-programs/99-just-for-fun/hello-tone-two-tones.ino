#include <bb_spi_lcd.h>
#include <string>
#include "pitches.h"

#define TOUCH_MISO 39
#define TOUCH_MOSI 32
#define TOUCH_CLK 25
#define TOUCH_CS 33

#define SOUND_PIN 26

int notes[89] = {33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 
                58, 62, 65, 69, 73, 78, 82, 87, 93, 98, 
                104, 110, 117, 123, 131, 139, 147, 156, 165, 175, 
                185, 196, 208, 220, 233, 247, 262, 277, 294, 311, 
                330, 349, 370, 392, 415, 440, 466, 494, 523, 554, 
                587, 622, 659, 698, 740, 784, 831, 880, 932, 988, 
                1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 
                1865, 1976, 2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 
                3322, 3520, 3729, 3951, 4186, 4435, 4699, 4978};

BB_SPI_LCD lcd;

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

void setup() {
  lcd.begin(DISPLAY_CYD);
  lcd.rtInit(TOUCH_MOSI, TOUCH_MISO, TOUCH_CLK, TOUCH_CS);

  lcd.fillScreen(TFT_BLACK);

  lcd.setFont(FONT_8x8);
}

void loop() {
  TOUCHINFO ti;

  long duration = 250;
  long gap = 250;
  int freq1 = 45;
  int freq2 = 57;
  bool press = false;
  bool playing = false;
  bool playNow = false;
  long base, pressTime;
  long pressGap = 200;
  int count = 0;

  //
  // Start and Stop buttons
  Button toneStartButton(160, 75, TFT_GREEN);
  toneStartButton.draw(80, 30, &lcd);
  toneStartButton.text("Start", TFT_BLACK, &lcd);

  Button toneStopButton(160, 75, TFT_RED);
  //
  // Duration buttons
  Button durUpButton(70, 25, TFT_GREY);
  durUpButton.draw(5, 30, &lcd);
  durUpButton.text("Up", TFT_BLACK, &lcd);

  Button durDisp(70, 25, TFT_BLACK);
  durDisp.draw(5, 55, &lcd);
  durDisp.text("Dur: %d", duration, TFT_WHITE, &lcd);

  Button durDownButton(70, 25, TFT_GREY);
  durDownButton.draw(5, 80, &lcd);
  durDownButton.text("Down", TFT_BLACK, &lcd);
  //
  // Gap buttons
  Button gapUpButton(70, 25, TFT_GREY);
  gapUpButton.draw(5, 135, &lcd);
  gapUpButton.text("Up", TFT_BLACK, &lcd);

  Button gapDisp(70, 25, TFT_BLACK);
  gapDisp.draw(5, 160, &lcd);
  gapDisp.text("Gap: %d", gap, TFT_WHITE, &lcd);

  Button gapDownButton(70, 25, TFT_GREY);
  gapDownButton.draw(5, 185, &lcd);
  gapDownButton.text("Down", TFT_BLACK, &lcd);
  //
  // Note1 buttons
  Button note1UpButton(70, 25, TFT_GREY);
  note1UpButton.draw(245, 30, &lcd);
  note1UpButton.text("Up", TFT_BLACK, &lcd);

  Button note1Disp(70, 25, TFT_BLACK);
  note1Disp.draw(245, 55, &lcd);
  note1Disp.text("Frq: %d", notes[freq1], TFT_WHITE, &lcd);

  Button note1DownButton(70, 25, TFT_GREY);
  note1DownButton.draw(245, 80, &lcd);
  note1DownButton.text("Down", TFT_BLACK, &lcd);
  //
  // Note2 buttons
  Button note2UpButton(70, 25, TFT_GREY);
  note2UpButton.draw(245, 135, &lcd);
  note2UpButton.text("Up", TFT_BLACK, &lcd);

  Button note2Disp(70, 25, TFT_BLACK);
  note2Disp.draw(245, 160, &lcd);
  note2Disp.text("Frq: %d", notes[freq2], TFT_WHITE, &lcd);

  Button note2DownButton(70, 25, TFT_GREY);
  note2DownButton.draw(245, 185, &lcd);
  note2DownButton.text("Down", TFT_BLACK, &lcd);

  while (true) {

    if (!playing && playNow) {
      switch (count % 2) {
        case 0:
          tone(SOUND_PIN, notes[freq1], duration);
          break;
        case 1:
          tone(SOUND_PIN, notes[freq2], duration);
          break;
      }
      //tone(SOUND_PIN, notes[freq], duration);
      playing = true;
    }

    if (((millis() - base) >= (duration + gap)) && playNow) {
      playing = false;
      base = millis();
      count++;
    }

    if (lcd.rtReadTouch(&ti)) {
      pressTime = (press) ? pressTime : millis();
      if (toneStartButton.click(&ti) && !playNow) {
        toneStartButton.wipe(TFT_BLACK, &lcd);
        toneStopButton.draw(80, 135, &lcd);
        toneStopButton.text("Stop", TFT_BLACK, &lcd);

        base = millis();
        playNow = true;
      } else if (toneStopButton.click(&ti)) {
        toneStopButton.wipe(TFT_BLACK, &lcd);
        toneStartButton.draw(80, 30, &lcd);
        toneStartButton.text("Start", TFT_BLACK, &lcd);

        playNow = false;
      } else if (durUpButton.click(&ti) && !press) {
        duration += (duration < 1000) ? 10 : 0;
        press = true;
        durDisp.wipeText(&lcd);
        durDisp.text("Dur: %d", duration, TFT_WHITE, &lcd);
      } else if (durDownButton.click(&ti) && !press) {
        duration -= (duration > 0) ? 10 : 0;
        press = true;
        durDisp.wipeText(&lcd);
        durDisp.text("Dur: %d", duration, TFT_WHITE, &lcd);
      } else if (gapUpButton.click(&ti) && !press) {
        gap += (gap < 1000) ? 10 : 0;
        press = true;
        gapDisp.wipeText(&lcd);
        gapDisp.text("Gap: %d", gap, TFT_WHITE, &lcd);
      } else if (gapDownButton.click(&ti) && !press) {
        gap -= (gap > 0) ? 10 : 0;
        press = true;
        gapDisp.wipeText(&lcd);
        gapDisp.text("Gap: %d", gap, TFT_WHITE, &lcd);
      } else if (note1UpButton.click(&ti) && !press) {
        freq1 += (freq1 < 88) ? 1 : 0;
        press = true;
        note1Disp.wipeText(&lcd);
        note1Disp.text("Frq: %d", notes[freq1], TFT_WHITE, &lcd);
      } else if (note1DownButton.click(&ti) && !press) {
        freq1 -= (freq1 > 0) ? 1 : 0;
        press = true;
        note1Disp.wipeText(&lcd);
        note1Disp.text("Frq: %d", notes[freq1], TFT_WHITE, &lcd);
      } else if (note2UpButton.click(&ti) && !press) {
        freq2 += (freq2 < 88) ? 1 : 0;
        press = true;
        note2Disp.wipeText(&lcd);
        note2Disp.text("Frq: %d", notes[freq2], TFT_WHITE, &lcd);
      } else if (note2DownButton.click(&ti) && !press) {
        freq2 -= (freq2 > 0) ? 1 : 0;
        press = true;
        note2Disp.wipeText(&lcd);
        note2Disp.text("Frq: %d", notes[freq2], TFT_WHITE, &lcd);
      } else if (((millis() - pressTime) > pressGap) && press) {
        press = false;
      } 
    } else if (press) {
      press = false;
    }

  }
}
