#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <SDL_net.h>
#include "sdlnetclient.h"

void initNetClient(char ipAddress[])
{
	Uint16 clientPort = 4000;
	Uint16 serverPort = 5000; // Server has a seperate port for both clients.


	char serverIp[16] = "\0";
	strcpy(serverIp, ipAddress);

	/* Initialize SDL_net */
	if (SDLNet_Init() < 0) {
		printf("SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	else printf("SDLNet_init successful!\n");

	/* Open a socket on random port */
	if (!(udpsock = SDLNet_UDP_Open(clientPort))) {
		printf("SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	else printf("Port: %d, opened successfully!\n", clientPort);

	/* Resolve server name */
	if (SDLNet_ResolveHost(&serverAddr, serverIp, serverPort)) {
		printf("SDLNet_ResolveHost(serverIp: %s port: %d): %s\n", serverIp, serverPort, SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	else printf("SDLNet_ResolveHost, serverAddr with \"serverIp\" and %d, successful", serverPort);

	/* Allocate memory for the packets */
	if (!(pSend = SDLNet_AllocPacket(packetSize))) {
		printf("SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	else printf("Allocating memory for sending packet, size: %d, successful!\n", packetSize);
	if (!(pRecv = SDLNet_AllocPacketV(10, packetSize))) {
		printf("SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	else printf("Allocating memory for recieving packet, size: %d, successful!\n", packetSize);

	/* Initialize SDLNet_SocketSet */
	socketSet = SDLNet_AllocSocketSet(1);
	if (!socketSet) {
		printf("SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	else printf("SDLNet_AllocSocketSet Successful!\n");
	if (!(SDLNet_UDP_AddSocket(socketSet, udpsock))) {
		printf("SDLNet_Addsocket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	else printf("SDLNet_UDP_Addsocket successful!\n");

	printf("SDLNet_ResloveIP: %s", SDLNet_ResolveIP(&serverAddr));
}

void quitNetClient() {
	disconnectClient();
	SDLNet_FreeSocketSet(socketSet);
	SDLNet_FreePacket(pSend);
	SDLNet_FreePacketV(pRecv);
	SDLNet_Quit();
}

void pack_BulletData(char bulletData[], int dir_index)
{
	if (dir_index == 1)
	{
		bulletData[0] = '1';
	}
	else if (dir_index == 2)
	{
		bulletData[0] = '2';
	}
	else if (dir_index == 3)
	{
		bulletData[0] = '3';
	}
	else if (dir_index == 4)
	{
		bulletData[0] = '4';
	}
	else
	{
		bulletData[0] = '0';
	}
}

void createPlayerPacket(char data[], char bulletData[], int frame, int flip, int destX, int destY, int hp)
{

	char strFrame[2] = "\0";
	char strFlip[2] = "\0";
	char strHP[2] = "\0";
	char strDestX[5] = "\0";
	char strDestY[5] = "\0";

	itoa(frame, strFrame, 10);
	itoa(flip, strFlip, 10);
	itoa(hp, strHP, 10);
	itoa(destX, strDestX, 10);
	itoa(destY, strDestY, 10);

	strcat(data, strFrame);
	data[strlen(data)] = 32;
	strcat(data, strFlip);
	data[strlen(data)] = 32;
	strcat(data, bulletData);
	data[strlen(data)] = 32;
	strcat(data, strHP);
	data[strlen(data)] = 32;
	strcat(data, strDestX);
	data[strlen(data)] = 32;
	strcat(data, strDestY);

}

void unpackPlayerPacket(char data[], Player *player, Bullet *bullet, int *nrOfBullets, unsigned int *new_SpawnTime)
{
	char frame[2] = "\0";
	char flip[2] = "\0";
	char destx[5] = "\0";
	char desty[5] = "\0";
	char hp[2] = "\0";
	char SpawnTime[10] = "\0";


	frame[0] = data[0];
	flip[0] = data[2];
	hp[0] = data[6];

	int i = 8;
	for (int x = 0; data[i] != 32; x++)
	{
		destx[x] = data[i++];
	}
	i++;
	for (int x = 0; data[i] != 32 && data[i] != 0; x++)
	{
		desty[x] = data[i++];
	}
	i++;
	for (int x = 0; data[i] != 32 && data[i] != 0; x++)
	{
		SpawnTime[x] = data[i++];
	}


	player->frame = atoi(frame);
	player->flip = atoi(flip);
	player->hp = atoi(hp);
	player->dest.x = atoi(destx);
	player->dest.y = atoi(desty);

	*new_SpawnTime = (unsigned)atoi(SpawnTime);

	if (data[4] == '1')
	{
		activateBullet(bullet, nrOfBullets, player->dest.x, player->dest.y, 1);
	}
	if (data[4] == '2')
	{
		activateBullet(bullet, nrOfBullets, player->dest.x, player->dest.y, 2);
	}
	if (data[4] == '3')
	{
		activateBullet(bullet, nrOfBullets, player->dest.x, player->dest.y, 3);
	}
	if (data[4] == '4')
	{
		activateBullet(bullet, nrOfBullets, player->dest.x, player->dest.y, 4);
	}
}

void clearPackets(char data[], char bulletData[])
{
	memset(data + 0, '\0', strlen(data));
	bulletData[0] = '0';
}

void disconnectClient()
{
	strcpy(pSend->data, "disconnect");
	pSend->address.host = serverAddr.host;
	pSend->address.port = serverAddr.port;
	pSend->len = strlen((char *)pSend->data) + 1;
	SDLNet_UDP_Send(udpsock, -1, pSend);
}