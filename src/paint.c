#include "header.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Event event;
int isDrawing = 0;
int prevMouseX, prevMouseY;
Uint8 red = 0, green = 0, blue = 0;
int brushSize = DEFAULT_BRUSH_SIZE; // Variable to store the brush size
float brushOpacity = 1.0;           // Variables for brush opacity

int main(void)
{
	initialize(); // Initialize SDL and create the window and renderer

	handle_input(); // Handles user's input

	cleanup(); // Free all memory

	return 0;
}