#include <SDL2/SDL_image.h>
#include "ptexture.h"
#include "dbg.h"

extern PTexture *createPTexture()
{
	PTexture *texture = NULL;
	texture = calloc(sizeof(PTexture), 1);
	check_mem(texture);
	
	texture->width = 0;
	texture->height = 0;
	texture->texture = NULL;
	
	return texture;
error:
	return NULL;
}

extern void destroyPTexture(PTexture *texture)
{
	if(texture) {
		if(texture->texture) {
			SDL_DestroyTexture(texture->texture);
			texture->texture = NULL;
		}
		
		free(texture);
		texture = NULL;
	}
}

extern void loadFromFile(SDL_Renderer *ren, PTexture *tex, const char *path, Color *key)
{
	// destroy the current texture if any.
	if(tex->texture) {
		SDL_DestroyTexture(tex->texture);
	}	
	
	// temporary surface
	SDL_Surface *tmp_surf = NULL;
	tmp_surf = IMG_Load(path);
	
	SDL_SetColorKey(tmp_surf, SDL_RLEACCEL,
					SDL_MapRGB(tmp_surf->format, key->r, key->g, key->b));
	
	SDL_Texture	*texture = SDL_CreateTextureFromSurface(ren, tmp_surf);
	// set defaults
	tex->texture = texture;
	tex->width = tmp_surf->w;
	tex->height = tmp_surf->h;
	
	SDL_FreeSurface(tmp_surf);
}

extern void render(SDL_Renderer *ren, PTexture *texture, int x, int y)
{
	SDL_Rect rect = {x, y, texture->width, texture->height};
	SDL_RenderCopy(ren, texture->texture, NULL, &rect);
}
