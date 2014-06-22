#ifndef _ball_h_
#define _ball_h_

#include "dbg.h"
#include "base.h"
#include "ptexture.h"
#include "physics.h"
#include <SDL2/SDL.h>

// Header to represent Ball object

typedef struct Ball {
	int speedX;
	int speedY;
	int x;
	int y;
	PTexture *tex;
} Ball;

// initialization
extern Ball *createBall(SDL_Renderer *ren);

// updates the position of the ball and renders it
extern SIDE updateRenderBall(SDL_Renderer *ren, Ball *ball);

// resets the position for the given bal
extern void resetBall(Ball *ball, SIDE side);

// destruction
extern void destroyBall(Ball *ball);


#endif
