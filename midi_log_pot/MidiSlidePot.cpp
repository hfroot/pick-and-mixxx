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
,  _previous_value(0) // 0-127
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

void MidiSlidePot::read()
{

  float potVal = analogRead(_pin);
  int midiVal = potVal * _midi_conversion;
  if (midiVal != _previous_value) {
    _midi_out.sendControlChange(_midi_channel, midiVal, 1);
    _previous_value = midiVal;
  }
}
