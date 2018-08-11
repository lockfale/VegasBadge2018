# VegasBadge2018
The badge to rule all SAOs in Vegas

## Modes and Buttons

There are two modes that the badge can be in:

* Color mode: Display a solid color with no change.
* Pattern mode: Displays a repeating pattern.

There are two buttons on the left side:

* SW1: Resets the CPU. There might be up to an 8 second wait.
* SW2: Changes different things based on the type of click:
  * Single Click: Cycles thru the different options within the current mode.
  * Double Click: Switches between modes.
  * Long Press: Shuts board down. Click SW1 to start badge back up.


## Menu System

The badges uses the SerialUI library (https://github.com/psychogenic/SerialUI)
for a menu system on the serial port.

The following is the current menu system:

```
TOP
   + colors              Change to solids colors
      * blue                Turn LEDs blue.
      * green               Turn LEDs green.
      * pink                Turn LEDs pink.
      * red                 Turn LEDs red.
      * yellow              Turn LEDs yellow.
   + patterns            Change LED patterns
      * chase               Chase the LEDs...
      * confetti            Party!!
      * popo                Popo coming...
      * rainbow             Taste the rainbow
      * strobe              Caution, may cause seizures!!
      * surge               Surging blue...
      * knight              Knight Rider
      * fire                Fire.. Fire!!!
      * groovy              Groovy man
      * smoothchase         A smoother chase
   + i2c                 SAO Communications
      * scan                Scan for SAOs
   + power               Power Savings
      * brightness          Toggle LED Brightness Level
      * sleep               Put badge into sleep mode
      * print               Print Power Configuration
  + debug               Debug
      * eeprom              Print EEPROM settings
```

The following are commands that are available on all menus:
```
..                  Move up to parent menu
?                   List available menu items
```

## Installation

### Prerequisites
  * python2-serial is required for **make upload**
  * screen is required for **make monitor**
  * Add account to dialup group or run make commands as root :(

### Setting up the Arduino build environment

Download the latest Arduino archive from https://www.arduino.cc/en/Main/Software

Uncompress archive: xz --decompress arduino-1.8.5-linux64.tar.xz

As root untar in /usr/local and create symlink:
```
    # cd /usr/local
    # tar xvf ~/Downloads/arduino-1.8.5-linux64.tar
    # ln -s arduino-1.8.5/ arduino
```

**NOTE:** This package should provide avrdude, avr-gcc, avr-g++, etc. The Arduino-Makefile should find these tools if the archive is installed in /usr/local/ardiono.
### Cloning this repository

As regular user, download badge code into home directory (--recursive will pull down dependency projects):
```
    cd
    git clone --recursive https://github.com/lockfale/VegasBadge2018.git
```

**NOTE:** If you clone the repository in a directory other than $HOME/VegasBadge2018, you will need to update the PROJECT_DIR line in VegasBadge2018/src/Makefile.

### Build and Upload to badge

Run the following commands in the src directory.

To build code:
```
    make
```

To upload to badge:
```
    make upload
```

### Connecting to the Serial Port

To connect serial port (requires screen):
```
    make monitor
```

To disconnect from the serial port in screen session:
```
    ^-a k Y
```

