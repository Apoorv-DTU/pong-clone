#include "score.h"
#include "dbg.h"
#include <stdio.h>

TTF_Font *gFont;
SDL_Surface *lSurf;
SDL_Surface *rSurf;
SDL_Texture *lTex;
SDL_Texture *rTex;
int lScore;
int rScore;

extern bool initScore()
{
	gFont = TTF_OpenFont("../media/DigitalDreamSkew.ttf", 200);
	check(gFont, "Failed to open gFont: %s", TTF_GetError());
	lSurf = rSurf = NULL;
	lTex = rTex = NULL;
	lScore = rScore = 0;
	
	return true;
error:
	return false;
}

extern void updateScore(SIDE side, SDL_Renderer *ren, Ball *ball)
{
	check(ren != NULL, "SDL_Renderer is NULL");
	check(ball != NULL, "Ball is NULL");
	
	if(side == SIDE_LEFT) {
		rScore++;
		resetBall(ball, SIDE_LEFT);
	} else if(side == SIDE_RIGHT) {
		lScore++;
		resetBall(ball, SIDE_RIGHT);
	}
	SDL_Color fontColor = {0x27, 0x28, 0x22, 0xff};
	
	// convert scores to strings
	char lScText[5], rScText[5];
	sprintf(lScText, "%d", lScore);
	sprintf(rScText, "%d", rScore);
	
	// render the score for left player
	lSurf = TTF_RenderText_Blended(gFont, lScText, fontColor);
	check(lSurf != NULL, "Left score rendering error: %s", TTF_GetError());
		
	SDL_Rect renQuad = {(SCREEN_WIDTH/2) - 70,5, 40,60};
	lTex = SDL_CreateTextureFromSurface(ren, lSurf);
	SDL_RenderCopy(ren, lTex, NULL, &renQuad);
	
	// render the score the right player
	rSurf = TTF_RenderText_Blended(gFont, rScText, fontColor);
	check(rSurf != NULL, "Right score rendering error: %s", TTF_GetError());
	
	renQuad.x = SCREEN_WIDTH/2 + 10;
	rTex = SDL_CreateTextureFromSurface(ren, rSurf);
	SDL_RenderCopy(ren, rTex, NULL, &renQuad);
	
error:
	return;
}

extern void destroyScore()
{
	// Close the font and destroy the surface and texture
	TTF_CloseFont(gFont);
	gFont = NULL;
	
	TTF_CloseFont(gFont);
	gFont = NULL;
	
	SDL_FreeSurface(lSurf);
	lSurf = NULL;
	
	SDL_FreeSurface(rSurf);
	rSurf = NULL;
	
	SDL_DestroyTexture(rTex);
	rTex = NULL;
	
	SDL_DestroyTexture(lTex);
	lTex = NULL;
}
