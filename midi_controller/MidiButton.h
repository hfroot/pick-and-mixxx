/*
	A tiny library to convert a button press
    into an MIDI signal using Arduino.

    Inspired by the Button library.
*/

#ifndef MidiButton_h
#define MidiButton_h
#include "Arduino.h"
#include <MIDI.h>
#include <Button.h>

class MidiButton
{
	public:
		MidiButton(midi::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial> > midi_out, Button button, uint8_t midi_channel);
		void sendChange();
	
	private:
		midi::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial> > _midi_out;
		Button  _button;
		uint8_t _midi_channel;
		void _send_midi_bool(bool state);
};

#endif
