# Atari-Digital-Video
Add a custom digital video port to Atari 8-Bit machines.

The Atari 8-bit line of computers could generate
a video dignal with 256 different colors.
Unluckily the quality of the output signal is
so bad that there is no hope of reconstructing
the "true" intent and subsequently any upscaling
solution will always carry all the noise. 

Some existing solutions involves a FPGA to monitor the 
digital signals inside the computer and produce
a cleaner analog RGB signal.

This project now tries a slightly different
approach to directly output the video with 8 
parallel digital lines. An FPGA or CPLD will
still be necessary, but maybe of a smaller
variant.
