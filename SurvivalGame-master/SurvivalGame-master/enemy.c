#include <SDL.h>
#include "enemy.h"
#include "video.h"

void animate_enemy(Enemy *enemy, int target_x, int target_y, float delta_x, float delta_y);

Enemy spawnEnemy(int *spawnLoc, int *nrOfEnemies, int *last_SpawnTime, int new_SpawnTime)
{
	Enemy newEnemy;
	newEnemy.HP = ENEMY_HP;
	newEnemy.isAlive = true;

	if (*spawnLoc == 1)
	{	//Upper left corner
		newEnemy.dest.h = 32;
		newEnemy.dest.w = 32;
		newEnemy.dest.x = 0;
		newEnemy.dest.y = 0;

	}
	else if (*spawnLoc == 2)
	{	//Upper right corner
		newEnemy.dest.h = 32;
		newEnemy.dest.w = 32;
		newEnemy.dest.x = WINDOW_WIDTH;
		newEnemy.dest.y = 0;
	}
	else if (*spawnLoc == 3)
	{	//Lower right corner
		newEnemy.dest.h = 32;
		newEnemy.dest.w = 32;
		newEnemy.dest.x = WINDOW_WIDTH;
		newEnemy.dest.y = WINDOW_HEIGHT;
	}
	else if (*spawnLoc == 4)
	{	//Lower left corner
		newEnemy.dest.h = 32;
		newEnemy.dest.w = 32;
		newEnemy.dest.x = 0;
		newEnemy.dest.y = WINDOW_HEIGHT;
	}
	else if (*spawnLoc == 5)
	{	
		newEnemy.dest.h = 32;
		newEnemy.dest.w = 32;
		newEnemy.dest.x = WINDOW_WIDTH / 2;
		newEnemy.dest.y = 70;
	}
	else if (*spawnLoc == 6)
	{	
		newEnemy.dest.h = 32;
		newEnemy.dest.w = 32;
		newEnemy.dest.x = WINDOW_WIDTH;
		newEnemy.dest.y = WINDOW_HEIGHT / 2;
	}
	else if (*spawnLoc == 7)
	{
		newEnemy.dest.h = 32;
		newEnemy.dest.w = 32;
		newEnemy.dest.x = WINDOW_WIDTH / 2;
		newEnemy.dest.y = WINDOW_HEIGHT;
	}
	else if (*spawnLoc == 8)
	{
		newEnemy.dest.h = 32;
		newEnemy.dest.w = 32;
		newEnemy.dest.x = 0;
		newEnemy.dest.y = WINDOW_HEIGHT / 2;
	}

	newEnemy.frame = 8;
	newEnemy.flip = SDL_FLIP_NONE;

	newEnemy.SpriteClips[0].x = 0;
	newEnemy.SpriteClips[0].y = 0;
	newEnemy.SpriteClips[0].w = 32;
	newEnemy.SpriteClips[0].h = 32;

	newEnemy.SpriteClips[1].x = 32;
	newEnemy.SpriteClips[1].y = 0;
	newEnemy.SpriteClips[1].w = 32;
	newEnemy.SpriteClips[1].h = 32;

	newEnemy.SpriteClips[2].x = 64;
	newEnemy.SpriteClips[2].y = 0;
	newEnemy.SpriteClips[2].w = 32;
	newEnemy.SpriteClips[2].h = 32;

	newEnemy.SpriteClips[3].x = 0;
	newEnemy.SpriteClips[3].y = 32;
	newEnemy.SpriteClips[3].w = 32;
	newEnemy.SpriteClips[3].h = 32;

	newEnemy.SpriteClips[4].x = 32;
	newEnemy.SpriteClips[4].y = 32;
	newEnemy.SpriteClips[4].w = 32;
	newEnemy.SpriteClips[4].h = 32;

	newEnemy.SpriteClips[5].x = 64;
	newEnemy.SpriteClips[5].y = 32;
	newEnemy.SpriteClips[5].w = 32;
	newEnemy.SpriteClips[5].h = 32;

	newEnemy.SpriteClips[6].x = 0;
	newEnemy.SpriteClips[6].y = 64;
	newEnemy.SpriteClips[6].w = 32;
	newEnemy.SpriteClips[6].h = 32;

	newEnemy.SpriteClips[7].x = 32;
	newEnemy.SpriteClips[7].y = 64;
	newEnemy.SpriteClips[7].w = 32;
	newEnemy.SpriteClips[7].h = 32;

	newEnemy.SpriteClips[8].x = 64;
	newEnemy.SpriteClips[8].y = 64;
	newEnemy.SpriteClips[8].w = 32;
	newEnemy.SpriteClips[8].h = 32;

	*last_SpawnTime = new_SpawnTime;

	(*nrOfEnemies)++;

	(*spawnLoc)++;
	if (*spawnLoc == 9)
		*spawnLoc = 1;

	return newEnemy;
}

