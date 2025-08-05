# Screen Switching

This is the stage of development where I've had things go screwy in the past, so it's best to plan it out now so I don't make a mistake later. 

Here's what I want to do. I want to have multiple options on the home screen, then when I click on one of them, it takes me to another screen. From that other screen I want to be able to back out to the home screen again and maybe choose another one of the options. Sounds simple, here's where I screwed it up in the past. 

I made a program (you can [see its current state here](https://github.com/dkallen78/math-trainer)) that also had a home screen and there were multiple options to choose from which would take me to another screen. From there I could choose to return or go to yet another screen. I set this up so each screen had a function I could call that would build it, and inside that function was a function that would return tme to the home screen, which was itself built by a function. I would use these function calls to navigate my UX and do things. This program would inevitably crash within five minutes. Why? Memory.

* When my program started it would run the homescreen function.
  * Within that function I would go to another screen
    * If I wanted to return to the home screen I would call the home screen function
      * At this point I'm back at the home screen but I'm actually *still inside the original function call*. It never completed and therefore all of its memory was still being held onto.
        * With this architecture there was no way for me to exit my bottomless memory pit
          * Every screen change just brought me closer to a program crash

If I did something like this on the CYD I would run out of memory fast. What I did instead was nest everything inside loops, then, when I wanted to go back up the UX tree, I would end the loop, killing that function and all its data. I'm going to do something similar with this program.

```C++
loop() {
  build_screen();
  input_loop() {

  }
  switch(current) {
    case 0:
      tracker();
    case 1:
      exercises();
    ...
    ...
  }
}

tracker() {
  build_screen();
  input_loop() {

  }
}

exercises() {
  build_screen();
  input_loop() {

  }
}
...
...
```

So, the `loop()` function will be my home screen. Inside the input loop, selecting one of the modes will cause the input loop to break, and a switch statement will trigger the next screen. When the user is done with that screen/function, the function will terminate back to `loop()` which will loop back to the screen-building block. That's the plan anyway, let's see if it works!

[Here's what I have so far](./gtg-home-screen-01.ino). The first thing I need to do is make a way to break the loop. I'm going to make a new bool to gatekeep my while loop. 

```C++
bool inputLoop = true;

while (inputLoop) {
  ...
}
```

Next I need to check if there's a touch on the mode button. I think this will be simple (let's see).

```C++
else if (mode.click(&ti) && !press) {
  inputLoop = false;
}
```

I also need to put in the switch. For now I'm just going to make a test function that all the cases go to.

```C++
switch(currentMode) {
  case 0:
    exercises();
    break;
  case 1:
    exercises();
    break;
  case 2:
    exercises();
    break;
  case 3:
    exercises();
    break;
}
```

And in my `exercises()` function, I'm going to make a button that breaks a loop when it's pressed. 

Aaaaaand it doesn't work. [Here's what I've got](./gtg-navigation-test-01.ino). So the home screen loads fine. then the test screen loads fine. But when I go back to the home screen, only the title element loads and not the input elements. And when I click the area where the input for the test screen would be, it goes back to the test screen and is locked there.

I think part of the problem is when I get back to `loop()` I'm redeclaring the same variables. I don't know what the best practice is in this case, but my first thought is to make a sentinal variable that tracks whether or not I've declared those variables and put their declaration behind an if block. Let's see if it works!

Nope, putting them in an if block takes them out of scope. And, after a bit of reading, each cycle of the loop destroys what was there before, so I'm not sure what the issue is here. I'm going to start by putting a counter into `loop()` and see if things are moving.

Things are looping, but for whatever reason, my blocks aren't drawing. I can press back and forth but around the 9th loop, even my test screen stops showing things. I can see the Block's `draw()` method is running by putting a `print()` in there.

Okay, I've got it. When I make my Block objects, I call the `createVirtual()` method which uses `malloc()` to set aside a chunk of memory for the sprite. Even though the variable is destroyed and recreated in each cycle of the loop, that chunk of memory remains allocated. As I continue to loop, I chew up all of my available memory until I can't make any more sprites. The solution is the `freeVirtual()` method which unbinds that memory so it can be used again.

[Here's the working code](./gtg-navigation-test-02.ino), and here are the relevant bits.

A method in my Block struct to clear the memory

```C++
void clearVirt() {
  sprite.freeVirtual();
}
```

and calls to the new method at the end of the loop, before going to a new screen

```C++
title.clearVirt();
mode.clearVirt();
modeLeft.clearVirt();
modeRight.clearVirt();
```

I'm glad this is working, but I think I might have to abandon my sprite-based Block struct if memory becomes sticky down the line. But that's a decision for another time. I have proven the validity of my design plan, I'm going to tackle I/O next which means I have to find an SD card ...