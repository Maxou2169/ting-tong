# Altitude, a simple 3D Wireframe map editor

This little project aims to implement Perlin Noise generation for terrains.
It also aims to be a simple example on how to generate a terrain.

## How to use it?

Compile using `make`. The launch it with `./bin/altitude -f {file to display}` if you want to project a special file,
or with `./bin/altitude -g {size_x} {size_y}` to generate a new random terrain.

## Interacting inside the window

- `ESCAPE` To quit the program
- `Z` To move up the
- `S` To move down
- `Q` To move left
- `D` To move right
- `T` and `Y` to tilt arround the X-axis
- `G` and `H` to tilt arround the Y-axis
- `B` and `N` to tilt arround the Z-axis

Options :
 - `./bin/affichage .... -e {file to export}` is a useful option to export the generated terrain.