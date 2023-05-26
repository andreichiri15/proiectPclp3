// Copyright Dragos Banica, Andrei Chirimeaca
// PCLP3 2023

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#pragma once

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define CIRCLE_RADIUS 50
#define RECT_WIDTH 100
#define RECT_HEIGHT 50
#define DEFAULT_BRUSH_SIZE 1

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Event event;
extern int isDrawing;
extern int prevMouseX, prevMouseY;
extern Uint8 red, green, blue;
extern int brushSize;
extern float brushOpacity;

void initialize();

void handle_input();

void cleanup();

void draw();

void eraseScreen(SDL_Renderer *renderer);

void set_red();

void set_green();

void set_blue();

void set_yellow();

void set_white();

void set_black();

void fill(SDL_Renderer *renderer, Uint8 red, Uint8 green, Uint8 blue);

void drawCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius,
				int brushSize, Uint8 red, Uint8 green, Uint8 blue);

void drawRectangle(SDL_Renderer *renderer, int x, int y, int width, int height,
				   int brushSize, Uint8 red, Uint8 green, Uint8 blue);
