/*
	A tiny library to convert a button press
    into an MIDI signal using Arduino.
*/

#include "MidiButton.h"
#include <Arduino.h>
#include <MIDI.h>
#include <Button.h>

MidiButton::MidiButton(midi::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial> > midi_out, Button button, uint8_t midi_channel)
:  _midi_out(midi_out)
,  _button(button)
,  _midi_channel(midi_channel)
{
}

// 
// public methods
// 

void MidiButton::sendChange()
{
  if (_button.pressed()) {
    _send_midi_bool(true);
  } else if (_button.released()) {
    _send_midi_bool(false);
  }
}

//
// private methods
//

// wrapper in case of library change
void MidiButton::_send_midi_bool(bool state)
{
    uint8_t value = 0;
    if (state == true) {
        value = 127;
    }
    _midi_out.sendControlChange(_midi_channel, value, 1);
}
