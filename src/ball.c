#include "ball.h"
#include "base.h"
#include "physics.h"

extern Ball *createBall(SDL_Renderer *ren)
{
	Ball *new = NULL;
	new = calloc(sizeof(Ball), 1);
	check_mem(new);
	new->speedX = 2;
	new->speedY = 2;
	new->x = SCREEN_WIDTH / 2;
	new->y = 0;
	new->tex = createPTexture();
	Color key = {0xff, 0xff, 0xff};
	loadFromFile(ren, new->tex, "../media/ball.png", &key);
	
	return new;
error:
	return NULL;
}

extern void resetBall(Ball *ball, SIDE side) {
	if(side == SIDE_LEFT) {
		ball->speedX = -BALL_SPEED;
	} else if(side == SIDE_RIGHT) {
		ball->speedX = BALL_SPEED;
	}
	ball->speedY = BALL_SPEED;
	ball->x = SCREEN_WIDTH / 2;
	ball->y = 0;
}

extern SIDE updateRenderBall(SDL_Renderer *ren, Ball *ball)
{	
	// side through which the ball went out
	SIDE out = SIDE_NONE;
	int newX = ball->x + ball->speedX;
	int newY = ball->y + ball->speedY;
	
	// check if ball is out of bounds
	if(newX >= SCREEN_WIDTH) {
		out = SIDE_RIGHT;
	} else if(newX <= 0) {
		out = SIDE_LEFT;
	}
	if(newY >= SCREEN_HEIGHT || newY <= 0) {
		ball->speedY = -ball->speedY;
	}

	// move the ball
	ball->x += ball->speedX;
	ball->y += ball->speedY;
	
	// render it
	SDL_Rect renQuad = {ball->x, ball->y, ball->tex->width, ball->tex->height};
	SDL_RenderCopy(ren, ball->tex->texture, NULL, &renQuad);
	
	return out;
}

extern void destroyBall(Ball *ball)
{
	if(ball) {
		if(ball->tex)
			destroyPTexture(ball->tex);
		free(ball);
	}
}
