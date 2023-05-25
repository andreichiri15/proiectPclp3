#include <SDL2/SDL.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void fill(int x, int y, Uint32 targetColor, Uint32 fillColor,
		  SDL_Surface *surface)
{
	Uint32 *pixels = (Uint32 *)surface->pixels;
	int width = surface->w;
	int height = surface->h;

	// Check if the target pixel is out of bounds
	if (x < 0 || x >= width || y < 0 || y >= height) {
		return;
	}

	// Check if the target pixel already has the fill color
	if (pixels[y * width + x] == fillColor) {
		return;
	}

	// Perform a flood fill using a stack-based approach
	Uint32 stackColor = pixels[y * width + x];
	int stackSize = 0;
	int stackCapacity = width * height;
	SDL_Point *stack = (SDL_Point *)malloc(stackCapacity * sizeof(SDL_Point));

	if (stack == NULL) {
		return;
	}

	// Push the starting point to the stack
	stack[stackSize++] = (SDL_Point){x, y};

	while (stackSize > 0) {
		// Pop a point from the stack
		SDL_Point current = stack[--stackSize];

		// Check if the current point is within bounds
		if (current.x >= 0 && current.x < width && current.y >= 0 &&
			current.y < height) {
			// Check if the current point has the target color
			if (pixels[current.y * width + current.x] == targetColor) {
				// Set the fill color for the current point
				pixels[current.y * width + current.x] = fillColor;

				// Push adjacent points to the stack
				stack[stackSize++] =
					(SDL_Point){current.x - 1, current.y}; // Left
				stack[stackSize++] =
					(SDL_Point){current.x + 1, current.y}; // Right
				stack[stackSize++] =
					(SDL_Point){current.x, current.y - 1}; // Up
				stack[stackSize++] =
					(SDL_Point){current.x, current.y + 1}; // Down
			}
		}
	}

	free(stack);
}

// Function to erase all colors and set the screen back to full white
void eraseScreen(SDL_Renderer *renderer, int windowWidth, int windowHeight)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255,
						   255); // Set the render draw color to white
	SDL_RenderClear(renderer); // Clear the renderer with the current draw color
	SDL_RenderPresent(renderer); // Update the screen with the cleared renderer
}

int main(void)
{
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Event event;
	int isDrawing = 0;
	int prevMouseX, prevMouseY;
	Uint8 red = 0, green = 0, blue = 0;

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
				eraseScreen(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
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
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				if (SDL_GetModState() & KMOD_LSHIFT) {
					// Perform fill at the clicked position
					fill(event.button.x, event.button.y, 0xFFFFFFFF, 0x000000FF,
						 SDL_GetWindowSurface(window));
					SDL_UpdateWindowSurface(window);
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
                SDL_RenderDrawLine(renderer, prevMouseX, prevMouseY, event.motion.x, event.motion.y);
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