#ifndef	ENEMY_H
#define ENEMY_H

#define MAX_ENEMIES 1000
#define ENEMY_SPEED 2
#define ENEMY_HP 5

#include <SDL.h>
#include <stdbool.h>
#include "player.h"

typedef struct
{
	int frame, HP;
	bool isAlive;
	SDL_Rect SpriteClips[9];
	SDL_Rect dest;
	SDL_RendererFlip flip;
}Enemy;

//Returns a new enemy to be placed in enemy array, which spawns a new enemy at one of 8 predefined spawn locations
Enemy spawnEnemy(int *spawnLoc, int *pnrOfEnemies, int *last_SpawnTime, int new_SpawnTime);
/*Calculates difference between an enemy and a player in x- and y-axis to determine hypotenuse lenght in order to 
update movement towards nearest player*/
void update_enemyMovement(Enemy enemies[], Player players[], int nrOfEnemies);
//Sort active enemies to be placed in bottom elements of array. Also updates nrOfEnemies with new value to indicate nr of active enemies
void organizeEnemies(Enemy enemies[], int *pNrOfEnemies);

#endif