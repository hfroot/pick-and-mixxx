#include <MIDI.h>
#include <Button.h> // I have modified this library locally to use a delay of 100ms, not 500
#include "MidiPot.h"

MIDI_CREATE_INSTANCE(HardwareSerial, Serial, midiOut);

const int ANALOG_READ_MAX = 1024;
const int MIDI_MAX = 128;
const double MIDI_CONVERSION = (double)MIDI_MAX / ANALOG_READ_MAX;

MidiPot slidePot1(midiOut, A0, 55);
MidiPot slidePot2(midiOut, A1, 56);
MidiPot slidePot3(midiOut, A2, 57);

Button button1(35); // Connect your button between pin 35 and GND

void setup() {
  button1.begin();

  while (!Serial) { }; // for Leos

  Serial.begin(115200); // midi
  // Serial.begin(9600); // terminal
}

void loop() {
  slidePot1.sendChange();
  slidePot2.sendChange();
  slidePot3.sendChange();

  if (button1.pressed()) {
     midiOut.sendControlChange(54, 127, 1);
  } else if (button1.released()) {
     midiOut.sendControlChange(54, 0, 1);
  }
}
