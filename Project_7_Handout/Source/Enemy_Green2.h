#ifndef __ENEMY_GREEN2_H__
#define __ENEMY_GREEN2_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Green2 : public Enemy
{
public:
	Enemy_Green2(int x, int y, int _pattern);

	void Update() override;

	void move();

private:
	
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;
	int xRecorrido = 0;
	int yRecorrido = 0;
	float radio = 4.8;//9
	float grados = 270;
	float radianes;
	int direction = 1;
	int following = 1;
	int TOP = 155;
	bool roundTwo = false;
	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation FirsAnim;
	Animation Up;
	Animation Down;
};

#endif // !__ENEMY_TEMPLATE_H__
