#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <SDL.h>

#include "video.h"
#include "player.h"
#include "menu.h"
#include "bullet.h"
#include "enemy.h"
#include "sdlnetclient.h"

int GameLoop()
{
	Player players[MAX_PLAYERS];
	Bullet bullets[MAX_BULLETS];
	Enemy enemies[MAX_ENEMIES];
	char out_data[packetSize] = "\0";
	char bulletData[2] = { '0', '\0' };

	int nrOfBullets = 0;
	int nrOfEnemies = 0;
	int spawnLoc = 1;

	unsigned int timePassed = 0;
	unsigned int startTime = 0;
	unsigned int endTime = 0;

	unsigned int last_SpawnTime = 0;
	unsigned int new_Spawntime = 0;

	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		initPlayer(&players[i]);
	}
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		initBullets(&bullets[i]);
	}

	SDL_Event event;
	int close_requested = 0;

	while (!close_requested)
	{
		startTime = SDL_GetTicks();

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				close_requested = 1;
				break;
			}
			if (players[0].isAlive == true)
			{
				switch (event.type)
				{
				case SDL_KEYDOWN:
					switch (event.key.keysym.scancode)
					{
					case SDL_SCANCODE_W:
						player_keyUp(&players[0], 1);
						break;

					case SDL_SCANCODE_S:
						player_keyDown(&players[0], 1);
						break;

					case SDL_SCANCODE_D:
						player_keyRight(&players[0], 1);
						break;

					case SDL_SCANCODE_A:
						player_keyLeft(&players[0], 1);
						break;

					case SDL_SCANCODE_UP:
						activateBullet(&bullets[nrOfBullets], &nrOfBullets, players[0].dest.x, players[0].dest.y, 1);
						pack_BulletData(bulletData, 1);
						break;

					case SDL_SCANCODE_DOWN:
						activateBullet(&bullets[nrOfBullets], &nrOfBullets, players[0].dest.x, players[0].dest.y, 2);
						pack_BulletData(bulletData, 2);
						break;

					case SDL_SCANCODE_RIGHT:
						activateBullet(&bullets[nrOfBullets], &nrOfBullets, players[0].dest.x, players[0].dest.y, 3);
						pack_BulletData(bulletData, 3);
						break;

					case SDL_SCANCODE_LEFT:
						activateBullet(&bullets[nrOfBullets], &nrOfBullets, players[0].dest.x, players[0].dest.y, 4);
						pack_BulletData(bulletData, 4);
						break;

					default:
						break;
					}
					break;

				case SDL_KEYUP:
					switch (event.key.keysym.scancode)
					{
					case SDL_SCANCODE_W:
						player_keyUp(&players[0], 0);
						break;

					case SDL_SCANCODE_S:
						player_keyDown(&players[0], 0);
						break;

					case SDL_SCANCODE_D:
						player_keyRight(&players[0], 0);
						break;

					case SDL_SCANCODE_A:
						player_keyLeft(&players[0], 0);
						break;

					default:
						break;
					}
				}
			}

		}

		if (SDLNet_CheckSockets(socketSet, 0))
		{
			if (SDLNet_SocketReady(udpsock))
			{
				if (SDLNet_UDP_RecvV(udpsock, pRecv))
				{
					unpackPlayerPacket(pRecv[0]->data, &players[1], &bullets[nrOfBullets], &nrOfBullets, &new_Spawntime);
					for (int i = 0; i < 10; i++)
					{
						strcpy(pRecv[i]->data, "\0");
					}
				}
			}
		}
		createPlayerPacket(out_data, bulletData, players[0].frame, players[0].flip, players[0].dest.x, players[0].dest.y, players[0].hp);
		strcpy(pSend->data, out_data);
		pSend->address.host = serverAddr.host;
		pSend->address.port = serverAddr.port;
		pSend->len = strlen((char *)pSend->data) + 1;
		SDLNet_UDP_Send(udpsock, -1, pSend);
		clearPackets(out_data, bulletData);

		if (!players_isAlive(players))
		{
			gameOverMenu(last_SpawnTime);
			return 0;
		}

		if (new_Spawntime > last_SpawnTime + 250)
		{
			enemies[nrOfEnemies] = spawnEnemy(&spawnLoc, &nrOfEnemies, &last_SpawnTime, new_Spawntime);
		}

		update_playerMovement(&players[0]);
		update_enemyMovement(enemies, players, nrOfEnemies);
		update_bulletMovement(bullets, nrOfBullets);

		BulletEnemy_Collision(bullets, enemies, nrOfBullets, nrOfEnemies);
		playerEnemy_collision(enemies, players, nrOfEnemies);

		organizeBullets(bullets, &nrOfBullets);
		organizeEnemies(enemies, &nrOfEnemies);

		SDL_RenderClear(video.rend);
		RenderBackground();

		RenderPlayers(players);

		RenderBullets(bullets, nrOfBullets);

		RenderEnemies(enemies, nrOfEnemies);
		RenderHUD(players[0].hp, players[1].hp, last_SpawnTime);
		SDL_RenderPresent(video.rend);


		endTime = SDL_GetTicks();
		timePassed = endTime - startTime;


		if (timePassed < (1000 / 60))
		{
			SDL_Delay((1000 / 60) - timePassed);
		}
	}
	return 1;
}