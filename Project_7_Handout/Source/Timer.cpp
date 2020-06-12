#include "Timer.h"
#include <SDL\include\SDL_timer.h>



Timer::Timer(int miliseconds){
	interval = miliseconds;
	acumulator = 0;
	total = 0;
	cur_time =SDL_GetTicks(); 
	last_time = SDL_GetTicks()+ miliseconds*2;
}
int Timer::ready() {
	return acumulator > interval;
}

int Timer::check(){

	if (ready()){
		acumulator -= interval;
		
		return 1;
	}
	return 0;
}
void Timer::update() {
	int delta;
    	cur_time = SDL_GetTicks();
	delta = cur_time - last_time;
	total += delta;
	acumulator += delta;
	last_time = cur_time;
	if (acumulator > interval*2)
		acumulator -= interval;
	
}