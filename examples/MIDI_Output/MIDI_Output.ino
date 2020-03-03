/*
    MIDI note player

    This sketch shows how to use the Serial or SoftwareSerial to send MIDI note
    data. If this circuit is connected to a MIDI synth, it will play the notes
    F#-0 (0x1E) to F#-5 (0x5A) in sequence.

    The circuit:
    - MIDI Breakout VCC connected to +5V pin
    - MIDI Breakout GND connected to GND pin
    - MIDI Breakout TX connected to TX pin or PIN_SW_RX

    This example code is in the public domain.
*/

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
#else
 #define DBG(x)
#endif

void sendNote (bool on, uint8_t pitch, uint8_t velocity) {
   #if USE_SW_SERIAL
    swSerial.write (on ? 0x80 : 0x90);
    swSerial.write (pitch);
    swSerial.write (velocity);
   #else
    Serial.write (on ? 0x80 : 0x90);
    Serial.write (pitch);
    Serial.write (velocity);
   #endif
}

void setup() {
   #if USE_SW_SERIAL  
    swSerial.begin (31250);
    Serial.begin (9600);
   #else
    Serial.begin (31250);
   #endif
}

void loop() {
  // play notes from F#-0 (0x1E) to F#-5 (0x5A):
    for (uint8_t note = 0x1E; note < 0x5A; note++) {
        // send note on
        sendNote (true, note, 0x45);
        delay (500);

        // send note off
        sendNote (false, note, 0x00);
        delay (250);
    }
}
