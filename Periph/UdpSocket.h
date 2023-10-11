#pragma once
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAX_PACKET_SIZE 1024
#define MAX_SOCKET_COUNT 10

typedef struct
{
    int sockfd;
    struct sockaddr_in myAddr;
    struct sockaddr_in clientAddr;
    char buffer[MAX_PACKET_SIZE];
    bool isListening;
    struct timeval readTimeout;
    bool isAllocated;
    void (*OnReceive)(void *);
} Udp_SocketData;

int UdpCreateSocket(ushort myPort, ushort connectionPort, const char* connectionIp, void* argInOnReceive);
int UdpCreateSocket_Int(ushort myPort, ushort connectionPort, int connectionIp, void* argInOnReceive);
void UdpSend(int argInSocketId, char* argInMsg, int argInMsgLength);
void UdpSocketClearReceiveBuffer(int argInSocketId);
void UdpClose();
