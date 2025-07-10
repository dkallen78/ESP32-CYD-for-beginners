# Hello Class

When last we saw our plucky program, we had run into a conundrum. The plan was to generalize our text box centering and drawing function, but we ran into a situation where we either had to do too much in our function, or pass a burdensome number of arguments to it in order for our program to behave as expected. Thankfully there is a solution. We're going to make a class for our text box.

## Intro to classes

A class is kind of like creating our own type of variable with some extra features bundled in. A more precise way of saying that, is that a class is a way for us to make our own data structures. Here's the basic form a class has to take:

```c++
class ClassName {
  public:
    int someVariable;
};
```

Then, when you want to make use of your fancy new data structure, you create an instance of it, just like you would when declaring a variable.

```c++
ClassName myObject;
```

And that variable on the inside? That's technically called an attribute and you can access it like so:

```c++
myObject.someVariable
```

So far so good? See that `public` bit? That means that everything below `public` is available for use outside of the class (more on that another time). The important thing is that you can not only declare as many variables/attributes as you'd like, you can also create functions/methods. Let's make a class for our text box.

## Making the text box class

First, our new class needs a name. I'm going with `TextBox`, but you do you.

> [!NOTE]
> Class names in C++ are traditionally written with the initial letter capitalized.

```c++
class TextBox {
  public:
    ...
};
```

Sweet. Now we need to build in all the variables we want it to have. Part of the reason we're doing this is because our class will be able to carry all of our text box data in a much neater package than otherwise possible (but there will be some other benefits as well). The two most important values are our `String` of text and the `charWidth` because all of our other values are derived from those two.

```c++
class TextBox {
  public:
    String text;
    int charWidth;
};
```

This is enough to get us started and we can start to see some benefit if we drop it into our program.

To use it, we'll need to create an instance of it and define its attributes.

```c++
TextBox textBox;
textBox.text = text;
textBox.charWidth = 12;
```

Now, instead of passing the `String` variable with our text to the `drawTextBox()` function, we can pass the <var>`textBox`</var> object we just created.

```c++
void drawTextBox(int yPos, TextBox textBox) {
  int textWidth = textBox.text.length() * textBox.charWidth;
  int textHeight = lcd.fontHeight();
  ...

}
```

We *could* go ahead and fill our `TextBox` class up with attributes so it can hold all the values we need, but that will clutter up our `loop()` function, and there's a better way to do this: methods.

Because all of our other values are directly derived from <var>`text`</var> and <var>`charWidth`</var>, those are the only ones we have to explicity define. We can use a method to calculate the other ones when we need them.

Methods are defined in pretty much the same way a function is, only we do it inside our class.

```c++
class TextBox {
  public:
    void boxMethod() {
      ...
    }
};
```

Then you can use the method just like we've been using other methods.

```c++
textBox.boxMethod();
```

Let's look back at the program we made in the last tutorial, [greetings-planet.ino](../05-hello-functions/greetings-planet.ino). In particular, look at the last three lines of the `drawTextBox()` function.

```c++
lcd.fillRect(boxXoffset, yPos, boxWidth, boxHeight, TFT_YELLOW);
lcd.setCursor(textXoffset, yPos + 4);
lcd.println(text);
```

Between these three commands — the heart of the function — there are seven variables. Let's take a look at them and figure out which ones we'll have to make methods for in our class.

* <var>`boxXoffset`</var> – derived from <var>`boxWidth`</var> which comes from <var>`textWidth`</var> which comes from <var>`text.length()`</var> and <var>`charWidth`</var>
* <var>`yPos`</var> – passed to the function from the for loop
* <var>`boxWidth`</var> – comes from <var>`textWidth`</var> which comes from <var>`text.length()`</var> and <var>`charWidth`</var>
* <var>`boxHeight`</var> – derived from <var>`textHeight`</var> which comes from <var>`lcd.fontHeight()`</var>
* <var>`TFT_YELLOW`</var> – constant defined in the BB_SPI_LCD library; in the global scope
* <var>`textXoffset`</var> – comes from <var>`textWidth`</var> which comes from <var>`text.length()`</var> and <var>`charWidth`</var>
* <var>`text`</var> – passed into the function as an argument

