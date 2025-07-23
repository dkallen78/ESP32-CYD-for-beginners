#include <bb_spi_lcd.h>

BB_SPI_LCD lcd, virt;

uint16_t virtBuffer[132 * 16];

#define TOUCH_MISO 39
#define TOUCH_MOSI 32
#define TOUCH_CLK 25
#define TOUCH_CS 33

struct Button {
  int w, h, x1, y1, x2, y2, color;

  Button(int _w, int _h, int _color) {
    w = _w;
    h = _h;
    color = _color;
  }

  void draw(int x, int y) {
    x1 = x;
    y1 = y;
    x2 = x + w;
    y2 = y + h;
    lcd.fillRect(x1, y1, w, h, color);
  }

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
  lcd.setTextColor(TFT_RED, TFT_BLACK);
  lcd.setFont(FONT_12x16);
  
  virt.createVirtual(132, 16, virtBuffer);
  virt.fillScreen(TFT_BLACK);
  virt.setTextColor(TFT_RED);
  virt.setFont(FONT_12x16);
  virt.print("Hello World");

}

void pushImg(int i) {
  lcd.pushImage(0, i, 132, 16, virtBuffer);
}

void drwSprt(int i) {
  lcd.drawSprite(0, i, &virt);
}

void printLine(int i) {
  lcd.setCursor(0, i);
  lcd.println("Hello World");
}

void loop() {
  TOUCHINFO ti;
  int drawMode = 0;
  

  Button printMode(136, 56, TFT_BLUE);
  printMode.draw(184, 4);
  printMode.text("Print Mode", 12);

  Button spriteMode(136, 56, TFT_BLUE);
  spriteMode.draw(184, 64);
  spriteMode.text("Sprite Mode", 12);

  Button pushMode(136, 56, TFT_BLUE);
  pushMode.draw(184, 124);
  pushMode.text("Push Mode", 12);

  Button output(136, 56, TFT_GREEN);
  output.draw(184, 184);
  //output.text("Print", 12);

  int yPos = 216;

  float rate;

  long start = millis();

  lcd.setTextColor(TFT_RED);

  while (true) {
    
    if (yPos > 215) {
      rate = millis() - start;
      lcd.setCursor(180, 204);
      lcd.setFont(FONT_8x8);
      output.text(String(1000 / rate), 8);
      lcd.setFont(FONT_12x16);
      lcd.setTextColor(TFT_RED);
      start = millis();

      yPos = -216;
    } else {
      yPos++;
    }

    if (yPos > 0) {
      lcd.drawRect(0, yPos - 1, 132, 1, TFT_BLACK);
    }

    if (lcd.rtReadTouch(&ti)) {
      if (printMode.click(ti.x[0], ti.y[0]) && (drawMode != 0)) {
        drawMode = 0;
        //output.draw(184, 184);
        //output.text("Print", 12);
        lcd.setTextColor(TFT_RED);
      } else if (spriteMode.click(ti.x[0], ti.y[0]) && (drawMode != 1)) {
        drawMode = 1;
        //output.draw(184, 184);
        //output.text("Sprite", 12);
      } else if (pushMode.click(ti.x[0], ti.y[0]) && (drawMode != 2)) {
        drawMode = 2;
        //output.draw(184, 184);
        //output.text("Push", 12);
      }
    }

    switch (drawMode) {
      case 0:
        printLine(abs(yPos));
        break;
      case 1:
        drwSprt(abs(yPos));
        break;
      case 2:
        pushImg(abs(yPos));
        break;
    }

  }
}
