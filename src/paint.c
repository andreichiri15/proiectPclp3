#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define CIRCLE_RADIUS 50
#define RECT_WIDTH 100
#define RECT_HEIGHT 50
#define DEFAULT_BRUSH_SIZE 1

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Event event;
int isDrawing = 0;
int prevMouseX, prevMouseY;
Uint8 red = 0, green = 0, blue = 0;
int brushSize = DEFAULT_BRUSH_SIZE; // Variable to store the brush size
float brushOpacity = 1.0;           // Variables for brush opacity

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

// Function to clean up SDL resources and exit the program
void cleanup()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void draw()
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, red, green, blue,
						   (Uint8)(255 * brushOpacity));

	// Draw lines with the current brush size
	SDL_RenderDrawLine(renderer, prevMouseX, prevMouseY, event.motion.x,
					   event.motion.y);

	// Draw additional lines for brush size
	int brushOffset = brushSize;
	for (int i = -brushOffset; i <= brushOffset; ++i) {
		for (int j = -brushOffset; j <= brushOffset; ++j) {
			if (i != 0 || j != 0) {
				SDL_RenderDrawLine(renderer, prevMouseX + i, prevMouseY + j,
								   event.motion.x + i, event.motion.y + j);
			}
		}
	}

	SDL_RenderPresent(renderer);
	prevMouseX = event.motion.x;
	prevMouseY = event.motion.y;
}

// Function to erase all colors and set the screen back to full white
void eraseScreen(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255,
						   255); // Set the render draw color to white
	SDL_RenderClear(renderer); // Clear the renderer with the current draw color
	SDL_RenderPresent(renderer); // Update the screen with the cleared renderer
}

void set_red()
{
	red = 255;
	green = 0;
	blue = 0;
}

void set_green()
{
	red = 0;
	green = 255;
	blue = 0;
}

void set_blue()
{
	red = 0;
	green = 0;
	blue = 255;
}
void set_yellow()
{
	red = 255;
	green = 255;
	blue = 0;
}

void set_white()
{
	red = 255;
	green = 255;
	blue = 255;
}

void set_black()
{
	red = 0;
	green = 0;
	blue = 0;
}

// Function to fill the screen with a certain color
void fill(SDL_Renderer *renderer, Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(
		renderer, red, green, blue,
		(Uint8)(255 * brushOpacity)); // Set the render draw color to white
	SDL_RenderClear(renderer); // Clear the renderer with the current draw color
	SDL_RenderPresent(renderer); // Update the screen with the cleared renderer
}

void drawCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius,
				int brushSize, Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, red, green, blue,
						   (Uint8)(255 * brushOpacity));

	int x = 0;
	int y = radius;
	int decision = 3 - 2 * radius;

	while (x <= y) {
		for (int i = -brushSize; i <= brushSize; ++i) {
			for (int j = -brushSize; j <= brushSize; ++j) {
				if (i != 0 || j != 0) {
					SDL_RenderDrawPoint(renderer, centerX + x + i,
										centerY + y + j);
					SDL_RenderDrawPoint(renderer, centerX - x + i,
										centerY + y + j);
					SDL_RenderDrawPoint(renderer, centerX + x + i,
										centerY - y + j);
					SDL_RenderDrawPoint(renderer, centerX - x + i,
										centerY - y + j);
					SDL_RenderDrawPoint(renderer, centerX + y + i,
										centerY + x + j);
					SDL_RenderDrawPoint(renderer, centerX - y + i,
										centerY + x + j);
					SDL_RenderDrawPoint(renderer, centerX + y + i,
										centerY - x + j);
					SDL_RenderDrawPoint(renderer, centerX - y + i,
										centerY - x + j);
				}
			}
		}

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

void drawRectangle(SDL_Renderer *renderer, int x, int y, int width, int height,
				   int brushSize, Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, red, green, blue,
						   (Uint8)(255 * brushOpacity));

	int thickness =
		brushSize * 2; // Set the initial thickness to the brush size

	// Draw multiple rectangles with increasing thickness
	while (thickness > 0) {
		SDL_Rect rect = {x - thickness, y - thickness, width + thickness * 2,
						 height + thickness * 2};
		SDL_RenderDrawRect(renderer, &rect);

		thickness--; // Reduce the thickness by 1 to create thicker margins
	}
}

int main(void)
{
	initialize();

	while (SDL_WaitEvent(&event) && event.type != SDL_QUIT) {
		switch (event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_e) {
				eraseScreen(renderer);
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
				draw();
			}
			break;
		}
	}

	cleanup();

	return 0;
}