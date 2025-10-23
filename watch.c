#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "fsm.h"
#include "draw.h"
#include "sound.h"

#define TARGET_FPS 100
#define NANOSECONDS_PER_SECOND 1000000000
#define TARGET_FRAME_NANOSECONDS (NANOSECONDS_PER_SECOND / TARGET_FPS)

int main()
{
	// Initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
	{
		printf("SDL initialisation error\n");
		return 1;
	}

	// Create a window
	SDL_Window* win = SDL_CreateWindow("Watch2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 1000, 0);
	if (!win)
	{
		printf("Window creation error\n");
		SDL_Quit();
		return 1;
	}

	// Create a renderer
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (!ren)
	{
		printf("Render creation error\n");
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}

	// Black out the background
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderPresent(ren);

	// Set the background texture
	SDL_Surface* loaded_surface = NULL;
	SDL_Texture* background_texture = NULL;
	loaded_surface = IMG_Load("assets/face2.png");
	background_texture = SDL_CreateTextureFromSurface(ren, loaded_surface);
	SDL_Rect screen_rect = {0, 0, 1000, 1000};
	SDL_RenderCopy(ren, background_texture, NULL, &screen_rect);

	// FPS code
	struct timespec start_time, end_time;
	long elapsed_nanoseconds;
	long sleep_nanoseconds;

	bool running = true;
	SDL_Event e;
	int tick = 1;

	// Create the clock
	FSM clock;
	init_c(&clock);
	char input = 'x';

	while(running)
	{
		while(SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				running = false;
			}
			else if (e.type == SDL_KEYUP)
			{
				switch (e.key.keysym.sym)
				{
					case SDLK_q:
						running = false;
						break;
					case SDLK_m:
						input = 'm';
						beep(3440.0, 50);
						break;
					case SDLK_s:
						input = 's';
						beep(3440.0, 50);
						break;
					case SDLK_r:
						input = 'r';
						beep(3440.0, 50);
						break;
					default:
						break;
				}
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					printf("Click at: (%d, %d)\n", e.button.x, e.button.y);
					if (e.button.x > 80 && e.button.x < 103 && e.button.y > 660 && e.button.y < 681)
					{
						input = 'm';
						beep(3440.0, 50);
						break;
					}
					if (e.button.x > 894 && e.button.x < 915 && e.button.y > 660 && e.button.y < 680)
					{
						input = 's';
						beep(3440.0, 50);
						break;
					}
					if (e.button.x > 85 && e.button.x < 104 && e.button.y > 319 && e.button.y < 336)
					{
						input = 'r';
						beep(3440.0, 50);
						break;
					}
				}
			}
		}

	clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);

	// Workload goes here
	// Give the tick to the tick_c function and print the FSM
	tick_c(&clock, tick, input);

	// Clear the input
	input = 'x';

	// Update the screen
	c_draw(ren, &clock);

	tick++;

	// Workload ends here

	clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
	elapsed_nanoseconds = (end_time.tv_sec - start_time.tv_sec) * NANOSECONDS_PER_SECOND + (end_time.tv_nsec - start_time.tv_nsec);
	sleep_nanoseconds = TARGET_FRAME_NANOSECONDS - elapsed_nanoseconds;

	if (sleep_nanoseconds > 0)
	{
		usleep(sleep_nanoseconds / 1000);
	}

	}

return 0;
}
