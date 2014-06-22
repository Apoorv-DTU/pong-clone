#ifndef _score_h_
#define _score_h_

#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#include "physics.h"
#include "ball.h"
#include "base.h"

// Initialization
extern bool initScore();

// Updates the score and renders it taking the SIDE through which the ball went out
extern void updateScore(SIDE side, SDL_Renderer *ren, Ball *ball);

// Destruction
extern void destroyScore();

#endif
