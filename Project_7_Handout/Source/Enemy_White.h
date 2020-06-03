#ifndef __ENEMY_WHITE_H__
#define __ENEMY_WHITE_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_White : public Enemy
{
public:
	Enemy_White(int x, int y, int _pattern);

	void Update() override;

	void move();

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;
	int xRecorrido = 0;
	int yRecorrido = 0;
	float radio = 5;
	float angulo = 450;
	float radianes;
	float grados = 0;
	int speed = SCREEN_SPEED;
	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation FirsAnim;
	Animation Up;
	Animation Down;
};

#endif // !__ENEMY_TEMPLATE_H__
