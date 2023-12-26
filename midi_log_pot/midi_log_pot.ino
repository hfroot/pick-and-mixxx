#include <MIDI.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial, midiOut);

const int ANALOG_READ_MAX = 1024;
const int MIDI_MAX = 128;
const double MIDI_CONVERSION = (double)MIDI_MAX / ANALOG_READ_MAX;

// the the channel for the corresponding pin in at the same idx
int ANALOG_PIN = A0;
int MIDI_CHANNEL = 55;
int previousValue = 0;

void setup() {
  while (!Serial) { }; // for Leos

  Serial.begin(115200); // midi
  // Serial.begin(9600); // terminal
}

void loop() {
  float potVal = analogRead(ANALOG_PIN);
  int midiVal = potVal * MIDI_CONVERSION;
  if (midiVal != previousValue) {
    midiOut.sendControlChange(MIDI_CHANNEL, midiVal, 1);
    previousValue = midiVal;
  }
}
