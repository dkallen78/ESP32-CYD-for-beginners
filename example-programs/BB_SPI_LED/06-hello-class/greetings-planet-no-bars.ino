#include <bb_spi_lcd.h>

BB_SPI_LCD lcd;

class TextBox {
  public:
    String text;
    int charWidth;
    int boxWidth() {
      return (text.length() * charWidth) + 8;
    }
    int boxHeight() {
      return lcd.fontHeight() + 8;
    }
    int textXoffset() {
      return 160 - ((text.length() * charWidth) / 2);
    }
    int boxXoffset() {
      return 160 - (boxWidth() / 2);
    }
};

void setup() {
  lcd.begin(DISPLAY_CYD); 
  lcd.fillScreen(TFT_BLUE);

  lcd.setTextColor(TFT_BLUE, TFT_YELLOW);
  lcd.setFont(FONT_12x16);
}

void drawTextBox(int yPos, TextBox textBox) {
  lcd.fillRect(textBox.boxXoffset(), yPos, textBox.boxWidth(), textBox.boxHeight(), TFT_YELLOW);
  lcd.setCursor(textBox.textXoffset(), yPos + 4);
  lcd.println(textBox.text);
}

void loop() {

  int delayTime = 1;
  TextBox textBox;
  textBox.text = "Greetings Planet";
  textBox.charWidth = 12;
  
  for (int i = 0; i <= 216; i++) {
    drawTextBox(i, textBox);
    delay(delayTime);
    lcd.fillRect(textBox.boxXoffset(), i, textBox.boxWidth(), 1, TFT_BLUE);
  }

  for (int i = 216; i >= 0; i--) {
    drawTextBox(i, textBox);
    delay(delayTime);
    lcd.fillRect(textBox.boxXoffset(), i + 24, textBox.boxWidth(), 1, TFT_BLUE);
  }
}