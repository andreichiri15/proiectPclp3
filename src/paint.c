#include <SDL2/SDL.h>
#include <stdlib.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(void)
{
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Event event;
	int isDrawing = 0;

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
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				isDrawing = 1;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) {
				isDrawing = 0;
			}
			break;
		case SDL_MOUSEMOTION:
			if (isDrawing) {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderDrawPoint(renderer, event.motion.x, event.motion.y);
				SDL_RenderPresent(renderer);
			}
            
			break;
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}