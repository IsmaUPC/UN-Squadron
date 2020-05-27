#ifndef __ENEMY_BLUESHIP_H__
#define __ENEMY_BLUESHIP_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_BlueShip : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_BlueShip(int x, int y,int _pattern);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void move();

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation fly;
	Animation flyInvers;
	Animation upAnimToRight;
	Animation downAnimToRight;
	Animation upAnimToLeft;
	Animation downAnimToLeft;

	//NEW VARS
	bool startmove = false;
	float countmove = 1;

	int xRecorrido = 0;
	int yRecorrido = 0;

	int FASE = 1;
	int TOP = 250;
	int n = 0;
	float alpha = 0;
};

#endif // __ENEMY_BROWNSHIP_H__
