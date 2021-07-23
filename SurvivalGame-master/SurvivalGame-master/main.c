#include <stdio.h>
#include "init_quit.h"
#include "game.h"

int main(void)
{
	char ipAddress[20] = "\0";
	int gamestate = 0;
	initGame();

	while (!menuStart(ipAddress))
	{
		initNetClient(ipAddress);
		gamestate = GameLoop();
		quitNetClient();

		if (gamestate == 1)
		{
			break;
		}
	}
	quitGame();
	

	return 0;
}