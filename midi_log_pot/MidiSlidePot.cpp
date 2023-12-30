/*
	A tiny library to convert a sliding logarithmic potentiometer
    into an MDI signal using Arduino.
*/

#include "MidiSlidePot.h"
#include <Arduino.h>
#include <MIDI.h>

MidiSlidePot::MidiSlidePot(midi::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial> > midi_out, uint8_t pin, uint8_t midi_channel)
:  _midi_out(midi_out)
,  _pin(pin)
,  _midi_channel(midi_channel)
,  _midi_conversion((double)128/1024) // 128 = midi max; 1024 = analog max
,  _current_value(0) // 0-127
,  _previous_value(0) // 0-127
{
}

// 
// public methods
// 

void MidiSlidePot::sendChange()
{
  uint8_t midiVal = _analog_to_midi();
  // Debouncing: compare against two values to avoid fluctuation,
  // presumably due to a position being in between two digital values
  if (midiVal != _current_value && midiVal != _previous_value) {
    _previous_value = _current_value;
    _current_value = midiVal;
    _send_midi_current_value();
  }
}

//
// private methods
//

uint8_t MidiSlidePot::_analog_to_midi()
{
  float potVal = analogRead(_pin);
  return potVal * _midi_conversion;
}

// wrapper in case of library change
void MidiSlidePot::_send_midi_current_value()
{
  _midi_out.sendControlChange(_midi_channel, _current_value, 1);
}
