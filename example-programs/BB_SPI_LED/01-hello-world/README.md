# Hello World

Every great programming journey starts with a "hello world" program, and why should the CYD be any different? 

To get started, take a look at the [hello-world.ino](hello-world.ino) file. If you've worked with the Arduino IDE or microcontrollers before, this will probably look familiar. If not, don't worry, I'll explain all the important parts. To keep things simple for now, just copy and paste everything from `#include` down to the last `}` into the Arduino IDE and upload it into your CYD.

<img src="../assets/img/01/cyd-hello-world-bb_spi_led-1.jpg" alt="CYD displaying Hello World">

It's not pretty, but it works!

Let's take a closer look at the code to see what's going on. 

```c++
#include <bb_spi_lcd.h>
```

The first line of our code tells the compiler to "include" the bb_spi_lcd library (and all of its commands) in the program. 

<details>
  <summary>Why is it called "bb_spi_lcd"?</summary>

  "bb" is short for <a href="https://bitbanksoftware.blogspot.com/">BitBank Software</a>, run by Larry Bank and he's the guy that made the library which is <a href="https://github.com/bitbank2/bb_spi_lcd/tree/master">hosted here on GitHub</a>.<br>

  SPI is a hardware communication protocol that allows CPUs to communicate with peripheral devices. It stands for **s**erial **p**eripheral **i**interface.

  LCD refers to the type of screen we're controlling with this library.
</details>

```c++
BB_SPI_LCD lcd;
```

This line creates a new instance of the class `BB_SPI_LCD` and names it <var>`lcd`</var>. You have to use the exact name `BB_SPI_LCD` because it's defined in the `bb_spi_lcd.h` library, but you can name this instance of it whatever you want. If you do change the name, make sure you change it on lines 6, 7, and 8 as well.

```c++
void setup() {
  ...
}
```

Next up is the `setup()` function. This is one of two required functions when compiling your code with the Arduino IDE. The `setup()` function is run one time when your CYD starts up.

```c++
lcd.begin(DISPLAY_CYD); 
```

<var>lcd</var> is the name of the `BB_SPI_LCD` object type we created earier. `begin()` is a method that initializes the display and gets it ready to push some pixels. Your program will compile just fine without this line, but you won't be able to display anything on the screen without it. 

The bb_spi_lcd library works with a lot of devices. In order to work with the CYD it needs to know about the screen size and the internal pin layout and other sundry details. To make life easier for developers, BitBank has stored the display details for dozens of devices in the library, so the users can just pass a constant name (in this case `DISPLAY_CYD`) to the method instead of the 10 arguments you would otherwise need to get the display up and running.

```c++
lcd.setTextColor(TFT_WHITE);
```

The purpose of this line should be fairly straightforward. The method `setTextColor()` sets the color of the text to be displayed. *Technically*, the method expects a hexadecimal value representing a 16-bit color, but again, BitBank has made your life a bit easier by creating [10 predefined colors for you to use](https://github.com/bitbank2/bb_spi_lcd/blob/b243e7421397ba31c6355bad0fd90131ab29508a/src/bb_spi_lcd.h#L136). If you'd rather use a custom color and use the hex code, [this site](https://rgbcolorpicker.com/565) will be a big help to you.

```c++
lcd.println("Hello World");
```

This line puts the text on the screen. Nothing fancy here. If you want `println()` to display text, it needs to be encapsulated in double quotation marks. You can enclose a single character in single quotes and it will render fine, but any more than one character will output a big number.

<details>
  <summary>Why the big number for strings in single quotes?</summary>
  In C++, single quotes are only for defining a single character, but if you put two or more characters into single quotes, they will be treated as digits of a base-256 number with all 256 ASCII symbols as possible glyphs.<br><br>

  So, if your line looked like this

  ```c++
  lcd.println('42');
  ```

  the compiler would take the ASCII value of the first digit (50) and add it to the ASCII value of the second digit (52) multiplied by 256.

  ```
  256¹ * 52 + 256⁰ * 50 = 13,362
  ```
</details>

You can also pass a number or variable as an argument. If you want to display a double number, keep in mind that `println()` can only display two decimal digits, anything more than that will be cut off. Also, although `println()` can *technically* accept a bool as an argument, it will only display a 1 or 0.

```c++
void loop() {
  // put your main code here, to run repeatedly:

}
```

The `loop()` function is another one of those functions required by the Arduino IDE. Anything in the `loop()` function will run on reapeat as long as the CYD is powered.

Now you have a working program, but it's kind of janky. [Next up](../02-better-hello-world/), we're going to dejank it.