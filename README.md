# Solar_System-

solar_system

A simple SDL2-based simulation of a solar system with orbiting planets.

Overview

This project visualizes a solar system using SDL2 graphics library in C. It simulates planets orbiting a central sun, with interactive controls to add or remove planets, adjust their speeds, and zoom in/out. Zooming can be controlled both by keyboard keys and mouse scroll wheel for intuitive navigation.

Features

Visualize a sun and multiple orbiting planets with different colors and sizes.
Planets move along elliptical orbits with adjustable speed.
Interactive keyboard controls to:
Add (a) and remove (r) planets dynamically.
Increase ([) and decrease (]) planet orbital speeds.
Zoom in (+/=) and zoom out (-).
Mouse wheel zooming for smooth zoom control.
Remove planets by right-clicking on them.
Smooth animations using SDL2 rendering and double buffering.
Controls

Key/Button	Action
a	Add a new planet
r	Remove the last added planet
[	Increase speed of all planets
]	Decrease speed of all planets
+ or =	Zoom in
-	Zoom out
Mouse wheel scroll	Zoom in/out
Right mouse click	Remove planet clicked on
Close window	Exit the simulation
Requirements

SDL2 library installed on your system.
GCC compiler or compatible C compiler.
Build Instructions

Ensure SDL2 development libraries are installed.
Clone or download the project source code.
Open a terminal and navigate to the project directory.
Run:
make
Run the executable:
./solar_system
File Structure

main.c — Program entry point, event handling, and main loop.
planet.c — Functions related to planet creation, drawing, and movement.
main.h — Shared declarations and data structures.
Makefile — Build script for compiling the project.
Notes

The simulation uses a simple linked list to manage planets.
Colors and planet properties are randomized for variety.
Designed for educational purposes and as a demonstration of SDL2 and C programming.
Mouse wheel zooming allows intuitive control over zoom level.
License

This project is open source and free to use.