void update_enemyMovement(Enemy enemies[], Player players[], int nrOfEnemies)
{
	float delta_1x, delta_1y, delta_2x, delta_2y, p1Distance, p2Distance;
	int target_1x, target_1y, target_2x, target_2y;

	for (int i = 0; i < nrOfEnemies; i++)
	{

		target_1x = players[0].dest.x;
		target_1y = players[0].dest.y;
		delta_1x = target_1x - enemies[i].dest.x;
		delta_1y = target_1y - enemies[i].dest.y;
		p1Distance = sqrt(delta_1x * delta_1x + delta_1y * delta_1y);

		target_2x = players[1].dest.x;
		target_2y = players[1].dest.y;
		delta_2x = target_2x - enemies[i].dest.x;
		delta_2y = target_2y - enemies[i].dest.y;
		p2Distance = sqrt(delta_2x * delta_2x + delta_2y * delta_2y);

		if (players[0].isAlive == true && players[1].isAlive == true)
		{
			if (p1Distance < p2Distance)
			{
				enemies[i].dest.x += delta_1x * ENEMY_SPEED / p1Distance;
				enemies[i].dest.y += delta_1y * ENEMY_SPEED / p1Distance;
				animate_enemy(&enemies[i], target_1x, target_1y, delta_1x, delta_1y);
			}
			else if (p2Distance < p1Distance)
			{
				enemies[i].dest.x += delta_2x * ENEMY_SPEED / p2Distance;
				enemies[i].dest.y += delta_2y * ENEMY_SPEED / p2Distance;
				animate_enemy(&enemies[i], target_2x, target_2y, delta_2x, delta_2y);
			}
			else if (p1Distance == p2Distance)
			{
				enemies[i].dest.x += delta_1x * ENEMY_SPEED / p1Distance;
				enemies[i].dest.y += delta_1y * ENEMY_SPEED / p1Distance;
				animate_enemy(&enemies[i], target_1x, target_1y, delta_1x, delta_1y);
			}
		}

		if (players[0].isAlive == false)
		{
			enemies[i].dest.x += delta_2x * ENEMY_SPEED / p2Distance;
			enemies[i].dest.y += delta_2y * ENEMY_SPEED / p2Distance;
			animate_enemy(&enemies[i], target_2x, target_2y, delta_2x, delta_2y);
		}
		else if (players[1].isAlive == false)
		{
			enemies[i].dest.x += delta_1x * ENEMY_SPEED / p1Distance;
			enemies[i].dest.y += delta_1y * ENEMY_SPEED / p1Distance;
			animate_enemy(&enemies[i], target_1x, target_1y, delta_1x, delta_1y);
		}
	}
}

void organizeEnemies(Enemy enemies[], int *pNrOfEnemies)
{
	Enemy tmp_enemy;
	for (int i = 0; i < *pNrOfEnemies; i++)
	{
		for (int j = 0; j < *pNrOfEnemies - i; j++)
		{
			if (enemies[j].isAlive == false && enemies[j + 1].isAlive == true)
			{
				tmp_enemy = enemies[j];
				enemies[j] = enemies[j + 1];
				enemies[j + 1] = tmp_enemy;
			}
		}
	}

	*pNrOfEnemies = 0;
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		if (enemies[i].isAlive == true)
		{
			(*pNrOfEnemies)++;
		}
	}
}

/*************** Local functions for enemy.c ****************/

void animate_enemy(Enemy *enemy, int target_x, int target_y, float delta_x, float delta_y)
{
	if (delta_x < 0 && delta_y < 0)
	{
		if (delta_y > delta_x)
		{
			enemy->flip = SDL_FLIP_NONE;

			if (enemy->frame == 0)
				enemy->frame = 1;
			else if (enemy->frame == 1)
				enemy->frame = 2;
			else
				enemy->frame = 0;
		}
		else if (delta_y < delta_x)
		{
			enemy->flip = SDL_FLIP_NONE;
			if (enemy->frame == 6)
				enemy->frame = 7;
			else if (enemy->frame == 7)
				enemy->frame = 8;
			else
				enemy->frame = 6;
		}
	}
	if (delta_x < 0 && delta_y > 0)
	{
		if (enemy->dest.y - target_y > delta_x)
		{
			enemy->flip = SDL_FLIP_NONE;

			if (enemy->frame == 0)
				enemy->frame = 1;
			else if (enemy->frame == 1)
				enemy->frame = 2;
			else
				enemy->frame = 0;
		}
		else if (enemy->dest.y - target_y < delta_x)
		{
			enemy->flip = SDL_FLIP_NONE;
			if (enemy->frame == 3)
				enemy->frame = 4;
			else if (enemy->frame == 4)
				enemy->frame = 5;
			else
				enemy->frame = 3;
		}
	}
	if (delta_x > 0 && delta_y < 0)
	{
		if (enemy->dest.x - target_x > delta_y)
		{
			enemy->flip = SDL_FLIP_NONE;
			if (enemy->frame == 6)
				enemy->frame = 7;
			else if (enemy->frame == 7)
				enemy->frame = 8;
			else
				enemy->frame = 6;
		}
		else if (enemy->dest.x - target_x < delta_y)
		{
			if (enemy->flip == SDL_FLIP_NONE)
				enemy->flip = SDL_FLIP_HORIZONTAL;

			if (enemy->frame == 0)
				enemy->frame = 1;
			else if (enemy->frame == 1)
				enemy->frame = 2;
			else
				enemy->frame = 0;
		}
	}
	if (delta_x > 0 && delta_y > 0)
	{
		if (delta_x > delta_y)
		{
			if (enemy->flip == SDL_FLIP_NONE)
				enemy->flip = SDL_FLIP_HORIZONTAL;

			if (enemy->frame == 0)
				enemy->frame = 1;
			else if (enemy->frame == 1)
				enemy->frame = 2;
			else
				enemy->frame = 0;
		}
		else if (delta_x < delta_y)
		{
			enemy->flip = SDL_FLIP_NONE;

			enemy->flip = SDL_FLIP_NONE;
			if (enemy->frame == 3)
				enemy->frame = 4;
			else if (enemy->frame == 4)
				enemy->frame = 5;
			else
				enemy->frame = 3;
		}
	}
}