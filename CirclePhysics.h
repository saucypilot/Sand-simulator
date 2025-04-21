#ifndef CIRCLE_PHYSICS_H
#define CIRCLE_PHYSICS_H

#include <SDL.h>

struct Circle {
    float x, y;       // Position
    int radius;     // Radius
    float velX, velY; // Velocity in X and Y directions
};

void updateCirclePhysics(Circle& circle, int screenWidth, int screenHeight);

#endif
