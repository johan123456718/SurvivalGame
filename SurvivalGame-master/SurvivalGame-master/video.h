#ifndef VIDEO_H
#define VIDEO_H


#include <SDL.H>
#include <SDL_ttf.h>
#include "player.h"
#include "bullet.h"
#include "enemy.h"

#define WINDOW_WIDTH (1280) //Defines the width of the gamewindow.
#define WINDOW_HEIGHT (720) //Defines the height of the gamewindow.

//A struct to define and hold the gamewindow, renderer and textures.
struct {
	SDL_Window* win;
	SDL_Renderer* rend;
	SDL_Texture* bgTexture;
	SDL_Texture* player1Texture;
	SDL_Texture* player2Texture;
	SDL_Texture* enemyTexture;
	SDL_Texture* bulletTexture;
	SDL_Texture* menuStartTexture;
	SDL_Texture* menuHoverPlayTexture;
	SDL_Texture* menuHoverQuitTexture;
	SDL_Texture* menuHoverIPTexture;
	SDL_Texture* enterIpMenuTexture;
	SDL_Texture* gameOverMenuTexture;
	SDL_Texture* HUDBothAlive;
	SDL_Texture* HUDP1Dead;
	SDL_Texture* HUDP2Dead;
} video;

//A struct to define font, color, textures and rectangles to be used with TTF text.
struct {
	TTF_Font* font;
	SDL_Color color;
	SDL_Texture* TextSurface;
	SDL_Texture* hp1_texture;
	SDL_Texture* hp2_texture;
	SDL_Texture* score_texture;
	SDL_Texture* IPaddress_texture;
	SDL_Rect hp1_dest;
	SDL_Rect hp2_dest;
	SDL_Rect score_dest;
	SDL_Rect IPaddress_dest;
} text;

//Create a window + renderer + necessary textures.
void initVideo();
//Renders the playingfield, the background image. 
void RenderBackground();
//Renders a player sprite accordingly to its current destination rectangle and sprite frame.
void RenderPlayers(Player players[]);
//Renders all enemies with correct sprites for their current destination rectangles and sprite frames.
void RenderEnemies(Enemy enemies[], int nrOfEnemies);
//Renders all bullets
void RenderBullets(Bullet bullets[], int nrOfBullets);
//Renders the correct sprite for the current menustate define by the integer sent with the functioncall.
void RenderMenuToWindow(int menustate);
//Function that displays three integer values representing player one and twos HP and the current score in the HUD ingame.
void DisplayText(int player1_hp, int player2_hp, int score);
//Function that renders the correct background sprite for the menustate where the user enters an server IP-address.
void RenderIP_Menu(char IpText[]);
//Function that renders the correct background for the gameover gamestate and prints the final score. 
void gameOverMenuState(int score);
//Renders the correct state of the HUD to the gamewindow. 
void RenderHUD(int player1_hp, int player2_hp, int score);

#endif