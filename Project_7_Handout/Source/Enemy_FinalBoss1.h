#ifndef __ENEMY_FINALBOSS1_H__
#define __ENEMY_FINALBOSS1_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleScene.h"
#include "Timer.h"

struct SDL_Texture;

class Enemy_FinalBoss1 : public Enemy
{
public:
	Enemy_FinalBoss1(int x, int y, int _pattern);
	virtual void OnCollision(Collider* collider);
	void Update() override;
	void updateAllTimers();
	void move();
	bool win = true;

	void Draw() override;

	void ballShot();
	void burstShot();
	void moab();

private:

	// The total height of the wave
	int waveHeight = 15;
	float xRecorrido = 0;
	float yRecorrido = 0;
	int TOP = 90;
	int i = 3;
	int delay=0;
	bool change = false;
	bool pasXtoBoss = false;
	int burst = 4;
	int randMoab;

	//bool isAlive;
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;
	Timer* timerState;
	Timer* timerStateCollision;//Whith player
	Timer* timerAnim;
	Timer* timerBallShot;
	Timer* timerMoabShot;
	Timer* timerBurstShot;
	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation FirsAnim;
	Animation ShootBack;
	Animation ShootBombs;
	Animation Hit;

	SDL_Texture* finalBoss1Texture = nullptr;


	int Burntimecount = 0;
	int openWingscount = 0;

	Animation Burstshot;
	Animation openWings;


};

#endif // !__ENEMY_TEMPLATE_H__
