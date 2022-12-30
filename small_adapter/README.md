# Small adapter 

For installation in an A600 or for other constrained installation, I have designed a generic adapter. 
Instead of being a plug-and-play solution, this board needs substantial soldering of individual wires.
Gerber files, schematics and BOM are available at https://github.com/hoglet67/RGBtoHDMI/tree/master/kicad_AmigaAdapter/Small .

![](smalladapter.png)

Use this issue thread for discussions on this special topic:
https://github.com/c0pperdragon/Amiga-Digital-Video/issues/22

I have now prepared kits for this small adapter containing one PCB and the necessary SMD parts. By sending these
kits in an untracked envelope, I can offer them for €6 including international postage.
If you want to get one, please drop me an e-mail  (address below in the contact information).


## Kit content

![](parts.jpg)

To be able to send it in a simple envelope, only the SMD parts are included. If you want to make the board detachable from the Pi,
you also need to get a female 40-pin connector.

There are basically the PCB, the ICs and the passives. It is easy to see which ICs go where - just make sure to get the orientation correct 
(pin 1 is marked on the board as well as on the ICs themselves).
C1, C2, C3 are the 100nF capacitors in the strip with 3 parts.
R1, R2 are 3k3 resistors in the strip with 2 parts.
C4 is a 1uF capacitor in the transparent strip all on its own.


## Installation

After soldering all the parts to the board, connect the board on top of the Raspberry Pi zero. The cheapest possible way is to just stick the board onto 
the GPIO pins of the Pi and solder it in place (make sure to leave a bit of space in between to allow heat dissipation). For a detachable solution,
you can also add a female 40-pin header to the underside of the adapter board first. 

After that find some convenient position in your Amiga and mount the Pi together with the adapter board with whatever means is convenient to you. 
Then wire up all the input signals to the proper positions on your main board.
The locations from where to get the signals are depending on the type of the machine and the board revision. There is quite an active community already discussing this topics 
in various issue threads. The Amiga 600 installation is specifically handled in  https://github.com/c0pperdragon/Amiga-Digital-Video/issues/22

The rest of the installation and operation works like for the standard Denise adapter. 
