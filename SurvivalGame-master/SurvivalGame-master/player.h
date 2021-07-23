#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <stdbool.h>

#define MAX_PLAYERS 2 //Defines the max amount of players in one game.
#define PLAYER_SPEED 4 //Defines the velocity of the players.
#define PLAYER_HP 5 //Defines player healthpoints, in other words, how many times the player can get hit before it dies.

//ADT for player object
typedef struct {
	int frame, hp, angle;
	bool isAlive;
	SDL_Rect SpriteClips[8];
	SDL_Rect dest;
	SDL_RendererFlip flip;

	int up, down, left, right;
} Player;

//Checks if the player is alive, and flips it's sprite 90 degrees if not.
int players_isAlive(Player players[]);
//Initiate values for players.
void initPlayer(Player *p);
//Move the player destination rectangle accordingly to keyboard input flags.
void update_playerMovement(Player *p);
//Set flags for W keyboard input (index = 1 indicates keydown, index = 0 keyup).
void player_keyUp(Player *p, int index);
//Set flags for S keyboard input.
void player_keyDown(Player *p, int index);
//Set flags for A keyboard input.
void player_keyLeft(Player *p, int index);
//Set flags for D keyboard input.
void player_keyRight(Player *p, int index);

#endif