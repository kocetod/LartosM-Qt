#pragma once
#include <sys/time.h>
#include "UdpSocket.h"
#include "SoftwareTimer.h"
#include "Configuration/ReadConfig.h"


bool AddIsnPacketProvider(void* argInPacketProviderFunction);
bool AddIsnPacketReceiver(void* argInPacketReceiverFunction);
void IsnInit();
