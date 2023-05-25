#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define DEFAULT_BRUSH_SIZE 1

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

// Function to erase all colors and set the screen back to full white
void eraseScreen(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255,
						   255); // Set the render draw color to white
	SDL_RenderClear(renderer); // Clear the renderer with the current draw color
	SDL_RenderPresent(renderer); // Update the screen with the cleared renderer
}

// Function to fill the screen with a certain color
void fill(SDL_Renderer *renderer, Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetRenderDrawColor(renderer, red, green, blue,
						   255); // Set the render draw color to white
	SDL_RenderClear(renderer); // Clear the renderer with the current draw color
	SDL_RenderPresent(renderer); // Update the screen with the cleared renderer
}

void drawCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius,
				Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetRenderDrawColor(renderer, red, green, blue, 255);

	int x = 0;
	int y = radius;
	int decision = 3 - 2 * radius;

	while (x <= y) {
		SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
		SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
		SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
		SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
		SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
		SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);
		SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
		SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);

		x++;

		if (decision < 0) {
			decision += 4 * x + 6;
		} else {
			decision += 4 * (x - y) + 10;
			y--;
		}
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0,
						   255); // Reset the renderer color to black
}

int main(void)
{
	SDL_Event event;
	int isDrawing = 0;
	int prevMouseX, prevMouseY;
	Uint8 red = 0, green = 0, blue = 0;
	int brushSize = DEFAULT_BRUSH_SIZE; // Variable to store the brush size

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Paint Program", SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
							  WINDOW_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	while (SDL_WaitEvent(&event) && event.type != SDL_QUIT) {
		switch (event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_e) {
				eraseScreen(renderer);
			} else if (event.key.keysym.sym == SDLK_r) {
				red = 255;
				green = 0;
				blue = 0;
			} else if (event.key.keysym.sym == SDLK_g) {
				red = 0;
				green = 255;
				blue = 0;
			} else if (event.key.keysym.sym == SDLK_b) {
				red = 0;
				green = 0;
				blue = 255;
			} else if (event.key.keysym.sym == SDLK_y) {
				red = 255;
				green = 255;
				blue = 0;
			} else if (event.key.keysym.sym == SDLK_w) {
				red = 255;
				green = 255;
				blue = 255;
			} else if (event.key.keysym.sym == SDLK_1) {
				brushSize = 1; // Set brush size to 1
			} else if (event.key.keysym.sym == SDLK_2) {
				brushSize = 2; // Set brush size to 2
			} else if (event.key.keysym.sym == SDLK_3) {
				brushSize = 3; // Set brush size to 3
			} else if (event.key.keysym.sym == SDLK_4) {
				brushSize = 4; // Set brush size to 4
			} else if (event.key.keysym.sym == SDLK_c) {
				// Get the mouse position
				int mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);

				// Draw a circle at the mouse position
				drawCircle(renderer, mouseX, mouseY, 50, red, green, blue);
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
				SDL_SetRenderDrawColor(renderer, red, green, blue, 255);

				// Draw lines with the current brush size
				SDL_RenderDrawLine(renderer, prevMouseX, prevMouseY,
								   event.motion.x, event.motion.y);

				// Draw additional lines for brush size
				int brushOffset = brushSize;
				for (int i = -brushOffset; i <= brushOffset; ++i) {
					for (int j = -brushOffset; j <= brushOffset; ++j) {
						if (i != 0 || j != 0) {
							SDL_RenderDrawLine(
								renderer, prevMouseX + i, prevMouseY + j,
								event.motion.x + i, event.motion.y + j);
						}
					}
				}

				SDL_RenderPresent(renderer);
				prevMouseX = event.motion.x;
				prevMouseY = event.motion.y;
			}
			break;
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}