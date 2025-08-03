# User Interface and User eXperience

UI and UX are really big umbrellas for a lot of small details that coalesce into the vibe of your program. This is the kind of thing I always have in the back of my mind, but until I pull it out into the light, I usually don't realize how amorphous my ideas are. But, now that I've demonstrated the feasability of my idea by making a working prototype, it's a good time to put a little polish on my UI/UX. Plus, making it nice to look at will keep me motivated to continue adding features.

Before I tinker with the UI anymore, I want to figure out the scope of my program. I know that at its core, it's a rep counter, but that leaves a lot of things left unsaid. For instance, what am I counting reps of? *I'm* planning on counting pull-ups and push-ups, but there's a lot of joy to be had in making something for other people, even if noone ever uses it. What I'm getting at is, what if people want to use the program, but they don't want to track pull-ups? Should I expect any other users of this program to edit my source code or save files to make it work for them? Lots of developers take that approach but I'd rather make something more user-friendly. As such, I'm going to need a way for users to add their own exercises which means text input.

**Feature List**

* Add exercises
  * Text input/on-screen keyboard

Since the exercises won't be hard-coded into the source code and they will be added after compile, that means they'll be saved into an external file on an SD card (CYD doesn't have EEPROM/onboard memory). But what happens if there is no file present? What should the start-up behavior of my program be? Will it start up to a home screen, a root from which other functionalities branch out? Or should it start to the rep-counting UI I've already built? I've decided that I want to have text input which means an on-screen keyboard which means that the rep-counting screen won't be the only one which means I need a way to exit the rep-counting screen. 

**Rep-counter UI Changes**

* Exit screen

But if I exit the rep-counting screen/page/interface, where does that take me? I think I need a home screen. Having decided that, I can get a better idea of my program's start-up behavior. 

**Feature List**

* Add exercises (this should probably be a screen)
  * Text input/on-screen keyboard
* Home screen

> [!NOTE]
> Having settled on two new screens at this point, I'm thinking about how to build them in the back of my mind. I'm not prepared to start implementing them just yet, but I'm imagining how they should behave and mentally trying out different ideas.

People using this app may not want the same alarm interval that I do, so there should be a way to change that.

**Feature List**

* Add exercise screen
  * Text input/on-screen keyboard
* Home screen
* Alarm screen

Since this program is supposed to connect to the user's Wi-Fi network, they need to have a way to input their network and password (looks like I'll have more than one use for my keyboard).

**Feature List**

* Add exercise screen
  * Text input/on-screen keyboard
* Home screen
* Alarm screen
* Wi-Fi screen