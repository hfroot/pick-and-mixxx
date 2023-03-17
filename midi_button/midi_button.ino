#include <MIDI.h>
#include <Button.h>

int resetFlag = 0;

MIDI_CREATE_INSTANCE(HardwareSerial, Serial, midiOut);

Button button1(22); // Connect your button between pin 22 and GND

void setup() {
  button1.begin();

  while (!Serial) { }; // for Leos

  Serial.begin(115200);
}

void loop() {
//  int reading = digitalRead(22);
//  delay(10);
//  int newReading = digitalRead(22);
//  if (reading == newReading) {
//    if (reading == LOW && resetFlag == 0) {
//      midiOut.sendControlChange(56, 127, 1); // send a MIDI CC -- 56 = note, 127 = velocity, 1 = channel
//      resetFlag = 1;
//    } else if (reading == HIGH && resetFlag == 1) {
//      midiOut.sendControlChange(56, 0, 1); // send a MIDI CC -- 56 = note, 127 = velocity, 1 = channel
//      resetFlag = 0;
//    }
//  }
  if (button1.pressed()) {
     midiOut.sendControlChange(56, 127, 1);
  } else if (button1.released()) {
     midiOut.sendControlChange(56, 0, 1);
  }

}
