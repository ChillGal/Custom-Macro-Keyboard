# Custom-Macro-Keyboard
Custom designed macro keyboard

This was personal project for my partner as he is a streamer and the extra keys to bind to use is very useful while being cheaper than a Elgato stream deck.
The case was designed in Autodesk Fusion 360.

## Part choice
For this project, I knew I wanted a display for text, a volume control knob and at least 8 buttons. The buttons also had to have a nice feeling so i went with Cherry MX Brown switches as they are my partner's favourite kind of switch. I used re-legendable keycaps to allow for relabelling the keycaps at a later date if necessary. The components used in this project are:
- Arduino Pro Micro (I specifically looked for a USB-C version since it is most robust than USB-B Micro)
- Rotary Encoders with threads (KY-040) to mount to the base plate
- Cherry MX Brown switches (I bought a pack of 30 for future project use)
- 0.91" OLED i2C module (Black & White)
- USB-C Female Breakout board (To mount to the Base)
- USB-C Male connector (To prevent wear and tear to the USB-C port built on the arduino)
- Solid core wire (Various colours to aid in organisation)
- M3 Screws (To mount the key plate)
- M3 Threaded Inserts (To allow the screws to mount)

## Tools
To finish this project, the following tools were used which I consider essential:
- Soldering Iron
- 3D Printer (Creality CR-10S-Pro Stock) with PLA filament
- Screwdriver
- Wire cutters (Or scissors)
- A device capable of flashing code to the arduino
- Super Glue (for holding the display in place without moving)

## Design
The design of the case was done in Fusion Autodesk 360 over 8 iterations. It has an angle of 45&deg; for the keyplate with the keyplate while the display is mounted at a slightly steeper 60&deg; angle.



## Soldering the pins
I chose to solder pins rather than headers to the pcb so that i could easily hotswap it incase of failures since it is much easier to unplug 2 big headers than lots of small pins in order to take out the arduino. Another advantage is the size taken up by the pins which is significantly smaller height wise allowing to fit into the case without issue.
![](Photos/ArduinoHeaders.jpg "Soldered Pins rather than headers")

## Mounting the arduino
Since i had soldered the pins to the arduino, this came with some concerns. Mainly the worry that the pins could come in contact with a metal surface and short out which is particulary dangerous since it could kill the arduino. To prevent this, I came up with a small base plate that the arduino will slot into and sit on while the project is in developed
