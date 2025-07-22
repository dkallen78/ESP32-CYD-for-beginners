#include <bb_spi_lcd.h>

BB_SPI_LCD lcd, virt;

uint16_t virtBuffer[132 * 16];

#define TOUCH_MISO 39
#define TOUCH_MOSI 32
#define TOUCH_CLK 25
#define TOUCH_CS 33


struct Button {
  /*----------------------------------------------------//
  // A structure to handle common button-related tasks  //
  //----------------------------------------------------*/

  int w, h, x1, y1, x2, y2, color;

  Button(int _w, int _h, int _color) {
    /*----------------------------------------------------//
    // _w: width of the button in pixels                  //
    // _h: height of the button in pixels                 //
    // _color: color of the button in 565RGB              //
    //----------------------------------------------------*/

    w = _w;
    h = _h;
    color = _color;
  }

  void draw(int x, int y) {
    /*----------------------------------------------------//
    // Draws the button on the screen and saves the       //
    //  coordinates for the top-left and lower-right      //
    //  corners                                           //
    //----------------------------------------------------//
    // x: x coordinate of the top-left corner in which to //
    //  place the button in pixels                        //
    // y: y coordinate of the top-left corner in which to //
    //  place the button in pixels                        //
    //----------------------------------------------------*/

    x1 = x;
    y1 = y;
    x2 = x + w;
    y2 = y + h;
    lcd.fillRect(x1, y1, w, h, color);
  }

  void text(String txt, int chr) {
    /*----------------------------------------------------//
    // Centers and draws the text for the button          //
    //----------------------------------------------------//
    // txt: the text to be drawn                          //
    // chr: the length of each character in the typeface  //
    //  in pixels                                         //
    //----------------------------------------------------*/

    int x = ((x1 + x2) / 2) - ((txt.length() * chr) / 2);
    int y = ((y1 + y2) / 2) - (lcd.fontHeight() / 2);
    lcd.setTextColor(TFT_BLACK, color);
    lcd.setCursor(x, y);
    lcd.println(txt);
  }

  bool click(int x, int y) {
    /*----------------------------------------------------//
    // Determines whether a pair of coordinates are within//
    //  the bounds of the button                          //
    //----------------------------------------------------//
    // x: x value of the coordinate to check              //
    // y: y value of the coordinate to check              //
    //----------------------------------------------------//
    // return: true or false whether the coordinates are  //
    //  within the button                                 //
    //----------------------------------------------------*/

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
  /*----------------------------------------------------//
  // Draws the text on the screen using the pushImage() //
  //  method                                            //
  //----------------------------------------------------//
  // i: y coordinate at which to draw the text          //
  //----------------------------------------------------*/

  lcd.pushImage(0, i, 132, 16, virtBuffer);
}

void drwSprt(int i) {
  /*----------------------------------------------------//
  // Draws the text on the screen using the drawSprite()//
  //  method                                            //
  //----------------------------------------------------//
  // i: y coordinate at which to draw the text          //
  //----------------------------------------------------*/

  lcd.drawSprite(0, i, &virt);
}

void printLine(int i) {
  /*----------------------------------------------------//
  // Draws the text on the screen using the setCursor() //
  //  and println() methods                             //
  //----------------------------------------------------//
  // i: y coordinate at which to draw the text          //
  //----------------------------------------------------*/

  lcd.setCursor(0, i);
  lcd.println("Hello World");
}

void loop() {
  TOUCHINFO ti;
  int drawMode = 0;
  
  //
  // Draws the four buttons on the screen

  Button printMode(136, 56, TFT_BLUE);
  printMode.draw(184, 4);
  printMode.text("Print Mode", 12);

  Button spriteMode(136, 56, TFT_BLUE);
  spriteMode.draw(184, 64);
  spriteMode.text("Sprite Mode", 12);

  Button pushMode(136, 56, TFT_BLUE);
  pushMode.draw(184, 124);
  pushMode.text("Push Mode", 12);
  //
  // This one isn't really a button, I'm just hijacking
  // its ability to center text and wipe itself clean
  Button output(136, 56, TFT_GREEN);
  output.draw(184, 184);
  output.text("Print", 12);
  //
  // initial y position.
  int yPos = -216;

  lcd.setTextColor(TFT_RED);

  while (true) {
    //
    // If the y position goes over 215, reset it back to -216
    // otherwise, increment it by 1
    if (yPos > 215) {
      yPos = -216;
    } else {
      yPos++;
    }
    //
    // If the text is descending, draw a skinny rectangle to 
    // erase old pixels
    if (yPos > 0) {
      lcd.drawRect(0, yPos - 1, 132, 1, TFT_BLACK);
    }
    //
    // Logic to check for button presses, and if it's pressed,
    // to change the text of the output "button"
    if (lcd.rtReadTouch(&ti)) {
      if (printMode.click(ti.x[0], ti.y[0]) && (drawMode != 0)) {
        drawMode = 0;
        output.draw(184, 184);
        output.text("Print", 12);
        lcd.setTextColor(TFT_RED);
      } else if (spriteMode.click(ti.x[0], ti.y[0]) && (drawMode != 1)) {
        drawMode = 1;
        output.draw(184, 184);
        output.text("Sprite", 12);
      } else if (pushMode.click(ti.x[0], ti.y[0]) && (drawMode != 2)) {
        drawMode = 2;
        output.draw(184, 184);
        output.text("Push", 12);
      }
    }
    //
    // Uses a different method of drawing to the screen depending
    // on which button has been pressed
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
