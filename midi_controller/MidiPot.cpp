/*
	A tiny library to convert a sliding logarithmic potentiometer
    into an MIDI signal using Arduino.
*/

#include "MidiPot.h"
#include <Arduino.h>
#include <MIDI.h>

MidiPot::MidiPot(midi::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial> > midi_out, uint8_t pin, uint8_t midi_channel)
:  _midi_out(midi_out)
,  _pin(pin)
,  _midi_channel(midi_channel)
// TODO: investigate whether analog max on the circuit
,  _midi_conversion((double)128/1024) // 128 = midi max; 1024 = analog max
,  _current_value(0) // 0-127
,  _previous_value(0) // 0-127
{
}

// 
// public methods
// 

void MidiPot::sendChange()
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

uint8_t MidiPot::_analog_to_midi()
{
  float potVal = analogRead(_pin);
  return potVal * _midi_conversion;
}

// wrapper in case of library change
void MidiPot::_send_midi_current_value()
{
  _midi_out.sendControlChange(_midi_channel, _current_value, 1);
}
