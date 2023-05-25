#include "header.h"

// Functions to set the drawing color
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

void draw()
{
	// Change the opacity if needed
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

	// Keep the mouse click positions
	SDL_RenderPresent(renderer);
	prevMouseX = event.motion.x;
	prevMouseY = event.motion.y;
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

	// Set the initial thickness to the brush size
	int thickness = brushSize * 2;

	// Draw multiple rectangles with increasing thickness
	while (thickness > 0) {
		SDL_Rect rect = {x - thickness, y - thickness, width + thickness * 2,
						 height + thickness * 2};
		SDL_RenderDrawRect(renderer, &rect);

		thickness--; // Reduce the thickness by 1 to create thicker margins
	}
}