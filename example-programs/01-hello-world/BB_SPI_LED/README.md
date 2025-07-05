# BB_SPI_LCD

BB_SPI_LCD is a library for manipulating LCD displays on various ESP32 and Arduino devices. 

## Screen Stuff

### `begin(int iStandardType)`

This method sets up the display for use by the other methods in the library. 

<var>`iStandardType`</var> is an integer that corresponds to one of dozens of predefined displays. The library has a number of [predefined constants](https://github.com/bitbank2/bb_spi_lcd/tree/master?tab=readme-ov-file#named-displays) you can use in place of these integers to make your code more legible.

If your display isn't in this list, you can probably still use the library, but doing so takes more knowledge than I currently have.

---
### `setBrightness(uint8_t u8Brightness)`

Sets the brightness of the display.

<var>`u8Brightness`</var> should be a non-negative integer value between 0 and 255.

---
### `setRotation(int iAngle)`

Sets the orientation of the screen. 

<var>`iAngle`</var> should be an integer between 0 and 3. You can also use one of four predefined constants for code readablity.

* <var>LCD_ORIENTATION_0</var> or <var>0</var> – portrait with USB at the bottom
* <var>LCD_ORIENTATION_90</var> or <var>1</var> – landscape with USB at the right
* <var>LCD_ORIENTATION_180</var> or <var>2</var> – portrait with USB at the top
* <var>LCD_ORIENTATION_270</var> or <var>3</var> – landscape with USB at the left (default for CYD)

---
### `getRotation()`

Gets the current screen rotation in the form of an integer between 0 and 3.

---
### `fillScreen(int iColor, int iFlags = DRAW_TO_LCD | DRAW_TO_RAM)`

Fills the screen with a single 16-bit color.

<var>`iColor`</var> an integer between 0 and 65,535 representing a color in the [RGB565 colorspace](https://rgbcolorpicker.com/565). Frequently given in the form of a four-digit hexadecimal number.

<var>`iFlags`</var> I don't know the functional or useful difference between the two possible values for this argument ... yet.

---
## Word Stuff

### `setWordwrap(int bWrap)`

Controls word wrapping behavior for text.

<var>`bWrap`</var> is essentially a boolean integer.

* <var>`0`</var> – no wrap
* any other integer – wrap, cuts off words

---
### `setTextColor(int iFG, int iBG = -2)`

Sets the foreground and background color of the displayed text.

<var>`iFG`</var> an integer between 0 and 65,535 representing the 16-bit foreground color.

<var>`iBG`</var> an integer between 0 and 65,535 representing the 16-bit background color. Defaults to black if omitted.

---
### `setCursor(int x, int y)`

Sets where to place the cursor for displaying text.

<var>`x`</var> the x position at which to place the cursor.
<var>`y`</var> the y position at which to place the cursor.

---
### `setFont(int iFont)`

Sets the font with which to display text output.

<var>`iFont`</var> expected to be an integer between 0 and 4 or one of five enumerated constants.

<details>
<summary>Font contants</summary>
  <ul>
    <li>FONT_6x8</li>
    <li>FONT_8x8</li>
    <li>FONT_12x16</li>
    <li>FONT_16x16</li>
    <li>Font_16x32</li>
  <ul>
</details>

---
### `getCursorX()`

Gets the current x position of the cursor in the form of an integer.

---
### `getCursorY()`

Gets the current y position of the cursor in the form of an integer.

---
### `fontHeight()`

Gets the height in pixels of the current font.