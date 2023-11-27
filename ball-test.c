#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

// Ball structure
typedef struct {
    float x, y;  // Position
    float vx, vy;  // Velocity
    float angular_velocity;  // Angular velocity
    float spin;  // Spin
} Ball;

// Update the ball's state
void updateBall(Ball *ball, float dt) {
    // Update linear motion
    ball->x += ball->vx * dt;
    ball->y += ball->vy * dt;

    // Update angular motion
    ball->angular_velocity += ball->spin * dt;

    // Update the ball's orientation based on angular velocity
    // This depends on your rendering system; for example, rotating a sprite.
}

// Apply forces to the ball
void applyForces(Ball *ball, float speed, float spin) {
    // Apply linear force
    float angle = atan2(ball->vy, ball->vx);
    ball->vx = speed * cos(angle);
    ball->vy = speed * sin(angle);

    // Apply angular force (spin)
    ball->spin = spin;
}

// Apply friction to the ball
void applyFriction(Ball *ball, float friction, float dt) {
    // Apply linear friction
    ball->vx *= exp(-friction * dt);
    ball->vy *= exp(-friction * dt);

    // Apply angular friction
    ball->spin *= exp(-friction * dt);
}

// Apply curve to the ball
void applyCurve(Ball *ball, float curveFactor) {
    float lateralForce = ball->spin * curveFactor;
    // Apply lateral force to the ball's velocity
    // This could be done using trigonometry to compute lateral components.
}

// Display the ball's position
void displayBall(const Ball *ball) {
    int x = 49 - (int) ball->x;
    int y = 17 + (int) ball->y;
    printf("Ball Position: (%d, %d)\n", x, y);
    for (int i = 0; i < 50; ++i) {
        for (int j = 0; j < 35; ++j) {
            if (i == x && j == y) {
                printf("X");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    usleep(10000);
    system("clear");
}

int main() {
    // Initialize the ball with speed and spin
    Ball ball = {0.0, 0.0, 0.0, 0.0, 0.0};
    float initialSpeed = 5.0;
    float initialSpin = 0.1;

    // Set initial velocities
    ball.vx = 5.0;  // Example initial x velocity
    ball.vy = -3.0;  // Example initial y velocity

    // Apply initial forces
    applyForces(&ball, initialSpeed, initialSpin);

    // Simulation parameters
    float dt = 0.1;  // Time step
    float totalTime = 5.0;  // Total simulation time
    float currentTime = 0.0;

    // Game loop
    while (1) {
        // Update ball state
        updateBall(&ball, dt);
        applyFriction(&ball, 0.1, dt);
        applyCurve(&ball, 0.02);

        // Display ball position
        displayBall(&ball);

        // Increment time
        currentTime += dt;
    }

    return 0;
}
