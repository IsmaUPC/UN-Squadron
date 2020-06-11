#ifndef __ENEMY_FINALBOSS1_H__
#define __ENEMY_FINALBOSS1_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleScene.h"
#include "Timer.h"

class Enemy_FinalBoss1 : public Enemy
{
public:
	Enemy_FinalBoss1(int x, int y, int _pattern);
	virtual void OnCollision(Collider* collider);
	void Update() override;
	void move();
	bool win = true;

	void ballShot();
	void burstShot();

private:

	// The total height of the wave
	int waveHeight = 15;
	float xRecorrido = 0;
	float yRecorrido = 0;
	int TOP = 90;
	int i = 3;
	bool change = false;
	int burst = 4;
	//bool isAlive;
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;
	Timer* timerState;
	Timer* timerStateCollision;//Whith player
	Timer* timerAnim;
	Timer* timerBallShot;
	Timer* timerBurstShot;
	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation FirsAnim;
	Animation ShootBack;
	Animation ShootBombs;
	Animation Hit;
};

#endif // !__ENEMY_TEMPLATE_H__
