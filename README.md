# Amiga-Digital-Video
Add pixel-perfect HDMI output to the Amiga machines.

For all Amiga versions that have a socketed Denise chip, a rather small adapter board can
be used to extract the digital video signal (12 bit) to a 40-pin connector compatible
with the Raspberry Pi Zero. This can then be used with the [RGBtoHDMI](https://github.com/hoglet67/RGBtoHDMI) software 
to produce a perfect HDMI picture with very low latency (a few milliseconds at most).

![](bootscreen.jpg)


## Stuff needed

The only hardware needed that can not be bought off-the-shelf is a small adapter board that goes
under the Denise chip.

The rest can be directly bought from many electronics retailers:
* Raspberry Pi Zero (any variant)
* Micro SD card (any)
* Mini-HDMI adapter or adapter cable (may already come in a set with the Pi)
* Some HDMI extension to reach the outside of the computer case

An optional push button can be added to allow forcing of specific output resolutions and other tweaks.
As the device auto-detects the monitor resolution and produces the best possible picture anyway,
this is normally not needed.


## Software

The Raspberry Pi needs to have a version of the RGBtoHDMI software on is SDCard. A compatible release of the 
software will eventually be available from the original repository at: https://github.com/hoglet67/RGBtoHDMI.
Until then I have mirrored a working [development release](misc/AmigaTest-v0-06.zip) for your convenience. 
Unzip the content of the archive to a micro SD card, formatted as FAT32. This card goes into the Rasperry Pi Zero 
and contains all software needed. 
Because the adapter board contains a configuration selector, the Amiga profile is already preselected and can be used directly.


## Installation - no soldering required

When you are not comfortable with a soldering iron or just don't have one, you can easily
obtain a Rasperry Pi Zero with preinstalled pin headers from various vendors. 
When you use this and don't require the optional menu button (for expert use only), the whole
installation is just done by plugging parts together. 
Depending on how you want to bring the HDMI signal out of the computer case, you may have to 
cut a hole in the case. Or to keep the case original, you could also bring the
cable out through some other opening (like the expansion port), or just do not close the case at all.

[Step by step installation instructions](installation/README.md)


## Compatibility

The current adapter board works with PAL and NTSC Amigas that have an OCS Denise (8362 variants).
An updated version of the board is currently in development that will also support a DIP-48 8373 SuperDenise
(sorry, Amiga 600 users), but only as long as none of the ECS screen modes are used.

Please note that the HDMI signal will not carry any audio. You still need to get the audio signal from
the RCA jacks as usual. If you absolutely have to merge the audio signal into HDMI there are
dedicated [external solutions](https://www.reichelt.at/at/en/hdmi-4k2k-audio-inserter-converter-ida-hdmi-ai4k-p247886.html?r=1)
for that.

Some monitors may refuse to work with a video signal with 50 frames per second as produced by the PAL Amiga variants.
In such a case you can force the upscaler to 60 frames mode by pressing the menu button during power-up.
If you have not installed the button, you can as well just semi-permanently put a jumper link on the button contacts
instead.
When you force 60 frames in such a way, you will experience screen-tearing or jumpy scrolling in games or demos, 
so this fall-back should only be used if it would not work at all otherwise.


## Build your own adapter board or get it ready-made

The board schematics and PCB design is open-source and part of the 
[RGBtoHDMI project](https://github.com/hoglet67/RGBtoHDMI/tree/master/kicad_AmigaAdapter/V1)
If you are not confident to solder parts with 0.65mm pin pitch, you can contact me via
(reinhard.grafl (at) aon.at) to get a completed board. I would give these away for €25 plus shipping. 
