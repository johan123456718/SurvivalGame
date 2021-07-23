#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string.h>
#include "video.h"
#include "init_quit.h"
#include "menu.h"
#include "sdlnetclient.h"

int menuHoverQuit(char ipAddress[]);
int menuHoverPlay(char ipAddress[]);
int menuHoverIP(char ipAddress[]);
void enterIP(char ipAddress[]);

int menuStart(char ipAddress[])
{
	int quitGame = 0;
	SDL_Event keyCheck;
	int close_requested = 0;

	RenderMenuToWindow(1);
	while (!close_requested)
	{
		while (SDL_PollEvent(&keyCheck))
		{
			switch (keyCheck.type)
			{
			case SDL_QUIT:
				close_requested = 1;
				break;

			case SDL_KEYDOWN:
				switch (keyCheck.key.keysym.scancode)
				{
				case SDL_SCANCODE_UP:
					quitGame = menuHoverPlay(ipAddress);
					return quitGame;
					break;

				case SDL_SCANCODE_DOWN:
					quitGame = menuHoverQuit(ipAddress);
					return quitGame;
					break;
				default:
					break;
				}
			}break;
		}
	}
}

void gameOverMenu(int last_SpawnTime)
{
	SDL_Event keyCheck;
	int close_requested = 0;

	gameOverMenuState(last_SpawnTime);
	disconnectClient();
	while (!close_requested)
	{
		while (SDL_PollEvent(&keyCheck))
		{
			switch (keyCheck.type)
			{
			case SDL_QUIT:
				close_requested = 1;
				break;

			case SDL_KEYDOWN:
				switch (keyCheck.key.keysym.scancode)
				{
				case SDL_SCANCODE_RETURN:
					close_requested = 1;
					break;
				default:
					break;
				}
			}
		}
	}
}

/***************** [Local functions for menu.c] *****************/

int menuHoverPlay(char ipAddress[])
{
	int quitGame = 0;
	SDL_Event keyCheck;
	int close_requested = 0;

	RenderMenuToWindow(2);
	while (!close_requested)
	{
		while (SDL_PollEvent(&keyCheck))
		{
			switch (keyCheck.type)
			{
			case SDL_QUIT:
				close_requested = 1;
				quitGame = 1;
				break;

			case SDL_KEYDOWN:
				switch (keyCheck.key.keysym.scancode)
				{
				case SDL_SCANCODE_RETURN:
					printf("play option chosen\n");
					close_requested = 1;
					break;

				case SDL_SCANCODE_DOWN:
					quitGame = menuHoverIP(ipAddress);
					close_requested = 1;
					break;
				default:
					break;
				}
			}break;
		}
	}
	return quitGame;
}

int menuHoverIP(char ipAddress[])
{
	int quitGame = 0;
	SDL_Event keyCheck;
	int close_requested = 0;

	RenderMenuToWindow(3);
	while (!close_requested)
	{
		while (SDL_PollEvent(&keyCheck))
		{
			switch (keyCheck.type)
			{
			case SDL_QUIT:
				close_requested = 1;
				quitGame = 1;
				break;

			case SDL_KEYDOWN:
				switch (keyCheck.key.keysym.scancode)
				{
				case SDL_SCANCODE_RETURN:
					enterIP(ipAddress);
					quitGame = menuHoverIP(ipAddress);
					close_requested = 1;
					break;

				case SDL_SCANCODE_DOWN:
					quitGame = menuHoverQuit(ipAddress);
					close_requested = 1;
					break;
				case SDL_SCANCODE_UP:
					quitGame = menuHoverPlay(ipAddress);
					close_requested = 1;
					break;
				default:
					break;
				}
			}break;
		}
	}
	return quitGame;
}

int menuHoverQuit(char ipAddress[])
{
	int quitGame = 0;
	SDL_Event keyCheck;
	int close_requested = 0;

	RenderMenuToWindow(4);
	while (!close_requested)
	{
		while (SDL_PollEvent(&keyCheck))
		{
			switch (keyCheck.type)
			{
			case SDL_QUIT:
				close_requested = 1;
				quitGame = 1;
				break;

			case SDL_KEYDOWN:
				switch (keyCheck.key.keysym.scancode)
				{
				case SDL_SCANCODE_UP:
					quitGame = menuHoverIP(ipAddress);
					close_requested = 1;
					break;

				case SDL_SCANCODE_RETURN:
					quitGame = 1;
					close_requested = 1;
					break;
				default:
					break;
				}
			}break;
		}
	}
	return quitGame;
}

void enterIP(char ipAddress[])
{
	int quitGame = 0;
	SDL_Event EventKey;
	int close_requested = 0;

	char displayText[17] = "/0";

	while (!close_requested)
	{
		while (SDL_PollEvent(&EventKey))
		{
			switch (EventKey.type)
			{
			case SDL_QUIT:
				for (int i = 0; i < 20; i++)
				{
					ipAddress[i] = '\0';
				}
				close_requested = 1;
				quitGame = 1;
				break;

			case SDL_KEYDOWN:
				switch (EventKey.key.keysym.scancode)
				{
				case SDL_SCANCODE_0:
					if (strlen(ipAddress) < 15)
						strcat(ipAddress, "0");
					break;

				case SDL_SCANCODE_1:
					if (strlen(ipAddress) < 15)
						strcat(ipAddress, "1");
					break;

				case SDL_SCANCODE_2:
					if (strlen(ipAddress) < 15)
						strcat(ipAddress, "2");
					break;

				case SDL_SCANCODE_3:
					if (strlen(ipAddress) < 15)
						strcat(ipAddress, "3");
					break;

				case SDL_SCANCODE_4:
					if (strlen(ipAddress) < 15)
						strcat(ipAddress, "4");
					break;

				case SDL_SCANCODE_5:
					if (strlen(ipAddress) < 15)
						strcat(ipAddress, "5");
					break;

				case SDL_SCANCODE_6:
					if (strlen(ipAddress) < 15)
						strcat(ipAddress, "6");
					break;

				case SDL_SCANCODE_7:
					if (strlen(ipAddress) < 15)
						strcat(ipAddress, "7");
					break;

				case SDL_SCANCODE_8:
					if (strlen(ipAddress) < 15)
						strcat(ipAddress, "8");
					break;

				case SDL_SCANCODE_9:
					if (strlen(ipAddress) < 15)
						strcat(ipAddress, "9");
					break;

				case SDL_SCANCODE_PERIOD:
					if (strlen(ipAddress) < 15)
						strcat(ipAddress, ".");
					break;

				case SDL_SCANCODE_BACKSPACE:
					for (int i = 0; i < 20; i++)
					{
						ipAddress[i] = '\0';
					}
					break;

				case SDL_SCANCODE_ESCAPE:
					for (int i = 0; i < 20; i++)
					{
						ipAddress[i] = '\0';
					}
					close_requested = 1;
					break;

				case SDL_SCANCODE_RETURN:

					close_requested = 1;
					break;
				default:
					break;
				}
			}break;
		}
		RenderIP_Menu(ipAddress);
	}
	return quitGame;
}