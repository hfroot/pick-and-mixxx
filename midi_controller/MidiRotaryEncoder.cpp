/*
	A tiny library to convert a rotary encoder
    into an MIDI signal using Arduino.
*/

#include "MidiRotaryEncoder.h"
#include <Arduino.h>
#include <MIDI.h>

MidiRotaryEncoder::MidiRotaryEncoder(midi::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial> > midi_out, uint8_t clk_pin, uint8_t dt_pin, uint8_t midi_channel)
:  _midi_out(midi_out)
,  _clk_pin(clk_pin)
,  _dt_pin(dt_pin)
,  _midi_channel(midi_channel)
,  _previous_clk_value(LOW)
,  _rotary_value(0)
,  _max_value(127)
{
}

// Ideas:
// - make use of the push button (2x scroll speed maybe?)
// - figure out how to make the jumps in mixxx when scanning smaller

// 
// public methods
// 

void MidiRotaryEncoder::setup()
{
  pinMode(_clk_pin, INPUT);
  pinMode(_dt_pin, INPUT);
  _previous_clk_value = digitalRead(_clk_pin);
}

void MidiRotaryEncoder::sendChange()
{
  int clk = digitalRead(_clk_pin);
  if (_previous_clk_value == LOW && clk == HIGH) {
    int dt = digitalRead(_dt_pin);
    if (dt == LOW) {
      // clockwise
      if (_rotary_value == _max_value) {
        _rotary_value = 0;
      } else {
        _rotary_value++;
      }
    } else {
      // anti clockwise
      if (_rotary_value == 0) {
        _rotary_value = _max_value;
      } else {
        _rotary_value--;
      }
    }
    _send_midi_current_value();
  }
  _previous_clk_value = clk;
}

// wrapper in case of library change
void MidiRotaryEncoder::_send_midi_current_value()
{
  _midi_out.sendControlChange(80, _rotary_value, 1);
}