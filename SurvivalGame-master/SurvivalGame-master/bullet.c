#include <SDL.h>
#include "bullet.h"
#include "collision.h"

void update_bulletMovement(Bullet bullets[], int nrOfBullets)
{
	for (int i = 0; i < nrOfBullets; i++)
	{
		if (bullets[i].active == true)
		{
			if (bullets[i].shoot_right)
				bullets[i].dest.x += BULLET_SPEED;
			else if (bullets[i].shoot_left)
				bullets[i].dest.x -= BULLET_SPEED;
			else if (bullets[i].shoot_up)
				bullets[i].dest.y -= BULLET_SPEED;
			else if (bullets[i].shoot_down)
				bullets[i].dest.y += BULLET_SPEED;

			bullet_BorderCollision(&bullets[i]);
		}
	}

}
void organizeBullets(Bullet bullets[], int *pNrOfBullets)
{
	Bullet tmp;
	for (int i = 0; i < MAX_BULLETS - 1; i++)
	{
		for (int j = 0; j < MAX_BULLETS - i - 1; j++)
		{
			if (bullets[j].active == false && bullets[j + 1].active == true)
			{
				tmp = bullets[j];
				bullets[j] = bullets[j + 1];
				bullets[j + 1] = tmp;
			}
		}
	}

	*pNrOfBullets = 0;
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (bullets[i].active == true)
		{
			(*pNrOfBullets)++;
		}
	}
}
void activateBullet(Bullet *bullet, int *pnrOfBullets, int x, int y, int dir_index)
{
	bullet->active = true;

	if (dir_index == 1)
	{
		bullet->shoot_up = 1;
		bullet->shoot_down = 0;
		bullet->shoot_right = 0;
		bullet->shoot_left = 0;
		bullet->dest.x = x + 7;
		bullet->dest.y = y - 5;
	}
	else if (dir_index == 2)
	{
		bullet->shoot_up = 0;
		bullet->shoot_down = 1;
		bullet->shoot_right = 0;
		bullet->shoot_left = 0;
		bullet->dest.x = x + 7;
		bullet->dest.y = y + 20;
	}
	else if (dir_index == 3)
	{
		bullet->shoot_up = 0;
		bullet->shoot_down = 0;
		bullet->shoot_right = 1;
		bullet->shoot_left = 0;
		bullet->dest.x = x + 10;
		bullet->dest.y = y + 10;
	}
	else if (dir_index == 4)
	{
		bullet->shoot_up = 0;
		bullet->shoot_down = 0;
		bullet->shoot_right = 0;
		bullet->shoot_left = 1;
		bullet->dest.x = x - 7;
		bullet->dest.y = y + 10;
	}

	if (*pnrOfBullets < MAX_BULLETS - 1)
		(*pnrOfBullets)++;
}
void send_bulletData(char data[], int dir_index)
{
	if (dir_index == 1)
	{
		data[12] = '1';
	}
	else if (dir_index == 2)
	{
		data[12] = '2';
	}
	else if (dir_index == 3)
	{
		data[12] = '3';
	}
	else if (dir_index == 4)
	{
		data[12] = '4';
	}
	else
		data[12] = '0';
}

void initBullets(Bullet *bullet)
{
	bullet->dest.x = NULL;
	bullet->dest.y = NULL;
	bullet->dest.h = 16;
	bullet->dest.w = 16;
	bullet->shoot_up = 0;
	bullet->shoot_down = 0;
	bullet->shoot_right = 0;
	bullet->shoot_left = 0;
	bullet->active = false;

}