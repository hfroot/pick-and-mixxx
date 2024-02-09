#include <MIDI.h>
#include <Button.h> // I have modified this library locally to use a delay of 100ms, not 500
#include "MidiPot.h"
#include "MidiButton.h"
#include "MidiRotaryEncoder.h"

MIDI_CREATE_INSTANCE(HardwareSerial, Serial, midiOut);

MidiPot slidePot1(midiOut, A0, 55);
MidiPot slidePot2(midiOut, A1, 56);
MidiPot slidePot3(midiOut, A2, 57);
// MidiPot slidePot4(midiOut, A3, 58);
MidiPot slidePot5(midiOut, A4, 59);
MidiPot slidePot6(midiOut, A5, 60);
MidiPot slidePot7(midiOut, A6, 61);
MidiPot slidePot8(midiOut, A7, 62);
MidiPot slidePot9(midiOut, A8, 63);

Button button1(35); // Connect your button between pin 35 and GND
Button button2(34);
Button button3(36);
Button button4(37);
Button button5(38);
Button button6(39);

MidiButton midiButton1(midiOut, button1, 71);
MidiButton midiButton2(midiOut, button2, 72);
MidiButton midiButton3(midiOut, button3, 73);
MidiButton midiButton4(midiOut, button4, 74);
MidiButton midiButton5(midiOut, button5, 75);
MidiButton midiButton6(midiOut, button6, 76);

MidiRotaryEncoder midiRotaryEncoder1(midiOut, 46, 48, 80);
MidiRotaryEncoder midiRotaryEncoder2(midiOut, 47, 49, 81);

void setup() {
  button1.begin();
  button2.begin();
  button3.begin();
  button4.begin();
  button5.begin();
  button6.begin();

  midiRotaryEncoder1.setup();
  midiRotaryEncoder2.setup();

  while (!Serial) { }; // for Leos

  Serial.begin(115200); // midi
  // Serial.begin(9600); // terminal
}

void loop() {
  slidePot1.sendChange();
  slidePot2.sendChange();
  slidePot3.sendChange();
//   slidePot4.sendChange();
  slidePot5.sendChange();
  slidePot6.sendChange();
  slidePot7.sendChange();
  slidePot8.sendChange();
  slidePot9.sendChange();

  midiButton1.sendChange();
  midiButton2.sendChange();
  midiButton3.sendChange();
  midiButton4.sendChange();
  midiButton5.sendChange();
  midiButton6.sendChange();

  midiRotaryEncoder1.sendChange();
  midiRotaryEncoder2.sendChange();
}
