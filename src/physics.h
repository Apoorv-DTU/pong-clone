#ifndef _physics_h_
#define _physics_h_

#include "dbg.h"
#include <stdbool.h>
#include <SDL2/SDL.h>

// header for physics functions

extern bool checkCollision(SDL_Rect *a, SDL_Rect *b);

typedef enum {SIDE_LEFT,
	  SIDE_RIGHT,
	  SIDE_TOP,
	  SIDE_BOTTOM,
	  SIDE_NONE} SIDE;

#endif
