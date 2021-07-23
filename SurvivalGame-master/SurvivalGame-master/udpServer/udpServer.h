#ifndef SDLNETCLIENT_H
#define SDLNETCLIENT_H

#include <sdl_net.h>
#include <stdbool.h>

#define packetSize 1024

/*(make IP addresses and p#connected to one ADT struct for the sake of scaling posibilities)*/

SDLNet_SocketSet socketSet; // socket containing the essential sockets for recvieving packets
UDPsocket udpRecvSock, udpSendSock; // Recvieving and sending socket
UDPpacket *packet; // Packet that recvieves and sends
IPaddress clientAddr1, clientAddr2; // Address struct of both clients
bool p1Connected; // if player 1 is connected or not
bool p2Connected; // if player 2 is connected or not

void initUdpServer(); // init sdlnet, open sockets,  alloc packet, resolve host, creates Socketset.
void findClients(); // finds clients and assigns their ip to IPaddress struct.
void serverLoop(); // main server loop
void closeServer(); // frees up allocated memory and quits

#endif#