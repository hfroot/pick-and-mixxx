/*
	A tiny library to convert a sliding logarithmic potentiometer
    into an MDI signal using Arduino.

    Inspired by the Button library.
*/

#ifndef MidiSlidePot_h
#define MidiSlidePot_h
#include "Arduino.h"
#include <MIDI.h>

class MidiSlidePot
{
	public:
		MidiSlidePot(midi::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial> > midi_out, uint8_t pin, uint8_t midi_channel);
		void sendChange();
	
	private:
		midi::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial> > _midi_out;
		uint8_t  _pin;
		uint8_t _midi_channel;
		double _midi_conversion;
		uint8_t _previous_value;
};

#endif
