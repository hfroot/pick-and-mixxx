#include <MIDI.h>
#include "MidiSlidePot.h"

MIDI_CREATE_INSTANCE(HardwareSerial, Serial, midiOut);

const int ANALOG_READ_MAX = 1024;
const int MIDI_MAX = 128;
const double MIDI_CONVERSION = (double)MIDI_MAX / ANALOG_READ_MAX;

MidiSlidePot slidePot1(midiOut, A0, 55);
MidiSlidePot slidePot2(midiOut, A1, 56);

void setup() {
  while (!Serial) { }; // for Leos

  Serial.begin(115200); // midi
  // Serial.begin(9600); // terminal
}

void loop() {
  slidePot1.read();
  slidePot2.read();
}
