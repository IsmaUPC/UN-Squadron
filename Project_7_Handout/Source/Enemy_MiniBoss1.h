#ifndef __ENEMY_MINIBOSS1_H__
#define __ENEMY_MINIBOSS1_H__

#include "Enemy.h"
#include "Path.h"
#include "Timer.h"

class Enemy_MiniBoss1 : public Enemy
{
public:
	Enemy_MiniBoss1(float x, float y, int _pattern);

	void Update() override;
	void shotMissil();

	void move();

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	int FASE = 0;
	int xRecorrido = 0;
	float yRecorrido = 0;
	bool inMap = false;
	float multiSpeed =1;
	int TOP = 300;
	bool stateShoting=false;

	Timer* timerShoting;
	Timer* timerState;
	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation FirsAnim;
	Animation Hit;
	Path path;

};

#endif // !__ENEMY_TEMPLATE_H__
