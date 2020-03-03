/*
    MIDI input handler

    This sketch shows how to use the Serial or SoftwareSerial to read MIDI data.

    Dependencies:
    - Arduino MIDI Library - https://www.arduinolibraries.info/libraries/midi-library

    The circuit:
    - MIDI Breakout VCC connected to +5V pin
    - MIDI Breakout GND connected to GND pin
    - MIDI Breakout RX connected to RX pin or PIN_SW_RX

    This example code is in the public domain.
*/

#include <MIDI.h>

/**
    Enable/Disable usage of SoftwareSerial.
    Set to 1 if you need to log text to the serial console. When enabled you
    are free to use Serial.print functions.
*/
#define USE_SW_SERIAL   0

/** The RX pin to use in the sofware serial when enabled */
#define PIN_SW_RX       2

/** The RX pin to use in the sofware serial when enabled */
#define PIN_SW_TX       3

#if USE_SW_SERIAL
 #include <SoftwareSerial.h>
#endif

#if USE_SW_SERIAL
 #define DBG(x) Serial.println(x)
 SoftwareSerial swSerial (PIN_SW_RX, PIN_SW_TX);
 MIDI_CREATE_INSTANCE (SoftwareSerial, swSerial, MIDI);
#else
 #define DBG(x)
 MIDI_CREATE_DEFAULT_INSTANCE();
#endif

void handleNoteOn (byte channel, byte note, byte velocity) {
    DBG ("Handle Note On");
}

void handleNoteOff (byte channel, byte note, byte velocity) {
    DBG("Handle Note Off");  
}

void setup() {
   #if USE_SW_SERIAL
    Serial.begin (9600);
   #endif
    MIDI.begin (MIDI_CHANNEL_OMNI);
    MIDI.setHandleNoteOn (handleNoteOn);
    MIDI.setHandleNoteOff (handleNoteOff);
}

void loop() {
    MIDI.read();
}
