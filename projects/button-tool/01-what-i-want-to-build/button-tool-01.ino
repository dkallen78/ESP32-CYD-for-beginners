#include <bb_spi_lcd.h>
#include <queue>
#include <algorithm>

#define TOUCH_MISO 39
#define TOUCH_MOSI 32
#define TOUCH_CLK 25
#define TOUCH_CS 33

BB_SPI_LCD lcd;
TOUCHINFO ti;

void setup() {
  Serial.begin(115200);
  Serial.println("started...");
  lcd.begin(DISPLAY_CYD);
  lcd.fillScreen(TFT_BLACK);
  lcd.setRotation(1);
  lcd.rtInit(TOUCH_MOSI, TOUCH_MISO, TOUCH_CLK, TOUCH_CS);
  //
  // Draw target
  lcd.drawLine(156, 120, 164, 120, TFT_WHITE);
  lcd.drawLine(160, 116, 160, 124, TFT_WHITE);
  //
  // Simple instructions
  lcd.setTextColor(TFT_WHITE);
  lcd.setFont(FONT_12x16);
  lcd.setCursor(88, 0);
  lcd.print("Touch Target");

  lcd.setFont(FONT_8x8);
  
}
//
// My offset object
struct Offset {
  int max = 0;
  int min = 0;
  int current = 0;
  int count = 0;

  void avg(int num) {
    current = ((current * count) + num) / ++count;
  }
};

int x, y;
int redX, redY;
int redMax;
int oldMax = 0;
bool press = false;
int count = 0;
std::queue<int> xPix;
std::queue<int> yPix;

Offset xOffset, yOffset;

void loop() {

  if (lcd.rtReadTouch(&ti) && !press) {
    press = true;
    if (count == 0) {
      lcd.fillScreen(TFT_BLACK);
      
      lcd.drawRect(0, 0, 8, 8, TFT_RED);
      lcd.setCursor(10, 0);
      lcd.print("Min button size");
    }
    count++;
    //
    // Print the count
    lcd.setCursor(0, 40);
    lcd.printf("count: %d", count);
    //
    // Draw the target
    lcd.drawLine(156, 120, 164, 120, TFT_WHITE);
    lcd.drawLine(160, 116, 160, 124, TFT_WHITE);
    //
    // Basic x, y positional data
    x = ti.x[0];
    y = ti.y[0];
    //
    // Fill up the queue
    xPix.push(x);
    yPix.push(y);
    // 
    // If there have been at least 50 cycles, erase the
    //  oldest pixels
    if (count > 50) {
      lcd.drawPixel(xPix.front(), yPix.front(), TFT_BLACK);
      xPix.pop();
      yPix.pop();
    }
    //
    // Calculate the offset of the touch from the target
    xOffset.avg(160 - x);
    yOffset.avg(120 - y);
    //
    // Show position of corrected touch
    lcd.drawPixel(x + xOffset.current, y + yOffset.current, TFT_GREEN);
    //
    // Show position of raw touch
    lcd.drawPixel(x, y, TFT_RED);
    //
    // Max offsets to draw the red square
    if (x < 160) {
      xOffset.min = ((160 - x) > xOffset.min) ? (160 - x) : xOffset.min;
    } else {
      xOffset.max = ((x - 160) > xOffset.max) ? (x - 160) : xOffset.max;
    }
    
    if (y < 120) {
      yOffset.min = ((120 - y) > yOffset.min) ? (120 - y) : yOffset.min;
    } else {
      yOffset.max = ((y - 120) > yOffset.max) ? (y - 120) : yOffset.max;
    }
    //
    // Find the largest offset to draw the maximum size of the square
    redMax = std::max({xOffset.min, xOffset.max, yOffset.min, yOffset.max});
    //
    // If the largest offset for the current touch is larger than the previous
    //  largest max offset, erase the previous red square and draw a new one
    if (redMax > oldMax) {
      lcd.drawRect(160 - oldMax, 120 - oldMax, oldMax * 2, oldMax * 2, TFT_BLACK);
      lcd.drawRect(160 - redMax, 120 - redMax, redMax * 2, redMax * 2, TFT_RED);
      oldMax = redMax;
    }
    //
    // Print the current smallest button size
    lcd.setCursor(160, 0);
    lcd.printf("button size: %dx%d", redMax * 2, redMax * 2);
    //
    // Print the offsets
    lcd.setCursor(0, 10);
    lcd.printf("-x: %d", xOffset.min);

    lcd.setCursor(56, 10);
    lcd.printf("+x: %d", xOffset.max);

    lcd.setCursor(160, 10);
    lcd.printf("-y: %d", yOffset.min);

    lcd.setCursor(216, 10);
    lcd.printf("+y: %d", yOffset.max);
    //
    // Print the averages
    lcd.setCursor(0, 20);
    lcd.printf("x offset: %d", xOffset.current);

    lcd.setCursor(160, 20);
    lcd.printf("y offset: %d", yOffset.current);

  } else if (!lcd.rtReadTouch(&ti)) {
    press = false;
  }
}
