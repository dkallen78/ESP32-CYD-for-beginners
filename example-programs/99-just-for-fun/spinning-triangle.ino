#include <bb_spi_lcd.h>

#define PI 3.1415

BB_SPI_LCD lcd;

void setup() {
  lcd.begin(DISPLAY_CYD);
  lcd.fillScreen(TFT_BLACK);
}

float deg2rad(int deg) {
  /*----------------------------------------------------//
  // Converts degrees into radians                      //
  //----------------------------------------------------//
  // deg: degrees to be converted                       //
  //----------------------------------------------------//
  // return: radians converted from degrees             //
  //----------------------------------------------------*/

  return deg * (PI / 180);
}

int sinY(float angle) {
  /*----------------------------------------------------//
  // Outputs the y value needed to make a point on a    //
  //  triangle                                          //
  //----------------------------------------------------//
  // angle: the angle in degrees off center of the point//
  //  to be drawn                                       //
  //----------------------------------------------------//
  // return: the y position of the triangle point       //
  //----------------------------------------------------*/

  return (sin(deg2rad(angle)) * 120) + 120;
}

int cosX(float angle) {
  /*----------------------------------------------------//
  // Outputs the x value needed to make a point on a    //
  //  triangle                                          //
  //----------------------------------------------------//
  // angle: the angle in degrees off center of the point//
  //  to be drawn                                       //
  //----------------------------------------------------//
  // return: the x position of the triangle point       //
  //----------------------------------------------------*/

  return (cos(deg2rad(angle)) * 120) + 160;
}

void loop() {
  for (int i = 0; i <= 120; i = i + 10) {
    //
    // Draws two triangles, one in green which is immediately erased by the one in black
    lcd.drawTriangle(cosX(i), sinY(i), cosX(i + 120), sinY(i + 120), cosX(i + 240), sinY(i + 240), TFT_GREEN);
    lcd.drawTriangle(cosX(i), sinY(i), cosX(i + 120), sinY(i + 120), cosX(i + 240), sinY(i + 240), TFT_BLACK);
  }
}
