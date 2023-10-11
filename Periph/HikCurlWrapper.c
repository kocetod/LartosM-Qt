# include "HikCurlWrapper.h"

int myCurlSock = -1;
char curlwrapMessage[32];

void HikCurlWrapSetZoom(int argInZoom)
{
    memset(&(curlwrapMessage),0,32);
    curlwrapMessage[0] = 'Z';

    unsigned char *bytePtr=(unsigned char*)(&argInZoom);
    for(int i =0; i<4;i++)
    {
        curlwrapMessage[1+i] = bytePtr[i];
    }

    UdpSend(myCurlSock,curlwrapMessage,32);
}

void HikCurlWrapSetPolarity(int argInPolarity)
{
    memset(&(curlwrapMessage),0,32);
    curlwrapMessage[0] = 'P';

    unsigned char *bytePtr=(unsigned char*)(&argInPolarity);
    for(int i =0; i<4;i++)
    {
        curlwrapMessage[1+i] = bytePtr[i];
    }

    UdpSend(myCurlSock,curlwrapMessage,32);
}

void HikCurlWrapSetBrightness(int argInBrightness)
{
    memset(&(curlwrapMessage),0,32);
    curlwrapMessage[0] = 'B';

    unsigned char *bytePtr=(unsigned char*)(&argInBrightness);
    for(int i =0; i<4;i++)
    {
        curlwrapMessage[1+i] = bytePtr[i];
    }

    UdpSend(myCurlSock,curlwrapMessage,32);
}

void HikCurlWrapSetContrast(int argInContrast)
{
    memset(&(curlwrapMessage),0,32);
    curlwrapMessage[0] = 'C';

    unsigned char *bytePtr=(unsigned char*)(&argInContrast);
    for(int i =0; i<4;i++)
    {
        curlwrapMessage[1+i] = bytePtr[i];
    }

    UdpSend(myCurlSock,curlwrapMessage,32);
}

void HikCurlWrapDoNUC()
{
    memset(&(curlwrapMessage),0,32);
    curlwrapMessage[0] = 'N';

    UdpSend(myCurlSock,curlwrapMessage,32);
}

void HikCurlWrapOnReceive(void* argInSocketData)
{
    UdpSocketClearReceiveBuffer(myCurlSock);
}

void HikCurlWrapInitHikCurlWrapper()
{
    myCurlSock = UdpCreateSocket(17003,17002,"127.0.0.1",HikCurlWrapOnReceive);
}
