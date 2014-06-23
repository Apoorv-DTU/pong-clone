#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <stdbool.h>
#include "dbg.h"
#include "score.h"
#include "bat.h"
#include "base.h"
#include "ball.h"
#include "physics.h"

// function to handle initialization
bool init();
// function to handle freeing
void shutDown();
// function to deflect the ball when it hits the bat
void deflectBall();

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

Bat lBat = {{5, SCREEN_WIDTH/2-100, 12, 60}, false, false};
Bat rBat = {{SCREEN_WIDTH-17, SCREEN_WIDTH/2-100, 12, 60}, false, false};
Ball *gBall = NULL;

// variable that controls pause of game
bool gPause = false;

bool init()
{
	 // initialize SDL IMG and TTF
	int rc = SDL_Init(SDL_INIT_VIDEO);
	check(rc >= 0, "Failed to init SDL: %s", SDL_GetError());
	
	rc = IMG_Init(IMG_INIT_PNG);
	check(rc == IMG_INIT_PNG, "Failed to init IMG: %s", IMG_GetError());
	
	check(TTF_Init() != -1, "Failed to initialize TTF: %s", TTF_GetError());
	
	// create a window
	gWindow = SDL_CreateWindow("Pong", 
				SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	check_mem(gWindow);
	
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	gBall = createBall(gRenderer);
	
	initScore();
	
	return true;
	
error:
	return false;
	
}

void shutDown()
{
	destroyBall(gBall);
	gBall = NULL;
	
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	
	destroyScore();
	
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void deflectBall()
{
	static bool hit = false;
	SDL_Rect ballRect = {gBall->x, gBall->y, gBall->tex->width,
						 gBall->tex->height};
	
	// check for collision
	if(checkCollision(&ballRect, &lBat.rect) || 
		checkCollision(&ballRect, &rBat.rect)) {
		if(!hit) {
			hit = true;
			// invert the x-speed of ball on collision
			gBall->speedX = -gBall->speedX;
		}
	} else {
		hit = false;
	}
}

int main(int argc, char *argv[])
{
	check(init(), "Failed to init");
	
	SDL_Event e;
	bool run = true;
	SIDE sideOut = SIDE_NONE;
	
	while(run) {
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT) {
				run = false;
			} else if(e.type == SDL_KEYDOWN) {
				switch(e.key.keysym.sym) {
					// Move the right bat with UP/DOWN arrows
					case SDLK_UP:
						rBat.movingUp = true;				
					break;
					
					case SDLK_DOWN:
						rBat.movingDown = true;			
					break;
					
					// Move the left bat with w/s
					case SDLK_w:
						lBat.movingUp = true;
					break;
					
					case SDLK_s:
						lBat.movingDown = true;
					break;
					
					default:
					break;
				}
			} else if (e.type == SDL_KEYUP) {
				switch(e.key.keysym.sym) {
					// stop moving the bat
					case SDLK_UP:
						rBat.movingUp = false;
					break;
					
					case SDLK_DOWN:
						rBat.movingDown = false;
					break;
					
					case SDLK_w:
						lBat.movingUp = false;
					break;
					
					case SDLK_s:
						lBat.movingDown = false;
					break;
					
					// toggle the pause with space
					case SDLK_SPACE:
						gPause = !gPause;
					break;
				}
			}
		}
		
		SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
		
		// render everything and change the positions
		if(!gPause) {
			SDL_RenderClear(gRenderer);
			deflectBall();
			renderBat(gRenderer, &lBat);
			renderBat(gRenderer, &rBat);
			sideOut = updateRenderBall(gRenderer, gBall);
			updateScore(sideOut, gRenderer, gBall);
			
		}
		SDL_RenderPresent(gRenderer);
	}
	
	// free everything	
	shutDown();
	
	return 0;
error:
	return -1;
}
