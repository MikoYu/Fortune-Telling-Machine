# Fortune-Telling Machine

## The Project

The *Fortune-Telling Machine* is a speculative project about belief for a CCA MFA Design studio course: Carry-On Manufacturing (co-taught by Matthew Boyko & Helen Ip.) It illustrates an alien civilization that sends back a machine to the present to gather historical data. This machine can answer a question about a person's future with an edible cube, whose message can only be fully understood by being eaten. The design fiction is shown through a performative experience. The interaction between the audience and the machine is facilitated by an alien priest, an alien machine operator, and a human translator.

*For more info about the project: [link to be updated].* 



## Machine and Codes

This repository contains two versions of the Arduino codes for the Fortune-Telling Machine (in the "code" folder,) and the music files for the second and most recent version (in the "music" folder.) Both versions of the machine use Arduino Uno boards to control the electronic components to show certain automaticity. However, the structures of the two machines and components used are largely different. 

### Version 2 

The machine has three stacking modules:

- Box A on the top holds six inverted bottles of hot liquid. Each kind of liquid can flow through a tube to Box B, controlled by **an electric valve.** There is also a rectangular window at the bottom of the front side to reveal liquid movement. It is also wrapped by **an LED strip.** Together with **a sound speaker** attached inside, the LEDs show different effects to indicates machine calculation. Besides, **An Arduino Uno board** is placed in Box A. It can randomly select two kinds of liquid and switch between pre-determined sound/light effects.
- In the middle is Box B, the working space of the alien operator. Here are almost all the ingredients and tools to quickly make an agar agar jelly. A smaller window for presenting the final result is at the top on the front side. The operator pushes **a button** to control the Arduino which consequently switches among different states.  
- Finally, Box C, at the bottom, is the storage space for dry ice and other tools.

[sketch/photo]



For this version, we use one Uno board to control all the components. There are two programs used for the exhibition.

"Valves_only" is for valves installation, deinstallation, or other tests.

"FortuneTelling" is the main program. When the button is pushed, it executes the following cases:

1. Scanning: the light & sound tell the audience the machine is as if scanning their question and calculating the answer.
2. Drop liquid No.1: the program randomly switches a valve on and let the fluid flow down.
3. Drop liquid No.2: ditto.
4. Making: a series of light & sound effects, showing the machine is producing the results, counting down, and presenting the answer. During this 5-min period, the operator makes the jelly and delivering it through the window on Box B.

0. Default state: nothing happens.



[schematic]

[video]



### Version 1 

In terms of the mechanism, there are a lot of changes between the first and second versions. At this early prototyping stage, one Arduino Uno board controls 360° servo motor, a rotary encoder, a photocell, and a stepper motor. Another Uno board controls the neopixel strip.

Eight shot dispensers form a circle on the top of the machine, each holds a different kind of liquid. The operator does as follows: 

1. Push the button for neopixel. It will show scanning and calculating effects.
2. Push the other button for liquid selection: 
   - The UNO board randomly select two kinds of liquid. 
   - A 360° servo motor with a rotary encoder spin a disc around the center to bring a plugged funnel under the first designated dispenser. The operator needs to push up the dispenser to drop the liquid in a short time. 
   - Then the motor spin to bring another funnel under the second dispenser. The operator does the job again. 
   - The disc comes back to its default position. 
3. The operator mixes the liquid with agar agar jelly, unplug the funnels to release the mixture. The two mixtures slowIng flow past two spiral tubes, cooling down at the same time.
4. When they get closer to the end, the operator pushes the same button again for molding. The stepper motor will randomly select a pre-programmed movement. So the two mixtures can form different patterns.
5. Cool down and demold.

[sketch/photo]

[schematic]

This version was later replaced because the mixtures are easily stuck in the tubes.



## Credits

### Libraries



### Contributors





