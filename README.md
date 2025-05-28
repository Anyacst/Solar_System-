# solar_system

A simple SDL2-based simulation of a solar system with orbiting planets.

## Overview

This project visualizes a solar system using the SDL2 graphics library in C.  
It simulates planets orbiting a central sun, with interactive controls to add or remove planets, adjust their speeds, and zoom in/out.  
Zooming can be controlled both by keyboard keys and mouse scroll wheel for intuitive navigation.

## Features

- Visualize a sun and multiple orbiting planets with different colors and sizes.
- Planets move along elliptical orbits with adjustable speed.
- Interactive keyboard controls to:
  - Add (`a`) and remove (`r`) planets dynamically.
  - Increase (`[`) and decrease (`]`) planet orbital speeds.
  - Zoom in (`+` or `=`) and zoom out (`-`).
- Mouse wheel zooming for smooth zoom control.
- Remove planets by right-clicking on them.
- Smooth animations using SDL2 rendering and double buffering.

## Controls

| Key/Button         | Action                        |
|--------------------|-------------------------------|
| `a`                | Add a new planet              |
| `r`                | Remove the last added planet  |
| `[`                | Increase speed of all planets |
| `]`                | Decrease speed of all planets |
| `+` or `=`         | Zoom in                      |
| `-`                | Zoom out                     |
| Mouse wheel scroll  | Zoom in/out                  |
| Right mouse click   | Remove planet clicked on     |
| Close window       | Exit the simulation           |

## Requirements

- SDL2 development libraries installed on your system.
- GCC or compatible C compiler.

## Build Instructions

1. Ensure SDL2 development libraries are installed.
2. Clone or download the project source code.
3. Open a terminal and navigate to the project directory.
4. Run the build command:

    ```bash
    make
    ```

5. Run the executable:

    ```bash
    ./solar_system
    ```

## File Structure

- `main.c` — Program entry point, event handling, and main loop.
- `planet.c` — Functions for planet creation, drawing, and movement.
- `main.h` — Shared declarations and data structures.
- `Makefile` — Build instructions.

## Notes

- The simulation uses a linked list to manage planets dynamically.
- Planet colors and properties are randomized for variety.
- Designed for learning and demonstration purposes with SDL2 and C.
- Mouse wheel zooming allows intuitive zoom control.

## License

This project is open source and free to use.
