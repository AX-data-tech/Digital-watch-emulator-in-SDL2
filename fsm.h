#ifndef FSM_H
#define FSM_H

typedef struct
{
	int base_tick;
	int mode;
	int time_hour;
	int time_min;
	int time_sec;
	int sw_running;
	int sw_min;
	int sw_sec;
	int sw_milli;
} FSM;

void init_c(FSM* fsm);
void tick_c(FSM* fsm, int tick, char input);
void get_time(const FSM* fsm, int tick);

#endif
