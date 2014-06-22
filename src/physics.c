#include "physics.h"

// checks if rect a collides with rect b
extern bool checkCollision(SDL_Rect *a, SDL_Rect *b)
{
	int a_left = a->x, b_left = b->x;
	int a_right = a->x + a->w, b_right = b->x + b->w;
	int a_top = a->y, b_top = b->y;
	int a_bottom = a->y + a->h, b_bottom = b->y + b->h;
	
	if(a_right >= b_left && a_left <= b_right 
		&& a_bottom >= b_top && a_top <= b_bottom) {
			return true;
	} else {
		return false;
	}
}
