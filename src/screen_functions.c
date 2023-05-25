#include "header.h"

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
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(
		renderer, red, green, blue,
		(Uint8)(255 * brushOpacity)); // Set the render draw color to white
	SDL_RenderClear(renderer); // Clear the renderer with the current draw color
	SDL_RenderPresent(renderer); // Update the screen with the cleared renderer
}