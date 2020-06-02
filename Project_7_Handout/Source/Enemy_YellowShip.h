#ifndef __ENEMY_YELLOWNSHIP_H__
#define __ENEMY_YELLOWNSHIP_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_YellowShip : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_YellowShip(int x, int y,int _pattern);

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
	Animation fly;				//Vuela hacia la derecha
	Animation flyInvers;		//Vuela hacia la izquierda (hacia nosotros)
	Animation twistToRight;		//Efectua un giro hacaia la derecha
	Animation twistToLeft;		//Efectua una giro hacia la izquierda
	Animation twistToRightToDown;
	Animation twistToLeftToDown;

	//NEW VARS
	int xRecorrido = 0;
	int yRecorrido = 0;
	float multiSpeed = 1.3;
	int FASE = 1;
	bool toRight = false;
	int direction = 1;
	int TOP = 0;
};

#endif // __ENEMY_YELLOWSHIP_H__
