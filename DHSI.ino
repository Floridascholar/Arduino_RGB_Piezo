/*
  Arduino Rainbow What the World Needs Now
  Based on Arduino Sketches
  https://learn.adafruit.com/adafruit-arduino-lesson-3-rgb-leds/arduino-sketch
  https://www.arduino.cc/en/Tutorial/toneMelody
  https://www.arduino.cc/en/Tutorial/StateChangeDetection
  Collaborative Project by @Emily_F_Brooks and @rtan00
 */
#include "pitches.h"

//Digital pin 2
const int buttonPin = 2;
//initialize button state
int buttonState = 0;
//initialize previous button state
int lastButtonState = 0;

int piezoPin = 3;

//use Arduino pins with PWM (pulse width modulation) for RGB LEDs
int redPin = 11;
int greenPin = 10;
int bluePin = 9;

//Make arrays for R, G, and B values on scales of 0-255 
//(Red = 255,0,0; Orange = 255,165,0; Yellow= 255,255,0; 
//Green= 0,255,0; Teal= 0,255,255; Blue= 0,0,255; Violet= 255,0,255)
int first[]= {
  255, 255, 255, 0, 0, 0, 255, 
  255, 255, 255, 0, 0, 0, 255, 
  255, 255, 255, 0, 0, 0, 255, 255, 255};
int second[]= {
  0, 165, 255, 255, 255, 0, 0, 
  0, 165, 255, 255, 255, 0, 0, 
  0, 165, 255, 255, 255, 0, 0, 0, 165};
int third[]= {
  0, 0, 0, 0, 255, 255, 255, 
  0, 0, 0, 0, 255, 255, 255, 
  0, 0, 0, 0, 255, 255, 255, 0, 0};

//What the World Needs Now melody
int melody[] = {
  NOTE_D4, NOTE_F4, NOTE_C5, 
  NOTE_C5, NOTE_A4, 
  NOTE_C4, NOTE_C5,
  NOTE_C5, NOTE_A4, 
  0,

  NOTE_G4, NOTE_F4, NOTE_G4, NOTE_D4, NOTE_F4,
  NOTE_D4, NOTE_F4, NOTE_A4, 
  NOTE_C4, NOTE_A4, NOTE_G4, NOTE_G4,
  0,
};

//What the World Needs Now tempo
int noteDurations[] = {
  4, 4, 2, 
  4, 2,
  4, 2, 
  4, 1,
  8,

  8, 8, 8, 8, 2,
  4, 4, 2, 
  4, 8, 8, 4,
  8,
};


void setup() {
  //set pins connected to RGB LED as outputs
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT); 
  //set pin connected to button as input
  pinMode(buttonPin, INPUT); 
}


void loop() {
  //read button pin 2
  buttonState = digitalRead(buttonPin);
  // compare the buttonState to its previous state
  if(buttonState != lastButtonState){
    //begin if/else statement testing that button has been pressed
    if (buttonState == HIGH) {  

      // iterate over the notes of the melody; thisNote < #,
      //where # corresponds to how many notes there are
      for (int thisNote = 0; thisNote < 22; thisNote++) {

        // to calculate the note duration, take one second 
        // divided by the note type.
        //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int noteDuration = 1600/noteDurations[thisNote];
        //tone on piezoPin (must be PWM)
        tone(piezoPin, melody[thisNote],noteDuration);
        setColor(first[thisNote], second[thisNote], third[thisNote]);

        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        // stop the tone playing:
        noTone(3); 
      } 
    }
    else{
      noTone(3);
      setColor(0,0,0);
    }
  } 
  // save the current state as the last state,
  //for next time through the loop
  lastButtonState = buttonState;
}

void setColor(int red, int green, int blue)
{
#ifdef COMMON_ANODE
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
#endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}

