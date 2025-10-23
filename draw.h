#ifndef DRAW_H
#define DRAW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_stdinc.h>

#include "fsm.h"

// Drawing function prototype
void c_draw(SDL_Renderer* ren, const FSM* fsm);

// Cell prototypes
//extern Sint16 cell_AA_x[4];
//extern Sint16 cell_AA_y[4];

#endif
