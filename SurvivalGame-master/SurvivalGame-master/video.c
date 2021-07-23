#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string.h>
#include <stdlib.h>
#include "video.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"

void initTextures();
SDL_Texture* loadTexture(char path[]);

void initVideo()
{
	video.win = SDL_CreateWindow("Spacemen vs Gnomes",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if (!video.win)
	{
		printf("error creating window: %s\n", SDL_GetError());
		SDL_Quit();

	}

	Uint32 render_flags = SDL_RENDERER_ACCELERATED;
	video.rend = SDL_CreateRenderer(video.win, -1, render_flags);
	if (!video.rend)
	{
		printf("error creating renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(video.win);
		SDL_Quit();

	}

	initTextures();
	text.font = TTF_OpenFont("fonts/arial.ttf", 100);
	SDL_Color color = { 255, 255, 255 };
	text.color = color;

}

void RenderBackground()
{
	SDL_RenderCopy(video.rend, video.bgTexture, NULL, NULL);
}

void RenderHUD(int player1_HP, int player2_HP, int score)
{
	SDL_Rect HUDRect;
	HUDRect.h = 70;
	HUDRect.w = 500;
	HUDRect.x = 400;
	HUDRect.y = 0;

	if (player1_HP == 0 && player2_HP > 0)
	{
		SDL_RenderCopy(video.rend, video.HUDP1Dead, NULL, &HUDRect);
	}
	else if (player1_HP > 0 && player2_HP == 0)
	{
		SDL_RenderCopy(video.rend, video.HUDP2Dead, NULL, &HUDRect);
	}
	else
	{
		SDL_RenderCopy(video.rend, video.HUDBothAlive, NULL, &HUDRect);
	}

	DisplayText(player1_HP, player2_HP, score);
}

void RenderPlayers(Player players[])
{
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		if (i == 0)
		{
			SDL_RenderCopyEx(video.rend, video.player1Texture, &players[i].SpriteClips[players[i].frame], &players[i].dest, players[i].angle, NULL, players[i].flip);
		}
		else if (i == 1)
		{
			SDL_RenderCopyEx(video.rend, video.player2Texture, &players[i].SpriteClips[players[i].frame], &players[i].dest, players[i].angle, NULL, players[i].flip);
		}
	}
}
void RenderEnemies(Enemy enemies[], int nrOfEnemies)
{
	for (int i = 0; i < nrOfEnemies; i++)
	{
		if (enemies[i].isAlive == true)
		{
			SDL_RenderCopyEx(video.rend, video.enemyTexture, &enemies[i].SpriteClips[enemies[i].frame], &enemies[i].dest, 0, NULL, enemies[i].flip);
		}
	}
}
void RenderBullets(Bullet bullets[], int nrOfBullets)
{
	for (int i = 0; i < nrOfBullets; i++)
	{
		if (bullets[i].active == true)
		{
			SDL_RenderCopy(video.rend, video.bulletTexture, NULL, &bullets[i].dest);
		}
	}
}
void RenderMenuToWindow(int menustate)
{
	if (menustate == 1)
	{
		SDL_RenderClear(video.rend);
		SDL_RenderCopy(video.rend, video.menuStartTexture, NULL, NULL);
		SDL_RenderPresent(video.rend);
		SDL_Delay(1500 / 60);
	}
	else if (menustate == 2)
	{
		SDL_RenderClear(video.rend);
		SDL_RenderCopy(video.rend, video.menuHoverPlayTexture, NULL, NULL);
		SDL_RenderPresent(video.rend);
		SDL_Delay(1500 / 60);
	}
	else if (menustate == 3)
	{
		SDL_RenderClear(video.rend);
		SDL_RenderCopy(video.rend, video.menuHoverIPTexture, NULL, NULL);
		SDL_RenderPresent(video.rend);
		SDL_Delay(1500 / 60);
	}
	else if (menustate == 4)
	{
		SDL_RenderClear(video.rend);
		SDL_RenderCopy(video.rend, video.menuHoverQuitTexture, NULL, NULL);
		SDL_RenderPresent(video.rend);
		SDL_Delay(1500 / 60);
	}
	else
	{
		printf("%d is an invalid menustate so this menustates texture could therefore not be rendered.", menustate);
	}
}
void RenderIP_Menu(char IpText[])
{
	text.TextSurface = TTF_RenderText_Solid(text.font, IpText, text.color);
	text.IPaddress_texture = SDL_CreateTextureFromSurface(video.rend, text.TextSurface);
	SDL_FreeSurface(text.TextSurface);
	text.IPaddress_dest.h = 50;
	text.IPaddress_dest.w = 30 * strlen(IpText);
	text.IPaddress_dest.x = WINDOW_WIDTH / 2 - text.IPaddress_dest.w / 2;
	text.IPaddress_dest.y = WINDOW_HEIGHT / 2 - text.IPaddress_dest.h / 2;

	SDL_RenderClear(video.rend);
	SDL_RenderCopy(video.rend, video.enterIpMenuTexture, NULL, NULL);
	SDL_RenderCopy(video.rend, text.IPaddress_texture, NULL, &text.IPaddress_dest);
	SDL_RenderPresent(video.rend);
	SDL_Delay(1500 / 60);
}
void DisplayText(int player1_hp, int player2_hp, int score)
{
	char hp_str[2];
	char hp2_str[2];
	char score_str[10];
	itoa(player1_hp, hp_str, 10);
	itoa(player2_hp, hp2_str, 10);
	itoa(score, score_str, 10);

	text.TextSurface = TTF_RenderText_Solid(text.font, hp_str, text.color);
	text.hp1_texture = SDL_CreateTextureFromSurface(video.rend, text.TextSurface);
	SDL_FreeSurface(text.TextSurface);
	text.hp1_dest.h = 30;
	text.hp1_dest.w = 30;
	text.hp1_dest.x = 825;
	text.hp1_dest.y = 20;
	SDL_RenderCopy(video.rend, text.hp1_texture, NULL, &text.hp1_dest);
	SDL_DestroyTexture(text.hp1_texture);

	text.TextSurface = TTF_RenderText_Solid(text.font, hp2_str, text.color);
	text.hp1_texture = SDL_CreateTextureFromSurface(video.rend, text.TextSurface);
	SDL_FreeSurface(text.TextSurface);
	text.hp2_dest.h = 30;
	text.hp2_dest.w = 30;
	text.hp2_dest.x = 440;
	text.hp2_dest.y = 20;
	SDL_RenderCopy(video.rend, text.hp1_texture, NULL, &text.hp2_dest);
	SDL_DestroyTexture(text.hp1_texture);

	text.TextSurface = TTF_RenderText_Solid(text.font, score_str, text.color);
	text.score_texture = SDL_CreateTextureFromSurface(video.rend, text.TextSurface);
	SDL_FreeSurface(text.TextSurface);
	text.score_dest.h = 30;
	text.score_dest.w = 15 * strlen(score_str);
	text.score_dest.x = (WINDOW_WIDTH / 2 - 15 / 2) + 10;
	text.score_dest.y = 20;
	SDL_RenderCopy(video.rend, text.score_texture, NULL, &text.score_dest);
	SDL_DestroyTexture(text.score_texture);
}

void gameOverMenuState(int score)
{
	char score_str[10];
	itoa(score, score_str, 10);

	text.TextSurface = TTF_RenderText_Solid(text.font, score_str, text.color);
	text.score_texture = SDL_CreateTextureFromSurface(video.rend, text.TextSurface);
	SDL_FreeSurface(text.TextSurface);
	text.score_dest.h = 50;
	text.score_dest.w = 75;
	text.score_dest.x = WINDOW_WIDTH / 2 - text.score_dest.w / 2;
	text.score_dest.y = WINDOW_HEIGHT / 2 - text.score_dest.h / 2;

	SDL_RenderClear(video.rend);
	SDL_RenderCopy(video.rend, video.gameOverMenuTexture, NULL, NULL);
	SDL_RenderCopy(video.rend, text.score_texture, NULL, &text.score_dest);
	SDL_RenderPresent(video.rend);
	SDL_DestroyTexture(text.score_texture);
}
/***************** [Local functions for video.c] *****************/

void initTextures()
{
	video.bgTexture = loadTexture("images/grass.png");
	video.player1Texture = loadTexture("images/Player1SPACEMAN.png");
	video.player2Texture = loadTexture("images/Player2SPACEMAN.png");
	video.enemyTexture = loadTexture("images/gnome.png");
	video.bulletTexture = loadTexture("images/laser2.png");
	video.menuStartTexture = loadTexture("images/StartMenuSprite.jpg");
	video.menuHoverPlayTexture = loadTexture("images/HoverPlayMenuSprite.jpg");
	video.menuHoverQuitTexture = loadTexture("images/HoverQuitMenuSprite.jpg");
	video.menuHoverIPTexture = loadTexture("images/HoverEnterIPMenuSprite.jpg");
	video.enterIpMenuTexture = loadTexture("images/EnterIPMenu.jpg");
	video.gameOverMenuTexture = loadTexture("images/GameOverMenuSprite.jpg");
	video.HUDBothAlive = loadTexture("images/HUDMenuBothAlive.png");
	video.HUDP1Dead = loadTexture("images/HUDMenuP1Dead.png");
	video.HUDP2Dead = loadTexture("images/HUDMenuP2Dead.png");
}

SDL_Texture* loadTexture(char path[])
{
	SDL_Surface* surface = IMG_Load(path);
	if (surface == NULL) {
		printf("error creating character surface: %s\n", path);
	}

	SDL_Texture* texture;
	texture = SDL_CreateTextureFromSurface(video.rend, surface);
	SDL_FreeSurface(surface);
	if (texture == NULL) {
		printf("error creating texture: %s\t%s\n", path, SDL_GetError());
		SDL_DestroyTexture(texture);
	}
	return texture;
}