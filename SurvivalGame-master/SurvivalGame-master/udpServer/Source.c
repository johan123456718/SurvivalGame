#include "udpServer.h"

int main(int argc, char **argv)
{
	initUdpServer();
	serverLoop();
	closeServer();
}