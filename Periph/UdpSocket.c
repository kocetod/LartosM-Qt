# include "UdpSocket.h"


Udp_SocketData sockets[MAX_SOCKET_COUNT];

void UdpSend(int argInSocketId, char* argInMsg, int argInMsgLength)
{
    if((argInSocketId>=0)&&(argInSocketId<MAX_SOCKET_COUNT))
    {
        if(sockets[argInSocketId].isListening==true)
        {
            sendto(sockets[argInSocketId].sockfd,argInMsg,argInMsgLength,0,(const struct sockaddr*)&(sockets[argInSocketId].clientAddr),sizeof(sockets[argInSocketId].clientAddr));
            //printf("%d",sockets[argInSocketId].clientAddr.sin_port);
        }
    }
}

void *Receive(void * argInUserData)
{
    Udp_SocketData* mySData = (Udp_SocketData*)(argInUserData);
    unsigned int clAddrSize = sizeof(mySData->clientAddr);
    while(mySData->isListening==true)
    {
        int n = recvfrom(mySData->sockfd,(char*)(&(mySData->buffer)),MAX_PACKET_SIZE, MSG_WAITALL,(struct sockaddr*)&mySData->clientAddr,&clAddrSize);
        if(n>0)
        {
            if(mySData->OnReceive!=NULL)
            {
                mySData->OnReceive(mySData);
            }
            //sendto(mySData->sockfd,"Test",4,0,(const struct sockaddr*)&(mySData->clientAddr),sizeof(mySData->clientAddr));
            //sendto(sockets[0].sockfd,"Test",4,0,(const struct sockaddr*)&(sockets[0].clientAddr),sizeof(sockets[0].clientAddr));
            //printf("%d",mySData->clientAddr.sin_port);
        }
    }
    pthread_exit(NULL);
}


void UdpSocketClearReceiveBuffer(int argInSocketId)
{
    if((argInSocketId>=0)&&(argInSocketId<MAX_SOCKET_COUNT))
    {
        Udp_SocketData mySData = sockets[argInSocketId];
        memset(&(mySData.buffer),0,MAX_PACKET_SIZE);
    }
}

int UdpCreateSocket(ushort myPort, ushort connectionPort, const char* connectionIp, void* argInOnReceive)
{
    int result = -1;
    for(int i=0;i<MAX_SOCKET_COUNT;i++)
    {
        if(sockets[i].isAllocated==false)
        {
            sockets[i].sockfd = socket(AF_INET, SOCK_DGRAM,0);
            if(sockets[i].sockfd<0)
            {
                exit(EXIT_FAILURE);
            }
            else
            {
                sockets[i].readTimeout.tv_sec = 0;
                sockets[i].readTimeout.tv_usec = 0;
                setsockopt(sockets[i].sockfd, SOL_SOCKET, SO_RCVTIMEO, &sockets[i].readTimeout, sizeof(sockets[i].readTimeout));
                memset(&sockets[i].myAddr,0,sizeof(sockets[i].myAddr));
                memset(&sockets[i].clientAddr,0,sizeof(sockets[i].clientAddr));
                sockets[i].myAddr.sin_family = AF_INET;
                sockets[i].myAddr.sin_addr.s_addr = INADDR_ANY;
                sockets[i].myAddr.sin_port =htons(myPort);
                sockets[i].clientAddr.sin_family = AF_INET;
                sockets[i].clientAddr.sin_addr.s_addr = inet_addr(connectionIp);
                sockets[i].clientAddr.sin_port =htons(connectionPort);
                int bres = bind(sockets[i].sockfd,(const struct sockaddr*)&sockets[i].myAddr,sizeof(sockets[i].myAddr));
                if(bres<0)
                {
                    exit(EXIT_FAILURE);
                }
                else
                {
                    sockets[i].OnReceive = argInOnReceive;
                    sockets[i].isListening = true;
                    sockets[i].isAllocated = true;
                    pthread_t recThr;
                    pthread_create(&recThr,NULL,&Receive,&(sockets[i]));
                    result = i;
                }
            }
            break;
        }
    }
    return result;
}


int UdpCreateSocket_Int(ushort myPort, ushort connectionPort, int connectionIp, void* argInOnReceive)
{
    int result = -1;
    for(int i=0;i<MAX_SOCKET_COUNT;i++)
    {
        if(sockets[i].isAllocated==false)
        {
            sockets[i].sockfd = socket(AF_INET, SOCK_DGRAM,0);
            if(sockets[i].sockfd<0)
            {
                exit(EXIT_FAILURE);
            }
            else
            {
                sockets[i].readTimeout.tv_sec = 0;
                sockets[i].readTimeout.tv_sec = 1000;
                setsockopt(sockets[i].sockfd, SOL_SOCKET, SO_RCVTIMEO, &sockets[i].readTimeout, sizeof(sockets[i].readTimeout));
                memset(&sockets[i].myAddr,0,sizeof(sockets[i].myAddr));
                memset(&sockets[i].clientAddr,0,sizeof(sockets[i].clientAddr));
                sockets[i].myAddr.sin_family = AF_INET;
                sockets[i].myAddr.sin_addr.s_addr = INADDR_ANY;
                sockets[i].myAddr.sin_port =htons(myPort);
                sockets[i].clientAddr.sin_family = AF_INET;
                sockets[i].clientAddr.sin_addr.s_addr = connectionIp;//inet_addr(connectionIp);
                sockets[i].clientAddr.sin_port =htons(connectionPort);
                int bres = bind(sockets[i].sockfd,(const struct sockaddr*)&sockets[i].myAddr,sizeof(sockets[i].myAddr));
                if(bres<0)
                {
                    exit(EXIT_FAILURE);
                }
                else
                {
                    sockets[i].OnReceive = argInOnReceive;
                    sockets[i].isListening = true;
                    sockets[i].isAllocated = true;
                    pthread_t recThr;
                    pthread_create(&recThr,NULL,&Receive,&(sockets[i]));
                    result = i;
                }
            }
            break;
        }
    }
    return result;
}

void UdpClose()
{
    for(int i=0;i<MAX_SOCKET_COUNT;i++)
    {
        sockets[i].isListening = false;
    }
}
