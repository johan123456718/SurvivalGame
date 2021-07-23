#ifndef BULLET_H
#define BULLET_H

#include <stdbool.h>

#define MAX_BULLETS 500
#define BULLET_SPEED 15


//ADT for bullet object
typedef struct {
	SDL_Rect dest;
	int shoot_up, shoot_down, shoot_right, shoot_left;
	bool active;
} Bullet;

//Updates all bullet movement according to flags, and calls for window collision detection.
void update_bulletMovement(Bullet bullets[], int nrOfPlayers);
//Bubble-sort bullet array and calculate new nrOfBullets.
void organizeBullets(Bullet bullets[], int *nrOfBullets);
//Gives the correct direction index to a string (to be used with the data-string declared in the game-loop).
void send_bulletData(char data[], int dir_index);
//Initiate all bullets to be deactivated.
void initBullets(Bullet *bullet);
//Activates bullet and sets flags accordingly to direction.
void activateBullet(Bullet *bullet, int *nrOfBullets, int x, int y, int dir_index);

#endif
