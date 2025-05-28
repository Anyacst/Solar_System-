#ifndef PLANET_H
#define PLANET_H

#include </opt/homebrew/include/SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>

#define WIDTH 1100
#define HEIGHT 1100
#define BLACK_COLOR 0x000000
#define SUN_COLOR 0xFE9900
#define RING_COLOR 0xFFFFFF
#define CENTER_X 550
#define CENTER_Y 550
#define TAIL_LENGTH 100

struct Position {
    int x, y;
};

struct Planet {
    int x;
    int y;
    double radius;
    int a;
    int b;
    double theta;
    double speed;
    double max_speed, min_speed;
    uint32_t color;
    struct Planet *prev;
    struct Planet *next;
    struct Position tail[TAIL_LENGTH];
    int tail_index;
};


// Getter for planet color (new)
uint32_t get_planet_color(int index);

void set_color(SDL_Renderer *renderer, uint32_t color);
void draw_circle(SDL_Renderer *renderer, struct Planet *planet, uint32_t color, float zoom);
void draw_rings(SDL_Renderer *renderer, struct Planet *planet, uint32_t color, int num, float zoom);
void planet_speed(struct Planet *planet, float zoom);
void draw_planet(SDL_Renderer *renderer, struct Planet *planet, int num, float zoom);
void add_planet(struct Planet **planet, struct Planet **Last_planet, int *num);
void remove_planet(struct Planet **Last_planet, int *num);
void delete_planet_by_mouse(struct Planet **head, struct Planet **last, struct Planet *current, int *num);
int isinsidetheplanet(int mx, int my, struct Planet *temp, float zoom);
void increase_speed_of_planet(struct Planet *planet);
void decrease_speed_of_planet(struct Planet *planet);

#endif
