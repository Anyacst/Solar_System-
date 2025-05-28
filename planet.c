#include "main.h"

static uint32_t planet_colors[5] = {
    0xFF5733,  // Mars-like red
    0x1E90FF,  // Earth blue
    0xADFF2F,  // Venus green-yellow
    0xDA70D6,  // Purple
    0xFFD700   // Mercury gold
};

uint32_t get_planet_color(int index) {
    return planet_colors[index % 5];
}

void set_color(SDL_Renderer *renderer, uint32_t color) {
    uint8_t r = (color >> 16) & 0xFF;
    uint8_t g = (color >> 8) & 0xFF;
    uint8_t b = color & 0xFF;
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
}

void draw_circle(SDL_Renderer *renderer, struct Planet *planet, uint32_t color, float zoom) {
    int radiuszoom = (int)(planet->radius * zoom);
    int radius = radiuszoom * radiuszoom;
    set_color(renderer, color);

    for (int y = planet->y - radiuszoom; y < planet->y + radiuszoom; y++) {
        for (int x = planet->x - radiuszoom; x < planet->x + radiuszoom; x++) {
            int dx = x - planet->x;
            int dy = y - planet->y;
            if ((dx * dx + dy * dy) <= radius) {
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}

void draw_rings(SDL_Renderer *renderer, struct Planet *planet, uint32_t color, int num, float zoom) {
    if (!planet || num <= 0) return;
    set_color(renderer, color);

    struct Planet *current = planet;
    for (int i = 0; i < num && current != NULL; i++) {
        int a = (int)(current->a * zoom);
        int b = (int)(current->b * zoom);
        for (double theta = 0; theta <= 2 * M_PI; theta += 0.01) {
            int ringx = CENTER_X + (int)(a * cos(theta));
            int ringy = CENTER_Y + (int)(b * sin(theta));
            SDL_RenderDrawPoint(renderer, ringx, ringy);
        }
        current = current->next;
    }
}

void planet_speed(struct Planet *planet, float zoom) {
    if (!planet) return;
    struct Planet *current = planet;
    while (current != NULL) {
        current->theta += current->speed * 0.001;
        current->x = CENTER_X + (int)(current->a * zoom * cos(current->theta));
        current->y = CENTER_Y + (int)(current->b * zoom * sin(current->theta));
        current = current->next;
    }
}

void draw_planet(SDL_Renderer *renderer, struct Planet *planet, int num, float zoom) {
    if (!planet || num <= 0) return;

    struct Planet *current = planet;
    for (int i = 0; i < num && current != NULL; i++) {
        draw_circle(renderer, current, current->color, zoom);
        current = current->next;
    }
}


void add_planet(struct Planet **planet, struct Planet **Last_planet, int *num) {
    struct Planet *temp = (struct Planet *)malloc(sizeof(struct Planet));
    if (temp == NULL) {
        fprintf(stderr, "Memory is not allocated for new planet. Sorry...!");
        exit(1);
    }

    int a = 190 + (*num) * 90;
    int b = 110 + (*num) * 60;

    temp->x = CENTER_X + (int)(a * cos(0));
    temp->y = CENTER_Y + (int)(b * sin(0));
    temp->a = a;
    temp->b = b;
    temp->radius = rand() % 21 + 20;
    temp->theta = 0;
    temp->speed = 1 + rand() % 8;
    temp->color = get_planet_color(*num);
    temp->next = NULL;
    temp->prev = NULL;
    temp->max_speed = temp->speed + 5;
    temp->min_speed = (temp->speed - 3 > 1) ? (temp->speed - 3) : 1;

    if (*planet == NULL) {
        *planet = temp;
    } else {
        (*Last_planet)->next = temp;
        temp->prev = *Last_planet;
    }

    *Last_planet = temp;
    (*num)++;
}

void remove_planet(struct Planet **Last_Planet, int *num) {
    if (*Last_Planet == NULL) {
        printf("No planet to remove...!\n");
        return;
    }

    struct Planet *to_remove = *Last_Planet;
    if (to_remove->prev != NULL) {
        *Last_Planet = to_remove->prev;
        (*Last_Planet)->next = NULL;
    } else {
        *Last_Planet = NULL;
    }

    free(to_remove);
    (*num)--;
}

void delete_planet_by_mouse(struct Planet **head, struct Planet **last, struct Planet *current, int *num) {
    if (!current || !*head || *num <= 0) return;

    // Unlink from list
    if (current->prev) current->prev->next = current->next;
    if (current->next) current->next->prev = current->prev;

    // Update head and last
    if (current == *head) {
        *head = current->next;
    }
    if (current == *last) {
        *last = current->prev;
    }

    // Clear tail data (optional, but clean)
    memset(current->tail, 0, sizeof(current->tail));
    current->tail_index = 0;

    free(current);
    (*num)--;
}


int isinsidetheplanet(int mx, int my, struct Planet *temp, float zoom) {
    int dx = mx - temp->x;
    int dy = my - temp->y;
    int radius = (int)(temp->radius * zoom);
    return (dx * dx + dy * dy <= radius * radius);
}

void increase_speed_of_planet(struct Planet *planet) {
    struct Planet *temp = planet;
    while(temp != NULL) {
        if(temp->speed < temp->max_speed) {
            temp->speed += 0.5;
        }
        temp = temp->next;
    }
}

void decrease_speed_of_planet(struct Planet *planet) {
    struct Planet *temp = planet;
    while(temp != NULL) {
        if(temp->speed > temp->min_speed) {
            temp->speed -= 0.5;
        }
        temp = temp->next;
    }
}

void draw_tail(SDL_Renderer *renderer, struct Planet *planet, float zoom) {
    if (!planet) return;

    set_color(renderer, planet->color);

    for (int i = 0; i < TAIL_LENGTH - 1; i++) {
        int idx1 = (planet->tail_index + i) % TAIL_LENGTH;
        int idx2 = (planet->tail_index + i + 1) % TAIL_LENGTH;

        SDL_RenderDrawLine(renderer,
            CENTER_X + planet->tail[idx1].x * zoom,
            CENTER_Y + planet->tail[idx1].y * zoom,
            CENTER_X + planet->tail[idx2].x * zoom,
            CENTER_Y + planet->tail[idx2].y * zoom);
    }
}

