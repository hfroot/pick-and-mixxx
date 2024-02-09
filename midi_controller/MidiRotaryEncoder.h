/*
	A tiny library to convert a rotary encoder
    into an MIDI signal using Arduino.

    Inspired by the Button library.
*/

#ifndef MidiRotaryEncoder_h
#define MidiRotaryEncoder_h
#include "Arduino.h"
#include <MIDI.h>

class MidiRotaryEncoder
{
	public:
		MidiRotaryEncoder(midi::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial> > midi_out, uint8_t clk_pin, uint8_t dt_pin, uint8_t midi_channel);
		void setup();
		void sendChange();
	
	private:
		midi::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial> > _midi_out;
		uint8_t  _clk_pin;
		uint8_t  _dt_pin;
		uint8_t _midi_channel;
		uint8_t _previous_clk_value;
        uint8_t _rotary_value;
        uint8_t _max_value;
		void _send_midi_current_value();
};

#endif
