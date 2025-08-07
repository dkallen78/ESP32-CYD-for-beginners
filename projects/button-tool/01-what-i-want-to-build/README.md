# What I Want to Build

I anticipate having to make an on-screen keyboard for my CYD, so I'm going to make a program to determine about how big my buttons should be so I can get a better idea of how I can configure my virtual keyboard. Here's the idea:

I'm going to put a pixel near the center of the screen, then I'm going to register touches and record the max distance in each direction those touches register and what the average distance is. Plus I'm going to draw boxes representing those two values to roughly represent how big those buttons will be.

Sounds simple! First I'm going to get a pixel on the middle of the screen.

```C++
lcd.drawPixel(160, 120, TFT_WHITE);
```

<img src="./img/button-tool-first-pixel.jpg" alt="CYD button tool program with a single pixel displayed">

Okay, that's a little too small. Maybe a small box would be better ...

```C++
lcd.fillRect(159, 119, 2, 2, TFT_WHITE);
```

<img src="./img/button-tool-bigger-pixel.jpg" alt="CYD button tool program with a 2 by 2 box">

Awesome, now let's display some touch data. I'm going to make two variables for my x and y data then use `print()` to put them on-screen, I think towards the top is best (for now).

```C++
if (lcd.rtReadTouch(&ti)) {
  x = ti.x[0];
  y = ti.y[0];
  
  lcd.setCursor(0, 0);
  lcd.printf("x: %d", x);
  
  lcd.setCursor(160, 0);
  lcd.printf("y: %d", y);
}
```

<img src="./img/button-tool-with-xy.jpg" alt="CYD button tool program displaying x and y touch coordinates">

It's coming together! Next I'm going to do the max offset values and I think I'm going to do it one line down so I'm going to put my cursor at 10, 0 to start but I'm going to have four values here x left, x right, y up, and y down so I'm going to crunch some numbers to make sure my output looks good =P 

I don't think my max offset from the center will be more than 100 pixels so I'll give myself 6 characters per offset ("-x: ##") and make sure to put my next value right of that. Since I'm using an 8 by 8 font, that means I need to move the cursor more than 40 for each output. I'll probably need some variables to hold those values and logic to determine them as well. Here's a bit of the code:

```C++
if (y < 120) {
  yu = ((120 - y) > yu) ? (120 - y) : yu;
} else {
  yd = ((y - 120) > yd) ? (y - 120) : yd;
}

lcd.setCursor(160, 10);
lcd.printf("-y: %d", yu);

lcd.setCursor(216, 10);
lcd.printf("+y: %d", yd);
```

<img src="./img/button-tool-with-offsets.jpg" alt="CYD button tool program displaying the max x and y offsets">