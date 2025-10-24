# Digital-watch-emulator-in-SDL2
Basic digital watch emulator, written by myself in C using SDL2 as a learning exercise.

# Demo
![Demo](assets/demo.gif)

The face was made in inkscape and exported to a png format.
The LCD's are created using SDL's polygon drawing feature.
The entire program runs at a smooth 100 frames per second.
I have added stopwatch functionality as well as keep time.
It isn't difficult to extend functionality through the fsm.c file which implements much of the logic.
Most notably the functionality to set the time and run countdown timers and so on is absent, but adding this wouldn't be a big learning experience so I passed it over.
The frequency and duration of the "beep" is hardcoded in the watch.c file and can be changed at will.
I was able to compile and run the program on a Windows 10 virtual machine without to much trouble.
The build script is a simple bash script that runs on my Arch Linux workstation.
