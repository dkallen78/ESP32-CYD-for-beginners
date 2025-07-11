#include <bb_spi_lcd.h>

BB_SPI_LCD lcd;

class TextBox {
  public:
    String text;
    int charWidth;
    TextBox(String txt, int chrWid) {
      text = txt;
      charWidth = chrWid;
    }
    int textWidth() {
      return text.length() * charWidth;
    }
    int boxWidth() {
      return textWidth() + 8;
    }
    int boxHeight() {
      return lcd.fontHeight() + 8;
    }
    int getXOffset(int width) {
      return 160 - (width / 2);
    }
};

void setup() {
  lcd.begin(DISPLAY_CYD); 
  lcd.fillScreen(TFT_BLUE);

  lcd.setTextColor(TFT_BLUE, TFT_YELLOW);
  lcd.setFont(FONT_12x16);
}

void drawTextBox(int yPos, TextBox textBox) {
  lcd.fillRect(textBox.getXOffset(textBox.boxWidth()), yPos, textBox.boxWidth(), textBox.boxHeight(), TFT_YELLOW);
  lcd.setCursor(textBox.getXOffset(textBox.textWidth()), yPos + 4);
  lcd.println(textBox.text);
}

void loop() {

  int delayTime = 1;
  TextBox textBox("Greetings Planet", 12);
  for (int i = 0; i <= 216; i++) {
    drawTextBox(i, textBox);
    delay(delayTime);
    lcd.fillRect(textBox.getXOffset(textBox.boxWidth()), i, textBox.boxWidth(), 1, TFT_BLUE);
  }

  for (int i = 216; i >= 0; i--) {
    drawTextBox(i, textBox);
    delay(delayTime);
    lcd.fillRect(textBox.getXOffset(textBox.boxWidth()), i + 24, textBox.boxWidth(), 1, TFT_BLUE);
  }
}