#include "CirclePhysics.h"
#include <SDL.h>
#include <cmath>

void updateCirclePhysics(Circle& circle, int screenWidth, int screenHeight) {
    const float gravity = 0.8f;       // Stronger gravity
    const float damping = 0.85f;      // Bounces retain more energy
    const float velocityThreshold = 0.1f; // Stop bouncing when small enough
    const float groundFriction = 0.98f;

    // Apply gravity
    circle.velY += gravity;

    // Update position
    circle.x += circle.velX;
    circle.y += circle.velY;

    // Bounce off the floor
    if (circle.y + circle.radius > screenHeight) {
        circle.y = screenHeight - circle.radius;
        circle.velY *= -damping;

        // Friction slows horizontal motion
        circle.velX *= groundFriction;

        // Stop bouncing if velocity is small
        if (std::abs(circle.velY) < velocityThreshold) {
            circle.velY = 0;
        }
        if (std::abs(circle.velX) < velocityThreshold) {
            circle.velX = 0;
        }
    }

    // Optional: bounce off walls
    if (circle.x - circle.radius < 0 || circle.x + circle.radius > screenWidth) {
        circle.velX = -circle.velX * damping;
        if (circle.x - circle.radius < 0) circle.x = circle.radius;
        if (circle.x + circle.radius > screenWidth) circle.x = screenWidth - circle.radius;
    }
}

