#include <SDL.h>
#include "video.h"
#include "player.h"
#include "collision.h"
int players_isAlive(Player players[])
{
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		if (players[i].hp == 0)
		{
			players[i].isAlive = false;
			players[i].angle = 90;
		}
	}

	if (players[0].isAlive == false && players[1].isAlive == false)
	{
		return 0;
	}
	else
		return 1;
}
void update_playerMovement(Player *p)
{
	if (p->hp > 0)
	{
		if (p->up && !p->down)
		{
			p->dest.y -= PLAYER_SPEED;

			p->flip == SDL_FLIP_NONE;

			if (p->frame == 4)
				p->frame = 5;
			else
				p->frame = 4;
		}
		if (p->down && !p->up)
		{
			p->dest.y += PLAYER_SPEED;

			p->flip == SDL_FLIP_NONE;

			if (p->frame == 0)
				p->frame = 1;
			else
				p->frame = 0;
		}
		if (p->left && !p->right)
		{
			p->dest.x -= PLAYER_SPEED;

			if (p->flip == SDL_FLIP_NONE)
			{
				p->flip = SDL_FLIP_HORIZONTAL;
			}

			if (p->frame == 2)
				p->frame = 3;
			else
				p->frame = 2;
		}
		if (p->right && !p->left)
		{
			p->dest.x += PLAYER_SPEED;

			if (p->flip == SDL_FLIP_HORIZONTAL)
			{
				p->flip = SDL_FLIP_NONE;
			}

			if (p->frame == 2)
				p->frame = 3;
			else
				p->frame = 2;
		}

		player_BorderCollision(p);
	}
}

void player_keyUp(Player *p, int index)
{
	if (index == 1)
	{
		p->up = 1;
	}
	else if (index == 0)
	{
		p->up = 0;
		p->frame = 4;
	}
}

void player_keyDown(Player *p, int index)
{
	if (index == 1)
	{
		p->down = 1;
	}
	else if (index == 0)
	{
		p->down = 0;
		p->frame = 6;
	}
}

void player_keyRight(Player *p, int index)
{
	if (index == 1)
	{
		p->right = 1;
	}
	else if (index == 0)
	{
		p->right = 0;
		p->frame = 7;
	}
}
void player_keyLeft(Player *p, int index)
{
	if (index == 1)
	{
		p->left = 1;

	}
	else if (index == 0)
	{
		p->left = 0;
		p->frame = 7;
	}
}
void initPlayer(Player *p)
{
	p->up = 0;
	p->down = 0;
	p->left = 0;
	p->right = 0;

	p->dest.h = 32;
	p->dest.w = 32;
	p->dest.x = (WINDOW_WIDTH - p->dest.w) / 2;
	p->dest.y = (WINDOW_HEIGHT - p->dest.h) / 2;

	p->frame = 6;
	p->hp = PLAYER_HP;
	p->isAlive = true;
	p->flip = SDL_FLIP_NONE;
	p->angle = 0;

	p->SpriteClips[0].x = 0;
	p->SpriteClips[0].y = 0;
	p->SpriteClips[0].w = 16;
	p->SpriteClips[0].h = 16;

	p->SpriteClips[1].x = 16;
	p->SpriteClips[1].y = 0;
	p->SpriteClips[1].w = 16;
	p->SpriteClips[1].h = 16;

	p->SpriteClips[2].x = 32;
	p->SpriteClips[2].y = 0;
	p->SpriteClips[2].w = 16;
	p->SpriteClips[2].h = 16;

	p->SpriteClips[3].x = 48;
	p->SpriteClips[3].y = 0;
	p->SpriteClips[3].w = 16;
	p->SpriteClips[3].h = 16;

	p->SpriteClips[4].x = 64;
	p->SpriteClips[4].y = 0;
	p->SpriteClips[4].w = 16;
	p->SpriteClips[4].h = 16;

	p->SpriteClips[5].x = 80;
	p->SpriteClips[5].y = 0;
	p->SpriteClips[5].w = 16;
	p->SpriteClips[5].h = 16;

	p->SpriteClips[6].x = 96;
	p->SpriteClips[6].y = 0;
	p->SpriteClips[6].w = 16;
	p->SpriteClips[6].h = 16;

	p->SpriteClips[7].x = 112;
	p->SpriteClips[7].y = 0;
	p->SpriteClips[7].w = 16;
	p->SpriteClips[7].h = 16;
}