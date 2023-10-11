#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/timerfd.h>
#include <pthread.h>
#include <poll.h>
#include <stdio.h>
#include <unistd.h>


typedef enum
{
    TIMER_SINGLE_SHOT = 0,
    TIMER_PERIODIC
} t_timer;

typedef void (*time_handler)(size_t timer_id, void * user_data);

int InitializeSoftwareTimerManager();
size_t StartSoftwareTimer(unsigned int interval, time_handler handler, t_timer type, void * user_data);
void StopSoftwareTimer(size_t timer_id);
void CloseSoftwareTimerManager();
