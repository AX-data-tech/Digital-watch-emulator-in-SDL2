#include <stdio.h>

#include "fsm.h"

// Initialise everything to zero
void init_c(FSM* fsm)
{
	fsm->mode = 0;
	fsm->time_hour = 21;
	fsm->time_min = 31;
	fsm->time_sec = 10;
	fsm->sw_running = 0;
	fsm->sw_min = 0;
	fsm->sw_sec = 0;
	fsm->sw_milli = 0;
	fsm->base_tick = 0;
}

// Handle a tick
void tick_c(FSM* fsm, int tick, char input)
{
	// Deal with the time first
	if ((tick - fsm->base_tick) % 100 == 0)
	{
		fsm->time_sec = (fsm->time_sec + 1) % 60;
		if ((fsm->time_sec) == 0)
		{
			fsm->time_min = (fsm->time_min + 1) % 60;
			if ((fsm->time_min) == 0)
			{
				fsm->time_hour = (fsm->time_hour + 1) % 24;
			}
		}
	}

	// Deal with stopwatch switching
	if (input == 'm')
	{
		fsm->mode = (fsm->mode + 1) % 2;
	}

	// Deal with stopwatch starting and stopping
	if (input == 's' && fsm->mode == 1)
	{
		fsm->sw_running = (fsm->sw_running + 1) % 2;
	}

	// Stopwatch reset
	if (input == 'r' && fsm->mode == 1)
	{
		if (fsm->sw_running == 1)
		{
			fsm->sw_running = 0;
		}
		fsm->sw_min = 0;
		fsm->sw_sec = 0;
		fsm->sw_milli = 0;
	}

	// Deal with the stopwatch
	if (fsm->sw_running == 1)
	{
		fsm->sw_milli = (fsm->sw_milli + 1) % 100;
		if (fsm->sw_milli == 0)
		{
			fsm->sw_sec = (fsm->sw_sec + 1) % 60;
			if (fsm->sw_sec == 0)
			{
				fsm->sw_min = (fsm->sw_min + 1) % 60;
			}
		}
	}

}

// Return the current time
void get_time(const FSM* fsm, int tick)
{
	printf("%d %d %d %d %d %d %d %d %d %d\n", tick, fsm->base_tick, fsm->mode, fsm->time_hour, fsm->time_min, fsm->time_sec, fsm->sw_running, fsm->sw_min, fsm->sw_sec, fsm->sw_milli); 
}
