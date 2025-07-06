Okay, you have a "Hello World" program up and running on your CYD, but it's kind of ugly, so let's see what else the BB_SPI_LCD library can offer us to make our program a bit more pretty.

The first thing we can do is use the `fillScreen()` method to fill our display with a more pleasing color instead of the actinic bars of our current program. 

```c++
lcd.fillScreen(TFT_BLUE);
```

Put this line right after the `begin()` method. It will mellow out the harsh of the display.

That looks much better but you have a new problem: The background color of your text defaults to black and it totally clashes with the blue background fill. 

<img src="../assets/img/cyd-blue-hello-world-bb.jpg" alt="CYD Hello World program with blue background">

To fix this you could set pass <var>TFT_BLACK</var> to `fillScreen()` but what if you *really* wanted that blue background. Thankfully, BitBank already has a solution. Remember the `setTextColor()` method? You can pass a second argument to it to set the background color of the text. If you omit the second argument it will default to a black background but you can set it to whatever you want. Let's set our text background color to blue like our display fill and set our text to yellow so it pops a bit.

```c++
lcd.setTextColor(TFT_YELLOW, TFT_BLUE);
```

<img src="../assets/img/cyd-blue-yellow-hello-world-bb.jpg" alt="CYD Hello World program with yellow text and blue background">

Things are starting to look better, but we can do more. For one thing, the font is really small. This is an easy fix with the `setFont()` method. `setFont()` can take one of five arguments that will determine the font. The library has five constants built in to make it clearer which font you're using. You could just use the numbers 0–4, but using the constants makes your code more readable.

<img src="../assets/img/cyd-font-sizes-bb.jpg" alt="CYD displaying the different font sizes in the BB_SPI_LCD library">

That 12 by 16 font looks sharp, let's go with that one.

```c++
lcd.setFont(FONT_12x16);
```

This is fine, but it would look better if the text were centered. The BB_SPI_LCD library doesn't have a built-in method to center text, so we'll have to do it ourselves. There are four things we need to do this: 
1. The `setCursor()` method which lets you determine from which pixel on the display your text will be written.
2. The width in pixels of your display. Since you're using a CYD you know that's either 320 or 240.
3. The number of characters in your string. There are 11 characters in the string "Hello World".
4. The width in pixels of your font. 

We know our font is 12 pixels wide. The fonts included in this library are monospaced, meaning each glyph takes up an equal amount of screen real estate. Our string is 11 characters long, so that means our string takes up 132 pixels. If we moved our cursor to pixel 160 on the x axis in the middle of the screen our text would begin from there, so the trick is to offset the pixel to the left by half the length of our string, 66 pixels. That means we need to move our cursor to pixel 160 - 66, or 94.

```c++
lcd.setCursor(94, 0);
```

<img src="../assets/img/cyd-hello-world-centered-bb.jpg" alt="CYD Hello World program with the text horizontally centered">

If you're feeling adventurous you could set all of that up programatically so that the computer does the math for you, but there are some parts of the code that would have to be restructured to pull it off.

If we want to center the text vertically, we have to do similar math. Our font is 16 pixels high and only takes up one line. The middle of the y axis on the CYD is 120 pixels. Offset that position by half of our pixel height to get our vertical center point. 120 - 8 = 112

```c++
lcd.setCursor(94, 112);
```

<img src="../assets/img/cyd-hello-world-hv-centered-bb.jpg" alt="CYD Hello World program with the text vertically and horizontally centered">

This is starting to look good! Let's go one step further to make our "Hello World" pop!

Let me introduce you to `fillRect()`. This method takes five arguments: the x and y position of the top-left corner, the pixel width and height of the rectangle, and its color. Let's make a box centered behind our text and give it a padding of 4 pixels. From the math we did earlier we know our text takes up a rectangle 132 pixels wide by 16 pixels high. If we want to add 4 pixels to each side, that would make our rectangle 8 pixels wider and taller or 140 by 24 pixels. We also have to offset the top-left corner of our rectangle by 4 pixels in each direction giving us initial x and y values of 90 and 108. If we make this box yellow, that will give us this command:

```c++
lcd.fillRect(90, 108, 140, 24, TFT_YELLOW);
```

Since that will be the same color as our text, we'll also have to swap out our foreground and background colors in the `setTextColor()` method if we want the text to look nice in its box.

<img src="../assets/img/cyd-hello-world-center-box-bb.jpg" alt="CYD Hello World program with centered text and box">

Keep in mind that the order in which you do things matters. If you put the text on the screen first, there's a chance that any box you draw afterwards will cover your text.