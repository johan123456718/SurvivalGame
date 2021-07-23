#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <sdl.h>
#include <sdl_net.h>
#include "udpServer.h"

void initUdpServer()
{
	Uint16 recvPort = 5000, sendPort = 6000;

	/* Initialize SDL_net */
	if (SDLNet_Init() < 0) {
		printf("SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	else printf("SDLNet_init successful!\n");

	/* Open a socket */
	if (!(udpRecvSock = SDLNet_UDP_Open(recvPort))) {
		printf("SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	else printf("Port: %d, opened successfully!\n", recvPort);
	if (!(udpSendSock = SDLNet_UDP_Open(sendPort))) {
		printf("SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	else printf("Port: %d, opened successfully!\n", sendPort);

	/* Make space for the packet */
	if (!(packet = SDLNet_AllocPacket(packetSize))) {
		printf("packet: SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	else printf("Allocating memory for packet, packetsize %d, successful!\n", packetSize);

	/* Initialize SDLNet_SocketSet */
	socketSet = SDLNet_AllocSocketSet(1);
	if (!socketSet) {
		printf("SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	else printf("SDLNet_AllocSocketSet Successful!\n");
	if (!(SDLNet_UDP_AddSocket(socketSet, udpRecvSock))) {
		printf("udpRecvSock, SDLNet_Addsocket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	else printf("udpRecvSock, SDLNet_UDP_Addsocket successful!\n");
}

void findClients()
{
	printf("look for clients\n");
	while (!p1Connected) { // look for p1 address... typedef{bool connected, IPaddress address}client, använd detta och gör den till en enda loop för varje gjord struct och kolla "connected" elementet.
		if (SDLNet_CheckSockets(socketSet, 0)) {
			if (SDLNet_SocketReady(udpRecvSock)) {
				if (SDLNet_UDP_Recv(udpRecvSock, packet)) {
					if (packet->address.host != clientAddr2.host) {
						clientAddr1.host = packet->address.host;
						clientAddr1.port = packet->address.port;
						p1Connected = true;
						printf("clientAddr1 connected: %u %u\n", clientAddr1.host, clientAddr1.port);
					}
				}
			}
		}
	}
	while (!p2Connected) { // look for p2 address
		if (SDLNet_CheckSockets(socketSet, 0)) {
			if (SDLNet_SocketReady(udpRecvSock)) {
				if (SDLNet_UDP_Recv(udpRecvSock, packet)) {
					if (packet->address.host != clientAddr1.host) {
						clientAddr2.host = packet->address.host;
						clientAddr2.port = packet->address.port;
						p2Connected = true;
						printf("clientAddr2 connected: %u %u\n", clientAddr2.host, clientAddr2.port);
					}
				}
			}
		}
	}
}

void serverLoop()
{
	unsigned int currentTime = 0, timeResetValue = 0, lastTimeRecv = 0;
	char clockSync[100] = "\0";
	char clock[100];
	bool timerIsOn = false;
	bool quit = false;
	bool exit = false;
	p1Connected = false;
	p2Connected = false;

	while (!quit) {
		if (SDLNet_CheckSockets(socketSet, 1000)) { //clear buffer
			while (SDLNet_SocketReady(udpRecvSock)) {
				SDLNet_UDP_Recv(udpRecvSock, packet);
			}
		}
		if (!p1Connected || !p2Connected) findClients();
		printf("both players connected\n");
		if (!timerIsOn) {
			if (SDL_Init(SDL_INIT_TIMER) != 0) {
				printf("SDL_Init: %s", SDL_GetError());
			}
			else {
				printf("SDL_INIT_TIMER successful\n");
				timerIsOn = true;
			}
		}
		else timeResetValue = SDL_GetTicks();
		while (p1Connected && p2Connected) { // ger till en funktion?
			currentTime = SDL_GetTicks() - timeResetValue;	// sätt allt detta inuti
			memset(clockSync, '\0', 100);					// if (!strcmp((char*)packet->data, "disconnect")){}...
			itoa(currentTime, clock, 10);					// ...
			strcpy(clockSync, " ");							// else{*HÄR*}
			strcat(clockSync, clock);						// för mer exakt klocka
			if (SDLNet_CheckSockets(socketSet, 0)) {
				if (SDLNet_SocketReady(udpRecvSock)) {
					if (SDLNet_UDP_Recv(udpRecvSock, packet)) {
						if (packet->address.host == clientAddr1.host) {
							lastTimeRecv = SDL_GetTicks() - timeResetValue;
							if (!strcmp((char*)packet->data, "disconnect")) {
								p1Connected = false;
								p2Connected = false;
							}
							else if (!strcmp((char*)packet->data, "quit")) {
								p1Connected = false;
								quit = true;
							}
							else {
								strcat(packet->data, clockSync);
								packet->address.host = clientAddr2.host;
								packet->address.port = clientAddr2.port;
								packet->len = strlen((char *)packet->data) + 1;
								SDLNet_UDP_Send(udpSendSock, -1, packet);
							}
						}
						else if(packet->address.host == clientAddr2.host){
							lastTimeRecv = SDL_GetTicks() - timeResetValue;
							if (!strcmp((char*)packet->data, "disconnect")) {
								p2Connected = false;
								p1Connected = false;
							}
							else if (!strcmp((char*)packet->data, "quit")) {
								p1Connected = false;
								quit = true;
							}
							else {
								strcat(packet->data, clockSync);
								packet->address.host = clientAddr1.host;
								packet->address.port = clientAddr1.port;
								packet->len = strlen((char *)packet->data) + 1;
								SDLNet_UDP_Send(udpSendSock, -1, packet);
							}
						}
					}
				}
			}
			if (lastTimeRecv + 10000 < SDL_GetTicks() - timeResetValue) {
				p1Connected = false;
				p2Connected = false;
				quit = true;
			}
		}
	}
}

void closeServer()
{
	SDLNet_FreeSocketSet(socketSet);
	SDLNet_FreePacket(packet);
	SDLNet_Quit();
	SDL_Quit();
}