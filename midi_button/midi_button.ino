#include <MIDI.h>

int resetFlag = 0;

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
    if (reading == LOW && resetFlag == 0) {
      midiOut.sendControlChange(56, 127, 1); // send a MIDI CC -- 56 = note, 127 = velocity, 1 = channel
      resetFlag = 1;
    } else if (reading == HIGH && resetFlag == 1) {
      midiOut.sendControlChange(56, 0, 1); // send a MIDI CC -- 56 = note, 127 = velocity, 1 = channel
      resetFlag = 0;
    }
  }

}
