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

This works fine on the CYD, albeit with a little tick as it loops around after the delay. But if you lower the duration and delay to 500 ms or lower, you'll only get sound briefly before it stops. Raise it to 501 ms and everything works as expected, but any lower and it won't. I don't know why but it's good info to have! Why do I know this? Because I wanted to alternate between 440 Hz and 880 Hz without a gap and that seemed like the best way to do it at first glance, but there is a better way.

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