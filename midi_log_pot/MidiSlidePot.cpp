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
,  _previous_value_0(0) // 0-127
,  _previous_value_1(0) // 0-127
{
}

// TODO: consider implementing this to set initial value based on control position
// void MidiSlidePot::begin()
// {
// 	pinMode(_pin, INPUT_PULLUP);
// }

// 
// public methods
// 

void MidiSlidePot::sendChange()
{

  float potVal = analogRead(_pin);
  int midiVal = potVal * _midi_conversion;
  // Debouncing: compare against two values to avoid fluctuation,
  // presumably due to a position being in between two digital values
  if (midiVal != _previous_value_0 && midiVal != _previous_value_1) {
    _midi_out.sendControlChange(_midi_channel, midiVal, 1);
    _previous_value_1 = _previous_value_0;
    _previous_value_0 = midiVal;
  }
}
