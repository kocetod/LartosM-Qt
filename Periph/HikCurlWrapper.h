#pragma once
#include <stdio.h>
#include "UdpSocket.h"
#include <unistd.h>
#include "SoftwareTimer.h"


void HikCurlWrapSetZoom(int argInZoom);
void HikCurlWrapSetPolarity(int argInPolarity);

void HikCurlWrapSetBrightness(int argInBrightness);
void HikCurlWrapSetContrast(int argInContrast);

void HikCurlWrapDoNUC();

void HikCurlWrapInitHikCurlWrapper();
