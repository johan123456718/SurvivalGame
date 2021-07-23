#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>

#include "init_quit.h"
#include "video.h"
#include "player.h"

void initGame()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
	{
		printf("error initializing SDL: %s\n", SDL_GetError());
		return 1;
	}
	srand(time(NULL));
	if (TTF_Init() != 0)
	{
		printf("error: %s\n", SDL_GetError());
		return 1;
	}

	initVideo();
}

void quitGame()
{
	SDL_DestroyTexture(video.player1Texture);
	SDL_DestroyTexture(video.player2Texture);
	SDL_DestroyTexture(video.enemyTexture);
	SDL_DestroyTexture(video.bgTexture);
	SDL_DestroyTexture(video.bulletTexture);
	SDL_DestroyTexture(video.menuStartTexture);
	SDL_DestroyTexture(video.menuHoverPlayTexture);
	SDL_DestroyTexture(video.menuHoverQuitTexture);
	SDL_DestroyTexture(video.menuHoverIPTexture);
	SDL_DestroyTexture(video.HUDBothAlive);
	SDL_DestroyTexture(video.HUDP1Dead);
	SDL_DestroyTexture(video.HUDP2Dead);
	SDL_DestroyRenderer(video.rend);
	SDL_DestroyWindow(video.win);
	TTF_CloseFont(text.font);
	TTF_Quit();
	SDL_Quit();
}