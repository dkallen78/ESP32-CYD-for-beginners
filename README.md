# ESP32 CYD for beginners
A record of my journey with the CYD that I'm making to help others who don't know a lot about hardware

Given the community that's growing up around the ESP32 CYD, I thought it was good idea to make a guide for absolute beginners who have very limited programming knowledge but still want to dive in and make something. Many tutorials and guides take the form of code examples that you're expected to copy and paste which works great for people with experience programming in C++, but not so much for every one else. 

## What is the ESP32 Cheap Yellow Display (CYD)?

The CYD is an ESP32 microcontroller with a built in 2.8-inch, 320 × 240 touch display (about 43 × 57 mm or 1.7 × 2.25 in). You can pick one up (or a close imitator) for anywhere from $10 to $25 depending on how you get it with AliExpress being the cheapest and Amazon being the most expensive.

Besides incorporating a display directly with the microcontroller, the CYD also has Wi-Fi, Bluetooth, USB input, an SD card slot, and a bunch of GPIO pins you can play with. Coupled with its low price, that makes the CYD a great value, especially for people who just want to make stuff.

## What software do you need?

### CH340 Driver

First, you need to make sure you have a driver for the CH340 chip the CYD uses to allow communication between it and your computer via a USB connection. If you're using a Windows machine, an easy way to see if you have this driver is to plug in your CYD and see if it shows up in your Device Manager. If you have the driver installed it should appear under `Ports (COM & LPT)` as `USB-SERIAL CH340 (COM##)`. 

<img src="device-manager-ch340.jpg" alt="Windows Device Manager showing the connected CYD">

If you don't have the driver installed, you'll have to get it. The easiest way to grab it is from [SparkFun's website](https://learn.sparkfun.com/tutorials/how-to-install-ch340-drivers/all) which also has the drivers Mac and Linux.