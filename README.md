# VegasBadge2018
The badge to rule all SAOs in Vegas

## If you need to setup an Arduino build environment:

Download the latest Arduino archive from https://www.arduino.cc/en/Main/Software

Uncompress archive: xz --decompress arduino-1.8.5-linux64.tar.xz

As root untar in /usr/local and create symlink:
```
    # cd /usr/local
    # tar xvf ~/Downloads/arduino-1.8.5-linux64.tar
    # ln -s arduino-1.8.5/ arduino
```

As regular user, download badge code into home directory (--recursive will pull down dependency projects):
```
    cd
    git clone --recursive https://github.com/lockfale/VegasBadge2018.git
```

## Build and Upload to badge

To build code:
```
    make
```

To upload to badge:
```
    make upload
```

To connect serial port (requires screen):
```
    make monitor
```

To disconnect from the serial port in screen session: 
```
    ^-a k Y
```

## Menu System

The badges uses the SerialUI library for a menu system on the serial port.

The following is the current menu system:

```
TOP
   + colors              Change to solids colors 
      * pink                Make the LEDs pink... 
      * red                 Make the LEDs red... 
      * green               Make the LEDs green... 
      * blue                Make the LEDs blue... 
   + patterns            Change LED patterns 
      * chase               Chase the LEDs... 
      * confetti            Party!! 
      * popo                Popo coming... 
      * rainbow             Taste the rainbow 
      * strobe              Caution, may cause seizures!! 
      * surge               Surging blue...
   + i2c                 SAO Communications 
      * scan                Scan for SAOs
   + power               Power Savings 
      * brightness          Toggle LED Brightness Level 
      * print               Print Power Configuration
  + debug               Debug 
      * eeprom              Print EEPROM settings
```

The following are commands that are available on all menus:
```
..                  Move up to parent menu
?                   List available menu items
```

