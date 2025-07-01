# Circle and Sand Physics Simulation (SDL2)

This project is a graphical simulation built using **SDL2**, modeling a dynamic interaction of two elements:
- **Sand particles** that follow simple granular physics
- **Bouncing circles** affected by gravity and wall/floor collisions

It demonstrates physics concepts such as gravity, velocity damping, and collision response in a real-time interactive environment.

## Features

- Real-time simulation of falling sand particles using a grid-based approach
- Circle physics with gravity, bounce, damping, and wall constraints
- Custom circle drawing using midpoint circle algorithm
- Interactive: click and hold to spawn sand
- Built on top of SDL2 for 2D graphics rendering

## File Overview

| File | Purpose |
|------|---------|
| `InitializeScene.cpp` | Main entry point. Initializes SDL, handles the event loop, mouse input, and sand simulation logic. |
| `CirclePhysics.h / CirclePhysics.cpp` | Defines the `Circle` struct and handles physics updates (gravity, bounce, friction). |
| `CreateCircle.h / CreateCircle.cpp` | Implements the custom circle drawing routine using SDL_Renderer. |

## How It Works

- **Sand Simulation**: A 2D grid stores particle types (`EMPTY`, `SAND`). Sand moves bottom-up, checking below and diagonal cells for possible movement.
- **Circle Physics**: A `Circle` has position, velocity, and radius. It responds to gravity and collisions with the floor or screen edges.
- **Rendering**: SDL is used to draw sand particles as filled rectangles and circles as outlines using calculated points.

## Dependencies

- **SDL2** development libraries
    - On Ubuntu: `sudo apt install libsdl2-dev`
    - On macOS: `brew install sdl2`
    - On Windows: Install via vcpkg or manually link SDL2

## Building

Compile using a C++ compiler with SDL2 linked. Example using `g++`:

```bash
g++ InitializeScene.cpp CirclePhysics.cpp CreateCircle.cpp -o sim -lSDL2
```

Then run with:
```
./sim
```
