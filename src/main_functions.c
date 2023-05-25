#include "header.h"

// Function to initialize SDL and create the window and renderer
void initialize()
{
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Paint Program", SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
							  WINDOW_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void handle_input() {
	while (SDL_WaitEvent(&event) && event.type != SDL_QUIT) {
		switch (event.type) {
		case SDL_KEYDOWN:
			// Handle keyboard events
			if (event.key.keysym.sym == SDLK_e) {
				eraseScreen(renderer); // "Erase" the screen with white color
			} else if (event.key.keysym.sym == SDLK_r) {
				set_red();
			} else if (event.key.keysym.sym == SDLK_g) {
				set_green();
			} else if (event.key.keysym.sym == SDLK_b) {
				set_blue();
			} else if (event.key.keysym.sym == SDLK_y) {
				set_yellow();
			} else if (event.key.keysym.sym == SDLK_w) {
				set_white();
			} else if (event.key.keysym.sym == SDLK_n) {
				set_black();
			} else if (event.key.keysym.sym == SDLK_1) {
				brushSize = 1; // Set brush size to 1
			} else if (event.key.keysym.sym == SDLK_2) {
				brushSize = 2; // Set brush size to 2
			} else if (event.key.keysym.sym == SDLK_3) {
				brushSize = 3; // Set brush size to 3
			} else if (event.key.keysym.sym == SDLK_4) {
				brushSize = 4; // Set brush size to 4
			} else if (event.key.keysym.sym == SDLK_6) {
				brushOpacity = 0.2;
			} else if (event.key.keysym.sym == SDLK_7) {
				brushOpacity = 0.4;
			} else if (event.key.keysym.sym == SDLK_8) {
				brushOpacity = 0.7;
			} else if (event.key.keysym.sym == SDLK_9) {
				brushOpacity = 1.0;
			} else if (event.key.keysym.sym == SDLK_c) {
				// Get the mouse position
				int mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);

				// Draw a circle at the mouse position
				drawCircle(renderer, mouseX, mouseY, CIRCLE_RADIUS, brushSize,
						   red, green, blue);
				SDL_RenderPresent(renderer);
			} else if (event.key.keysym.sym == SDLK_d) {
				// Get the mouse position
				int mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);

				// Draw a rectangle at the mouse position
				drawRectangle(renderer, mouseX, mouseY, RECT_WIDTH, RECT_HEIGHT,
							  brushSize, red, green, blue);
				SDL_RenderPresent(renderer);
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				if (SDL_GetModState() & KMOD_LSHIFT) {
					// Perform fill at the clicked position
					fill(renderer, red, green, blue);
				} else {
					isDrawing = 1;
					prevMouseX = event.button.x;
					prevMouseY = event.button.y;
				}
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) {
				isDrawing = 0;
			}
			break;
		case SDL_MOUSEMOTION:
			if (isDrawing) {
				// Draw a line from the previous mouse position to the current mouse position
				draw();
			}
			break;
		}
	}
}

// Function to clean up SDL resources and exit the program
void cleanup()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}