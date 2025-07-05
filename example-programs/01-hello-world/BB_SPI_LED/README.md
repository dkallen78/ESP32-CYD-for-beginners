# BB_SPI_LCD

BB_SPI_LCD is a library for manipulating LCD displays on various ESP32 and Arduino devices. 

## BB_SPI_LCD Methods

### `begin(int iStandardType)`

This method sets up the display for use by the other methods in the library. 

<var>`iStandardType`</var> is an integer that corresponds to one of dozens of predefined displays. The library has a number of [predefined constants](https://github.com/bitbank2/bb_spi_lcd/tree/master?tab=readme-ov-file#named-displays) you can use in place of these integers to make your code more legible.

If your display isn't in this list, you can probably still use the library, but doing so takes more knowledge than I currently have.

### `setBrightness(uint8_t u8Brightness)`

Sets the brightness of the display.

<var>u8Brightness</var> should be a non-negative integer value between 0 and 255.

### `setRotation(int iAngle)`

Sets the orientation of the screen. 

<var>iAngle</var> should be an integer between 0 and 3. You can also use one of four predefined constants for code readablity.

* <var>LCD_ORIENTATION_0</var> or <var>0</var> – portrait with USB at the bottom
* <var>LCD_ORIENTATION_90</var> or <var>1</var> – landscape with USB at the right
* <var>LCD_ORIENTATION_180</var> or <var>2</var> – portrait with USB at the top
* <var>LCD_ORIENTATION_270</var> or <var>3</var> – landscape with USB at the left (default for CYD)

### `getRotation()`

Gets the current screen rotation in the form of an integer between 0 and 3.

### `setWordwrap(int bWrap)`

Controls word wrapping behavior for text.

<var>bWrap</var>

* <var>0</var> – no wrap
* any other integer – wrap, cuts off words

### `fillScreen(int iColor, int iFlags = DRAW_TO_LCD | DRAW_TO_RAM)`

Fills the screen with a single 16-bit color.

<var>iColor</var> 