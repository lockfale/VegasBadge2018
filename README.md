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

