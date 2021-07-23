#ifndef SDLNETCLIENT_H
#define SDLNETCLIENT_H

#include <SDL_net.h>
#include "player.h"
#include "bullet.h"

#define packetSize 1024

SDLNet_SocketSet socketSet;
UDPsocket udpsock;
IPaddress serverAddr;
UDPpacket *pSend, **pRecv;

void initNetClient(char ipAddress[]);
void quitNetClient();
void pack_BulletData(char bulletData[], int dir_index);
void createPlayerPacket(char data[], char bulletData[], int frame, int flip, int destX, int destY, int hp);
void unpackPlayerPacket(char data[], Player *player, Bullet *bullet, int *nrOfBullets, unsigned int *new_SpawnTime);
void clearPackets(char data[], char bulletData[]);
void disconnectClient();

#endif#