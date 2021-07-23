#include <SDL.h>
#include "video.h"
#include "collision.h"

void BulletEnemy_Collision(Bullet bullets[], Enemy enemies[], int nrOfBullets, int nrOfEnemies)
{
	for (int i = 0; i < nrOfBullets; i++)
	{
		for (int j = 0; j < nrOfEnemies; j++)
		{
			if (enemies[j].isAlive == true)
			{
				if (bullets[i].dest.x - bullets[i].dest.w / 2 <= enemies[j].dest.x + enemies[j].dest.w / 2
					&& bullets[i].dest.x + bullets[i].dest.w / 2 >= enemies[j].dest.x - enemies[j].dest.w / 2)
				{
					if (bullets[i].dest.y - bullets[i].dest.h / 2 <= enemies[j].dest.y + enemies[j].dest.h / 2
						&& bullets[i].dest.y + bullets[i].dest.h / 2 >= enemies[j].dest.y - enemies[j].dest.h / 2)
					{
						bullets[i].active = false;
						enemies[j].isAlive = false;
					}
				}
			}
		}
	}
}
void playerEnemy_collision(Enemy enemies[], Player players[], int nrOfEnemies)
{
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		for (int j = 0; j < nrOfEnemies; j++)
		{
			if (players[i].isAlive == true)
			{
				if (players[i].dest.x - players[i].dest.w / 2 <= enemies[j].dest.x + enemies[j].dest.w / 2
					&& players[i].dest.x + players[i].dest.w / 2 >= enemies[j].dest.x - enemies[j].dest.w / 2)
				{
					if (players[i].dest.y - players[i].dest.h / 2 <= enemies[j].dest.y + enemies[j].dest.h / 2
						&& players[i].dest.y + players[i].dest.h / 2 >= enemies[j].dest.y - enemies[j].dest.h / 2)
					{
						enemies[j].isAlive = false;

						if (players[0].hp > 0 && i == 0)
							players[0].hp--;

					}
				}
			}
		}
	}
}

void player_BorderCollision(Player *p)
{
	if (p->dest.x <= 0)
		p->dest.x = 0;
	if (p->dest.y <= 0)
		p->dest.y = 0;
	if (p->dest.x >= WINDOW_WIDTH - p->dest.w)
		p->dest.x = WINDOW_WIDTH - p->dest.w;
	if (p->dest.y >= WINDOW_HEIGHT - p->dest.h)
		p->dest.y = WINDOW_HEIGHT - p->dest.h;
}
void bullet_BorderCollision(Bullet *bullet)
{
	if (bullet->dest.x <= 0)
	{
		bullet->active = false;
	}
	else if (bullet->dest.x >= WINDOW_WIDTH - bullet->dest.w)
	{
		bullet->active = false;
	}
	else if (bullet->dest.y <= 0)
	{
		bullet->active = false;
	}
	else if (bullet->dest.y >= WINDOW_HEIGHT - bullet->dest.h)
	{
		bullet->active = false;
	}
}