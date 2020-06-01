#ifndef __ENEMY_FINALBOSS1_H__
#define __ENEMY_FINALBOSS1_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleScene.h"

class Enemy_FinalBoss1 : public Enemy
{
public:
	Enemy_FinalBoss1(int x, int y, int _pattern);
	virtual void OnCollision(Collider* collider);


	void Update() override;

	void move();
	bool isDead=false;
	bool win = true;
private:
	// The position (as ratio) in the wave at a specific moment
	float waveRatio = 0.0f;

	// The speed at which the wave ratio is increased
	float waveRatioSpeed = 0.05f;

	// The original spawning position. The wave will be calculated from that
	int spawn_y = 0;

	// The total height of the wave
	int waveHeight = 15;
	float xRecorrido = 0;
	float yRecorrido = 0;
	int TOP = 90;
	int i = 3;
	bool change = false;
	//bool isAlive;
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation FirsAnim;
	Animation ShootBack;
	Animation ShootBombs;
	Animation Hit;
};

#endif // !__ENEMY_TEMPLATE_H__
