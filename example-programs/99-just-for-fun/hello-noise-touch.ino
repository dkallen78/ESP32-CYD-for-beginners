#include <bb_spi_lcd.h>

#define TOUCH_MISO 39
#define TOUCH_MOSI 32
#define TOUCH_CLK 25
#define TOUCH_CS 33

#define SOUND_PIN 26

BB_SPI_LCD lcd;
//
// My latest riff on a button structure
struct Button {
  int w, h, x1, y1, x2, y2, color;
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

  void text(char *text, int _color, BB_SPI_LCD *dest) {
    int16_t _x1, _y1;
    uint16_t _w, _h;
    dest->getTextBounds(text, 0, 0, &_x1, &_y1, &_w, &_h);

    int x = ((x1 + x2) / 2) - (_w / 2);
    int y = (_y1 == 0) ? ((y1 + y2) / 2) - (_h / 2) : ((y1 + y2) / 2) + (_h / 2);

    dest->setTextColor(_color, color);
    dest->setCursor(x, y);
    dest->println(text);
  }

  bool click(int x, int y) {
    return (x >= x1 && x <= x2) && (y >= y1 && y <= y2);
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
  //
  // These are all the buttons or displays I'm going to use
  //
  // Start the repeating tone
  Button toneStartButton(160, 75, TFT_GREEN);
  toneStartButton.draw(80, 30, &lcd);
  toneStartButton.text("Start", TFT_BLACK, &lcd);
  //
  // Stop the repeating tone
  Button toneStopButton(160, 75, TFT_RED);
  //
  // Increase the duration of the tone
  Button durUpButton(70, 30, TFT_GREY);
  durUpButton.draw(5, 75, &lcd);
  durUpButton.text("Up", TFT_BLACK, &lcd);
  //
  // Decrease the duration of the tone
  Button durDownButton(70, 30, TFT_GREY);
  durDownButton.draw(5, 135, &lcd);
  durDownButton.text("Down", TFT_BLACK, &lcd);
  //
  // The area where the current duration is displayed
  Button durDisp(70, 30, TFT_BLACK);
  durDisp.draw(5, 105, &lcd);
  durDisp.text("Dur: 250", TFT_WHITE, &lcd);
  //
  // Increase the gap between tones
  Button gapUpButton(70, 30, TFT_GREY);
  gapUpButton.draw(245, 75, &lcd);
  gapUpButton.text("Up", TFT_BLACK, &lcd);
  //
  // Decrease the gap between tones
  Button gapDownButton(70, 30, TFT_GREY);
  gapDownButton.draw(245, 135, &lcd);
  gapDownButton.text("Down", TFT_BLACK, &lcd);
  //
  // the area where the current gab is displayed
  Button gapDisp(70, 30, TFT_BLACK);
  gapDisp.draw(245, 105, &lcd);
  gapDisp.text("Gap: 250", TFT_WHITE, &lcd);
  //
  // Initial values
  long duration = 250;
  long gap = 250;
  int freq = 440;
  bool press = false;

  while (true) {
    //
    // If the Start button is pressed, wipe the Start button, 
    //  display the Stop button, start counting milliseconds, 
    //  and make a variable to track whether or not a tone is playing
    if (lcd.rtReadTouch(&ti) && toneStartButton.click(ti.x[0], ti.y[0])) {

      toneStartButton.wipe(TFT_BLACK, &lcd);
      toneStopButton.draw(80, 135, &lcd);
      toneStopButton.text("Stop", TFT_BLACK, &lcd);

      long base = millis();
      
      bool playing = false;
      //
      // Until the Stop button is clicked, play the tone pattern
      //
      // Unfortunately, this blocks all other programming so no  
      //  changing the duration or gap while the pattern is playing :(
      while (!toneStopButton.click(ti.x[0], ti.y[0])) {
        lcd.rtReadTouch(&ti);
        //
        // If there's no tone playing and we're not in a gab, 
        //  play another tone and set the playing variable to true
        if (!playing) {
          tone(SOUND_PIN, freq, duration);
          playing = true;
        }
        //
        // If the set amount of time has passed between tones, reset 
        //  the counter and the play state
        if ((millis() - base) >= (duration + gap)) {
          playing = false;
          base = millis();
        }
      }
      //
      // If the Stop buttin is pressed and the loop ends, wipe the Stop
      //  button and redraw the Start button
      toneStopButton.wipe(TFT_BLACK, &lcd);
      toneStartButton.draw(80, 30, &lcd);
      toneStartButton.text("Start", TFT_BLACK, &lcd);
    // 
    // If the duration Up button is pressed, raise the duration, set 
    //  the press state to true (to prevent spamming the button), and 
    //  update the output in the duration display
    } else if (lcd.rtReadTouch(&ti) && durUpButton.click(ti.x[0], ti.y[0]) && !press) {
      duration += 10;
      press = true;
      durDisp.wipe(TFT_BLACK, &lcd);
      durDisp.text("dur: %d", duration, TFT_WHITE, &lcd);
      lcd.setTextColor(TFT_WHITE);
      lcd.setCursor(5, 116);
      lcd.printf("dur: %d", duration);
    //
    // duration Down button
    } else if (lcd.rtReadTouch(&ti) && durDownButton.click(ti.x[0], ti.y[0]) && !press) {
      duration -= 10;
      press = true;
      durDisp.wipe(TFT_BLACK, &lcd);
      lcd.setTextColor(TFT_WHITE);
      lcd.setCursor(5, 116);
      lcd.printf("dur: %d", duration);
    //
    // gap Up button
    } else if (lcd.rtReadTouch(&ti) && gapUpButton.click(ti.x[0], ti.y[0]) && !press) {
      gap += 10;
      press = true;
      gapDisp.wipe(TFT_BLACK, &lcd);
      lcd.setTextColor(TFT_WHITE);
      lcd.setCursor(245, 116);
      lcd.printf("gap: %d", gap);
    //
    // gap Down button
    } else if (lcd.rtReadTouch(&ti) && gapDownButton.click(ti.x[0], ti.y[0]) && !press) {
      gap -= 10;
      press = true;
      gapDisp.wipe(TFT_BLACK, &lcd);
      lcd.setTextColor(TFT_WHITE);
      lcd.setCursor(245, 116);
      lcd.printf("gap: %d", gap);
    //
    // If no button is pressed, reset the press state to false
    } else if (!lcd.rtReadTouch(&ti)) {
      press = false;
    }
  }

}
