#include <MIDI.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial, midiOut);

const int ANALOG_READ_MAX = 1024;
const int POT_READ_MAX = 907; // from measurements
// Debugging tip: if midiVal not getting to 0, make this smaller
const int POT_READ_MIN = 10;
const int READ_MAX = POT_READ_MAX - POT_READ_MIN;
const int MIDI_MAX = 128;
const double MIDI_CONVERSION = (double)MIDI_MAX / READ_MAX;
const int LED_MAX = 256;
const int LED_CONVERSION = READ_MAX / LED_MAX;


void setup() {
  Serial.begin(115200); // midi
//  Serial.begin(9600); // terminal
}

// the the channel for the corresponding pin in at the same idx
int pins[] = {A2, A0};
int channels[] = {57, 56};
int previousVals[] = {READ_MAX, READ_MAX}; // this value is greater than anything analogRead will return
int pinCount = 2;

void loop() {
  for(int idx = 0; idx < pinCount; idx++) {
    pot(idx);
  }
}

void pot(int idx) {
  int potPin = pins[idx];
  float potVal = analogRead(potPin);
  
  int midiVal = potVal - POT_READ_MIN; // get rid of final volts
  midiVal = READ_MAX - midiVal; // flip rotation
  midiVal = midiVal * MIDI_CONVERSION;
  if (midiVal < 0) { midiVal = 0; }
  else if (midiVal >= MIDI_MAX) { midiVal = MIDI_MAX - 1; }

  if(previousVals[idx] == READ_MAX) {
    previousVals[idx] = midiVal; // get initial state
  }

  if(midiVal > previousVals[idx] || midiVal < previousVals[idx]) {
    midiOut.sendControlChange(channels[idx], midiVal, 1);
    previousVals[idx] = midiVal;
    delay(10);
  }
}