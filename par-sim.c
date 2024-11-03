// particle.c
#include <emscripten.h>
#include <stdlib.h>

typedef struct {
    float x, y;
    float vx, vy;
} Particle;

#define NUM_PARTICLES 1000
Particle particles[NUM_PARTICLES];

// Initialize particles
EMSCRIPTEN_KEEPALIVE
void initParticles() {
    for (int i = 0; i < NUM_PARTICLES; i++) {
        particles[i].x = (float)rand() / RAND_MAX * 800;
        particles[i].y = (float)rand() / RAND_MAX * 600;
        particles[i].vx = ((float)rand() / RAND_MAX * 2 - 1) * 2;
        particles[i].vy = ((float)rand() / RAND_MAX * 2 - 1) * 2;
    }
}

// Update particle positions
EMSCRIPTEN_KEEPALIVE
void updateParticles() {
    for (int i = 0; i < NUM_PARTICLES; i++) {
        particles[i].x += particles[i].vx;
        particles[i].y += particles[i].vy;
        
        // Bounce off walls
        if (particles[i].x < 0 || particles[i].x > 800) particles[i].vx *= -1;
        if (particles[i].y < 0 || particles[i].y > 600) particles[i].vy *= -1;
    }
}

// Get particle positions for rendering
EMSCRIPTEN_KEEPALIVE
float* getParticlePositions() {
    static float positions[NUM_PARTICLES * 2];
    for (int i = 0; i < NUM_PARTICLES; i++) {
        positions[i*2] = particles[i].x;
        positions[i*2+1] = particles[i].y;
    }
    return positions;
}
