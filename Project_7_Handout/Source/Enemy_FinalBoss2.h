#ifndef __ENEMY_FINALBOSS2_H__
#define __ENEMY_FINALBOSS2_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleScene2.h"
#include "Timer.h"

class Enemy_FinalBoss2 : public Enemy
{
public:
	Enemy_FinalBoss2(int x, int y, int _pattern);
	virtual void OnCollision(Collider* collider);
	bool upDown(bool Do);
	void Update() override;
	void Anim1();
	void Anim2();
	void move();
	bool win = true;
	void shotSmallBombs();
private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;
	Timer* timerState;
	Timer* timerStateCollision;//Whith player
	Timer* timerAnim;

	Timer* timerShotBombs;
	Timer* timerCadenceBombs;
	int limitBombs =8;
	int randPos=0;


	int xRecorrido = 0;
	float radio = 4;
	float radianes;
	float grados = 0;
	int angulo = 360;
	bool Do = false;
	bool UpDown = false;
	int FASE = 0;
	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation FirsAnim;
	Animation Inclined;
	Animation Down;
	Animation Hit;
};

#endif // !__ENEMY_TEMPLATE_H__

