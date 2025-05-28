#include "main.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
    srand((unsigned int)time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize. SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Solar System",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        SDL_WINDOW_SHOWN);

    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    struct Planet sun = { CENTER_X, CENTER_Y, 80, 0, 0, 0, 0, 0, 0, SUN_COLOR, NULL, NULL };
    SDL_Event e;
    int running = 1;

    struct Planet *planet = NULL;
    struct Planet *Last_planet = NULL;
    int num_planets = 0;
    float zoom = 1.0f;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = 0;

            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_PLUS || e.key.keysym.sym == SDLK_EQUALS) {
                    zoom += 1.0f;
                    if (zoom > 5.0f) zoom = 5.0f;
                } else if (e.key.keysym.sym == SDLK_MINUS) {
                    zoom -= 0.1f;
                    if (zoom < 0.1f) zoom = 0.1f;
                } else if (e.key.keysym.sym == SDLK_a) {
                    add_planet(&planet, &Last_planet, &num_planets);
                } else if (e.key.keysym.sym == SDLK_r) {
                    remove_planet(&Last_planet, &num_planets);
                } else if (e.key.keysym.sym == SDLK_LEFTBRACKET) {
                    increase_speed_of_planet(planet);
                } else if (e.key.keysym.sym == SDLK_RIGHTBRACKET) {
                    decrease_speed_of_planet(planet);
                }

            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (e.button.button == SDL_BUTTON_RIGHT) {
                    int mx = e.button.x;
                    int my = e.button.y;

                    struct Planet *current = planet;
                    while (current != NULL) {
                        struct Planet *next = current->next;
                        if (isinsidetheplanet(mx, my, current, zoom)) {
                            delete_planet_by_mouse(&planet, &Last_planet, current, &num_planets);
                            break;
                        }
                        current = next;
                    }
                }
            } else if (e.type == SDL_MOUSEWHEEL) {
                if (e.wheel.y > 0) {
                    zoom += 0.1f;
                    if (zoom > 5.0f) zoom = 5.0f;
                } else if (e.wheel.y < 0) {
                    zoom -= 0.1f;
                    if (zoom < 0.1f) zoom = 0.1f;
                }
            }
        }

        set_color(renderer, BLACK_COLOR);
        SDL_RenderClear(renderer);

        draw_circle(renderer, &sun, SUN_COLOR, zoom);
        draw_rings(renderer, planet, RING_COLOR, num_planets, zoom);

        draw_planet(renderer, planet, num_planets, zoom);

        planet_speed(planet, zoom);
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    // Free all planets
    while (Last_planet != NULL) {
        remove_planet(&Last_planet, &num_planets);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
