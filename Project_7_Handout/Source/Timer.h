#ifndef TIMER_H
#define TIMER_H

#include "Timer.h"
//#include "Module.h"


class Timer {
public:
	Timer(int seconds);
	~Timer() {
		delete[] this;
	};
	int ready();
	int check();
	void update();

private:
	int last_time;
	int cur_time;
	int acumulator;
	int total;
	int interval;
};



#endif // MODULE_TIMER_H

