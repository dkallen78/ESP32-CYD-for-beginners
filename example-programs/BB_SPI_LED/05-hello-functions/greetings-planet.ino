#include <bb_spi_lcd.h>

BB_SPI_LCD lcd;

void setup() {
  lcd.begin(DISPLAY_CYD); 
  lcd.fillScreen(TFT_BLUE);

  lcd.setTextColor(TFT_BLUE, TFT_YELLOW);
  lcd.setFont(FONT_12x16);
}

void drawTextBox(int yPos, String text) {
  int charWidth = 12;

  int textWidth = text.length() * charWidth;
  int textHeight = lcd.fontHeight();

  int boxWidth = textWidth + 8;
  int boxHeight = textHeight + 8;

  int textXoffset = 160 - (textWidth / 2);
  int boxXoffset = 160 - (boxWidth / 2);

  lcd.fillRect(boxXoffset, yPos, boxWidth, boxHeight, TFT_YELLOW);
  lcd.setCursor(textXoffset, yPos + 4);
  lcd.println(text);
}

void loop() {

  int delayTime = 1;
  String text = "Greetings Planet";
  
  for (int i = 0; i <= 216; i++) {
    drawTextBox(i, text);
    delay(delayTime);
    lcd.fillRect(90, i, 140, 1, TFT_BLUE);
  }

  for (int i = 216; i >= 0; i--) {
    drawTextBox(i, text);
    delay(delayTime);
    lcd.fillRect(90, i + 24, 140, 1, TFT_BLUE);
  }
}