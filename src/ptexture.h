#ifndef _ptexture_h_
#define _ptexture_h_

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "base.h"

// A thin wrapper on SDL_Texture to handle initialization, loading etc. 
// Note: PTexture stands for PongTexture just int case.

typedef struct PTexture {
	SDL_Texture *texture;
	int width;
	int height;
} PTexture;

// handles the init.
extern PTexture *createPTexture();

// handles the destruction
extern void destroyPTexture(PTexture *texture); 

// handles loading
extern void loadFromFile(SDL_Renderer *ren, PTexture *tex, const char *path, Color *key);

// handles rendering
extern void render(SDL_Renderer *ren, PTexture *texture, int x, int y);

#endif
