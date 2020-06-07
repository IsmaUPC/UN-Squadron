#ifndef __ENEMY_FINALBOSS2_H__
#define __ENEMY_FINALBOSS2_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_FinalBoss2 : public Enemy
{
public:
	Enemy_FinalBoss2(int x, int y, int _pattern);

	void Update() override;

	void move();

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation FirsAnim;
	Animation Inclined;
	Animation Down;
};

#endif // !__ENEMY_TEMPLATE_H__

