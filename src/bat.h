#ifndef _bat_h_
#define _bat_h_
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "ptexture.h"
#include "base.h"

// header for bat object

typedef struct Bat {
	SDL_Rect rect;
	bool movingUp;
	bool movingDown;
} Bat;

// correct the bat position if it goes out of bounds
inline void correctBatPos(Bat *bat)
{
	if(bat->rect.y + bat->rect.h > SCREEN_HEIGHT-3) {
		bat->rect.y = SCREEN_HEIGHT-bat->rect.h-3;
		bat->movingDown = false;
	} else if(bat->rect.y < 3) {
		bat->rect.y = 3;
		bat->movingUp = false;
	}
}

// render the bat
inline void renderBat(SDL_Renderer *ren, Bat *bat)
{
	// move the bat
	if(bat->movingUp) {
		bat->rect.y -= BAT_SPEED;
		bat->movingDown = false;
	} else if(bat->movingDown) {
		bat->rect.y += BAT_SPEED;
		bat->movingUp = false;
	}
	// correct the pos if it went out
	correctBatPos(bat);
	
	// render it
	SDL_Rect rect = {bat->rect.x, bat->rect.y, bat->rect.w, bat->rect.h};
	SDL_SetRenderDrawColor(ren, 0x27, 0x28, 0x22, 0xff);
	SDL_RenderFillRect(ren, &rect);
}

#endif
