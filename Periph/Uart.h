#pragma once
# include <stdio.h>
# include <stdlib.h>
# include <termio.h>
# include <unistd.h>
# include <fcntl.h>
# include <getopt.h>
# include <time.h>
# include <errno.h>
# include <string.h>
#include <stdbool.h>

void ComInit(int argInSpeed);
void ComSetSpeed(int argInSpeed);
int ComRoutine();
void ComAddOnReceive(void* argInOnReceive);
void ComSend(void* argInData, int argInSize);
void ComExit();
