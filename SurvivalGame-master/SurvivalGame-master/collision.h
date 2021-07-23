#ifndef COLLISION_H
#define COLLISION_H

#include "player.h"
#include "bullet.h"
#include "enemy.h"

//Checks if the player destination recangle has collided with the window borders.
void player_BorderCollision(Player *p);
//Checks if any bullet destination rect has collided with the window borders.
void bullet_BorderCollision(Bullet *bullet);
//Checks if any bullet has collided with an enemy.
void BulletEnemy_Collision(Bullet bullets[], Enemy enemies[], int nrOfBullets, int nrOfEnemies);
//Checks if a player has collided with an enemy. 
void playerEnemy_collision(Enemy enemies[], Player players[], int nrOfEnemies);

#endif