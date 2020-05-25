#ifndef __ENEMY_MINIBOSS1_H__
#define __ENEMY_MINIBOSS1_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_MiniBoss1 : public Enemy
{
public:
	Enemy_MiniBoss1(float x, float y, int _pattern);

	void Update() override;

	void move();

private:
	// The position (as ratio) in the wave at a specific moment
	float waveRatio = 0.0f;

	// The speed at which the wave ratio is increased
	float waveRatioSpeed = 0.05f;

	// The original spawning position. The wave will be calculated from that
	int spawn_y = 0;

	// The total height of the wave
	int waveHeight = 15;
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;
	int FASE = 0;
	int xRecorrido = 0;
	int yRecorrido = 0;

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation FirsAnim;
};

#endif // !__ENEMY_TEMPLATE_H__
