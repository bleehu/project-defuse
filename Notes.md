## 2024-01-24

Initial notes

I could totally make a physical, modular version
Timer module with classic red 7-seg display

Input elements
Toggle switches. DIP switches. Latching pushbuttons. Tactile switches. Tactile switches behind a little hole. Rotary switches. 16-step address switches. RGB illuminated switches. Covered toggle switches. Microswitches. Key switches, like a key for a lock. (Hard mode -- you have to pick it.) Momentary switches that you need to hold while doing something. Reed switches with magnets. 
Rotary encoders. Potentiometers. Slide pots.
Wires to cut.
Panels to be removed with various fasteners. Sense which screws are removed.
Operation, with plated edges for detecting jitter.
PCB cards to pull from slots and insert into other slots.
Ball bearing maze, with magnet to move it to different contact points.
Patch cables.
Batteries.
PIR motion sensor.
Temperature sensor.
Joysticks.
Capacitive touch.
Light sensors.
Humidity sensors.
Microphone.
Short pins or test points. 
NFC tag
Pull chips from sockets


Display elements
LEDs. 7-segment LED displays. More-segment displays could show difficult-to-describe characters. Character displays. Analog meters. Matrix displays. LED rings. 
Motor driving an indicator disk. 
Speakers. Piezo beepers.
Printed labels.
UV-reactive printed labels. Combine that with UV light sensors.
QR codes. Bar codes.
Nixie tubes.
E ink displays.
Stroboscopic display, synced to a spinning motor.
VFD.
Lighted placard. Just an LED with something to block it. What's this really called? 
Neon.
RGB LED with color printed sheet. Different colors show different symbols.
Volt meter across pins or test points.
PCB layout between different revisions of a board. 
Silkscreen.
Small electric shock
QR code LED matrix. Smallest QR code is 21x21. DIY LED matrix with JLC assembly is only a few dollars, but need several PCB stackup to construct it. Micro QR is as small as 11x11. A 15x15 micro QR is a good fit for a 16x16 LED matrix, but I can't get micro QR to scan.

Master module: timer display, disarm switch, strikes display, puzzle completion indicators, beeper.
Removable panel module: removable panel, security screws, screw removal detection, contains a sub-module.
Wire cut submodule: colored wires, EEPROM for board ID.
Circuit card submodule: several PCIe x1 connectors, assortment of boards with various resistors
Patch bay submodule: array of 3.5mm jacks, assorted patch cables
DIP switch submodule: array of DIP switches, 7-segment display
Cryptic module: 16-segment display, toggle switches
Meter module: analog meter, rotary switch, toggle switches
LED matrix maze module: RGB LED matrix, 4 direction tactile switches
Circuit probe submodule: 74HC373 with OE tied high lets us drive 16 other pins at will. But what else?
QR module: E-ink display (or other) displays QR code (smallest QR code is 21x21), changes every N seconds, need to enter a code



Communication protocol
    I'm thinking each module will be an RP2040, connected to the brain via USB. 
    Communication will be JSON transmitted over USB UART.


# Modules

## Master Module

This module contains the non-puzzle elements.

### User Interface
* Timer: 4-digit 7-segment LED display
* Disarm switch: Probably a momentary toggle
* Strikes: 1-digit 7-segment LED display
* Puzzle completion indicators: Single LEDs - tells you which puzzles are completed correctly
* Beeper: Piezo

### Internal elements
* The main microcontroller. 
    * Either implements the game logic itself, or communicates with a host computer which implements the game logic. 
    * Talks to the other microcontrollers to read and write state.
    * Controls the UI elements
* USB connector
    * For programming the system, or controlling the system from a host computer.


## Removable Panel Puzzle Carrier
This module encapsulates another puzzle and hides it behind a removable panel. Removing the panel is part of the puzzle.

### User Interface
* Screws: 4 screws mounting the panel. It can sense when each screw is removed.

### Internal elements
Probably will not have a separate microcontroller. Instead the submodule's microcontroller will connect to the screw sensors.


## Wire cut submodule



# Mechanical Design

What will be the largest puzzle?
    Analog meter is about 2", but there are some smaller options
    8x8 LED matrix is 1.25"
    Patch bay has a pitch of 0.4". 8-wide would be 3.2"
    QR code on an e-ink display. I see 

# Game Design

# Documentation