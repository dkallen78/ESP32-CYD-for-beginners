# Hello Fonts (and Typefaces)

So in case you missed the conceit of these tutorials on the README for this repo, I'm learning this as I go and bringing you along for the ride. I miss some things and I'm constantly learning and poking and prodding to see how things work. All that to say, I found a simpler way of figuring out how many pixels a string of text takes up on screen, but first, let's get into fonts and typefaces.

<details>
  <summary>Fonts vs typefaces sidequest!</summary>

  ---

  *Technically*, typefaces are the sets of glyphs with unique designs like Arial or Times New Roman. Fonts are variations on those designs, like size or italics. So, all the fonts we've been using so far in this tutorial are part of the same typeface. Pretty simple, really.

  ---

</details>

Let's take a big step back to the [program we made in the second tutorial](../02-better-hello-world/hello-world-2.ino). If you don't want to click the link, it's the one where we centered "Hello World" and put it in a box. Recall that for the `setTextColor()` method we had to specify a color for the text and an optional color for the background that would default to black. This lack of transparency works fine for relatively simple UIs and layouts, but has some obvious drawbacks.

<img src="../assets/img/09/cyd-hello-world-split-bg.jpg" alt="CYD Hello World program with split color background">

This drawback is only limited to the default fonts included with this library, but there are alternatives, you just have to find them, download them, and put them in the right place so your program can find them.

To start, download a font (here, [take this one](Calligraffitti_Regular_16.h)), and put it in your `libraries` directory with your other downloaded libraries. On Windows, it's probably in C:/Users/[your_name]/Documents/Arduino. 