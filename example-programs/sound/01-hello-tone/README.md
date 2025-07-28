# Hello Tone

It's about time to make some noise. Sound probably isn't something you need for most projects, but it's a nice tool to have at your disposal. 

Before we get too far, to make noise with your CYD, you're going to need a speaker. I got a [pack of four](https://www.amazon.com/dp/B0177ABRQ6) from Amazon along with a [bundle of 1.25 mm 2-pin JST connectors](https://www.amazon.com/dp/B078NPRW46), then I soldered a pair of them together along with some heat shrink. Once everything's assembled, plug it into the 2-pin speaker connector on the back of your board.

<img src="../assets/img/01/cyd-speaker-connector.jpg" alt="Back of the CYD board with a red arrow pointing to the speaker connector">

If you've got all that done, let's start with the simplest noise we can make.

```C++
#define SOUND_PIN 26

void setup() {
  tone(SOUND_PIN, 440);
}

void loop() {

}
```

https://github.com/user-attachments/assets/fabc6c34-21de-4f0b-a7dc-f52a5e6f2e26

When you've got that compiled and running, turn it off, because it's probably annoying. Once you're not being yelled at by your silicon, let's talk about what's happening.

```C++
#define SOUND_PIN 26
```

First off, we're defining which pin is going to receive our sound output. You don't have to put it in a constant like this, but it's a good habit that will make your code more readable in the long run.

```C++
tone(SOUND_PIN, 440);
```

This is the function (which is part of Arduino's bag of goodies) that makes the sound. The sound it makes is a square wave with a duty cycle of 50%. In other words a square wave whose peaks and troughs are of equal duration/width (50% high, 50% low). You can only play one `tone()` at a time, even if you're sending them to multiple pins. The lowest frequency value you can input is 32 Hz and the largest is 8 MHz (the average range of hearing is about 20 Hz to 20 kHz, so there's not many good reasons to crank it up to 8 MHz).

We can also add another argument to the `tone()` function to control its duration in milliseconds.

```C++
tone(SOUND_PIN, 440, 1000);
```

You can also mix in delays to get an alarm clock vibe.

```C++
tone(SOUND_PIN, 440, 250);
delay(500);
```

https://github.com/user-attachments/assets/a6145ffb-e8f2-40ab-9010-16da18426246


You can get a slightly different vibe by changing the frequency,

```C++
tone(SOUND_PIN, 440, 250);
delay(500);
tone(SOUND_PIN, 880, 250);
delay(500);
```

As you're playing with all of this, you'll come to realize that `tone()` is a bit different. Part of what makes it harder to understand is that it's non-blocking, so the program continues to run while the tone is playing, that's why in the above code the delay is set to 500 ms, but the perceived delay is 250 ms. In other words, the tone is playing its alotted 250 ms while the delay is counting down. *But*, `tone()` doesn't always behave how you expect it to. Take a look at the following code I paraphrased from the [Arduino Language Reference](https://docs.arduino.cc/language-reference/en/functions/advanced-io/tone/):

```C++
tone(SOUND_PIN, 440, 1000);
delay(1000);
```

This works fine on the CYD, albeit with a little tick as it loops around after the delay, but if you lower the duration and delay to 500 ms or lower, you'll only get sound briefly before it stops. Raise it to 501 ms and everything works as expected, but any lower and it won't. I don't know why but it's good info to have! Why do I know this? Because I wanted to alternate between 440 Hz and 880 Hz without a gap and that seemed like the best way to do it at first glance, but there is a better way.

Remember, you can only have one `tone()` running at a time, but if you call the `tone()` function again on the same pin with a different frequency, it will begin playing the new frequency (if you have another pin with a speaker and you try to call `tone()` while it's already playing a tone on another pin, nothing will happen). So, if you want instantaneous change between two frequencies, omit the duration.

```C++
tone(SOUND_PIN, 440);
delay(250);
tone(SOUND_PIN, 880);
delay(250);
```

This sounds less like an alarm clock and more like an urgent alarm. Tweak the values a bit and you can get something very similar to the old North American standard for a [ringing tone](https://en.wikipedia.org/wiki/Ringing_tone) (not the kind you put on your mobile phones).

```C++
tone(SOUND_PIN, 440);
delay(50);
tone(SOUND_PIN, 480);
delay(50);
```

Arpeggios feel less urgent to me and more like something from a video game.

```C++
tone(SOUND_PIN, 262);
delay(50);
tone(SOUND_PIN, 349);
delay(50);
tone(SOUND_PIN, 392);
delay(50);
```

Okay, this has been fun, but we've got a bit of problem on our hands. If we use `delay()` to control the duration of our notes, there's not much else we can do, because `delay()` pretty much blocks any logic from running. In other words, all we can do is make noise. If we wanted to push a button, crunch some numbers, or use the processor in any way, `delay()` would prevent us from doing so. Depending on what we want to do, we can approach this in a few different ways, but all of them rely on using the `millis()` function to keep track of time.

`millis()` is a function supplied by the Arduino IDE and it returns a `long` integer value representing the number of milliseconds that have elapsed since the board was turned on. In isolation this isn't a very useful metric to have, but by comparing two `millis()` calls, you can get a measure of elapsed time.

```C++
long time_stamp = millis();
void loop() {
  if (millis() - time_stamp > duration) {
    do_something();
  }
}
```

Let's put some real code in here and see what happens when we run it!

```C++
long stamp = millis();
long duration = 500;

void loop() {
  tone(SOUND_PIN, 440);
  if (millis() - stamp > duration) {
    noTone(SOUND_PIN);
  }
}
```

What you get is a whole lot of nothing. That's because we're spamming the `tone()` function, so we need a way to only call it only if it's not playing. That's where flags/status/state variables come in handy. Flag variables are booleans that you use to keep track of the state of a portion of your code. In this case, we need a flag to determine if there is a tone playing. Most sources agree that flags should start with `is` or `has` or a similar prefix and be positive. In this case that means that <var>`isPlaying`</var> is preferred over <var>`isNotPlaying`</var>. Let's go ahead and put that bool outside of our loop and set its initial value to <var>`false`</var>.

```C++
bool isPlaying = false;
```

Next, we have to wrap our `tone()` up in an if statement and use our new flag as our condition. Don't forget to change the value of our flag once we call `tone()`.

```C++
if (!isPlaying) {
  tone(SOUND_PIN, 440);
  isPlaying = true;
}
```

Don't forget to change the value of the flag once we call `noTone()`, and most importantly, we need to reset our <var>`stamp`</var> value with `millis()` otherwise our second if block will be called for every loop and we'll get some awful sound out of our speaker (ask me how I know).

```C++
if (millis() - stamp > duration) {
  noTone(SOUND_PIN);
  isPlaying = false;
  stamp = millis();
}
```

That will give us a tone with a blip in it every half second. This should give you the basic framework to play with `tone()` without throwing a wrench into the digital gears of your program. 

As a final challenge for working with `tone()`, see if you can make a program that oscillates between 100 and 1,000 Hz, doesn't use `delay()`, *and* starts and stops with the touch of a button (feel free to use the `Button` [object we put together](../../BB_SPI_LED/98-utilities/button-struct.ino) or just make the whole screen your button =P). 

Just be aware, a for loop moves too fast for your changing tone to play properly and it isn't easy to interrupt the loop external input. Also, if your tone is playing for fewer than 5 ms before you change it, you'll get some silence on the low end of your oscillation. 

[Here's what I came up with](hello-tone-oscillator-01.ino) along with some quality-of-life additions to make button input a little nicer.