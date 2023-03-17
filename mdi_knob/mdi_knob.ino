#include <MIDI.h>
#include <Button.h>

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

// the the channel for the corresponding pin in at the same idx
int analogs[] = {A2, A0, A1};
int analogChannels[] = {57, 56, 55};
int previousAnalogVals[] = {READ_MAX, READ_MAX, READ_MAX}; // this value is greater than anything analogRead will return
int analogCount = 3;

//int buttonPins[] = {22};
Button button1(24); // Connect your button between pin 22 and GND
Button button2(22);
Button buttons[] = {button2, button1};
int btnChannels[] = {61, 60};
int buttonCount = 2;

void setup() {
  button1.begin();
  button2.begin();

  while (!Serial) { }; // for Leos

  Serial.begin(115200); // midi
//  Serial.begin(9600); // terminal
}

void loop() {
  for(int idx = 0; idx < analogCount; idx++) {
    pot(idx);
  }
  for(int idx = 0; idx < buttonCount; idx++) {
    button(idx);
  }
}

void pot(int idx) {
  int potPin = analogs[idx];
  float potVal = analogRead(potPin);
  
  int midiVal = potVal - POT_READ_MIN; // get rid of final volts
  midiVal = READ_MAX - midiVal; // flip rotation
  midiVal = midiVal * MIDI_CONVERSION;
  if (midiVal < 0) { midiVal = 0; }
  else if (midiVal >= MIDI_MAX) { midiVal = MIDI_MAX - 1; }

  if(previousAnalogVals[idx] == READ_MAX) {
    previousAnalogVals[idx] = midiVal; // get initial state
  }

  if(midiVal > previousAnalogVals[idx] || midiVal < previousAnalogVals[idx]) {
    midiOut.sendControlChange(analogChannels[idx], midiVal, 1);
    previousAnalogVals[idx] = midiVal;
    delay(10);
  }
}
int resetFlag = 0;

void button(int idx) {
  if (buttons[idx].pressed()) {
     midiOut.sendControlChange(btnChannels[idx], 127, 1);
  } else if (buttons[idx].released()) {
     midiOut.sendControlChange(btnChannels[idx], 0, 1);
  }
}
