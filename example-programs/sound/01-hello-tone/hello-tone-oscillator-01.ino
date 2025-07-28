#include <bb_spi_lcd.h>

#define TOUCH_MISO 39
#define TOUCH_MOSI 32
#define TOUCH_CLK 25
#define TOUCH_CS 33

#define SOUND_PIN 26

BB_SPI_LCD lcd;

void setup() {
  //
  // Need to begin the display to use the touch
  lcd.begin(DISPLAY_CYD);
  //
  // No buttons, just touch the screen to toggle the play state
  lcd.rtInit(TOUCH_MOSI, TOUCH_MISO, TOUCH_CLK, TOUCH_CS);
}

long stamp = millis();  // Sets the initial time stamp
long duration = 5;      // How long the tone plays each frequency
int low = 100;          // The low end of the oscillation
int freq = low;         // The initial frequency
int high = 1000;        // The high end of the oscillation
int direction = 1;      // The direction of oscillation: up or down
int step = 2;           // The change in frequency for each frequency change
bool canPlay = false;   // Flag for whether the tone is playing or not
bool isPressed = false; // Flag for whether the button is pressed or not
TOUCHINFO ti;

void loop() {
  //
  // We don't want a situation where pressing and holding on the screen
  //  rapidly changes our canPlay state off and on, so we need to keep 
  //  track of the state of whether the screen is being pressed.
  //
  // If there is a touch, and the screen is not already being touched ...
  if (lcd.rtReadTouch(&ti) && !isPressed) {
    canPlay = !canPlay;   // Toggle the canPlay state
    isPressed = true;     // Set the isPressed state to true
  //
  // If there is no touch ...
  } else if (!lcd.rtReadTouch(&ti)) {
    isPressed = false;    // Set the isPressed state to false
  }
  //
  // If the elapsed time since the tone was started is greater than our
  //  set duration, and the canPlay state is true ...
  if (((millis() - stamp) > duration) && canPlay) {
    tone(SOUND_PIN, freq);        // Play the tone
    freq += (step * direction);   // Increment the frequency by the given step in the given direction
    stamp = millis();             // Set a new time stamp
    //
    // If the frequency reaches or exceeds its bounds, change the 
    //  direction of increment
    if (freq >= high || freq <= low) {
      direction *= -1;
    }
  //
  // If the canPlay state is toggled to false ...
  } else if (!canPlay) {
    noTone(SOUND_PIN);            // Stop playing the tone
  }
}