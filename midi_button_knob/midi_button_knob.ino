#include <MIDI.h>

int val = 60;
int stepDirection = -1; // will switch immediately to +1 so first direction is positive
int stepSize = 5;
int previousState = HIGH;
int LOWEST_VELOCITY = 0;
int HIGHEST_VELOCITY = 127;

MIDI_CREATE_INSTANCE(HardwareSerial, Serial, midiOut);

void setup() {
  pinMode(9, INPUT_PULLUP);

  Serial.begin(115200); 
}

void loop() {
  int reading = digitalRead(9);
  delay(10);
  int newReading = digitalRead(9);
  if (reading == newReading) {
    // HIGH -> LOW : new press
    // LOW -> LOW : press and hold
    // LOW -> HIGH : release
    if (previousState == HIGH && reading == LOW) {
      // new press
      previousState = LOW;
      stepDirection *= -1; // switching here so can do double press to continue in same direction
      delay(200); // allow user time to release if they want to stay in same direction
    } else if (previousState == LOW && reading == LOW) {
      // press is held
      int s = stepDirection * stepSize;
      if (val + s > LOWEST_VELOCITY && val + s < HIGHEST_VELOCITY) {
        val += s;
        midiOut.sendControlChange(56, val, 1);
        delay(100);
      }
    } else if (previousState == LOW && reading == HIGH) {
      // release
      previousState = HIGH;
    }
  }

}
