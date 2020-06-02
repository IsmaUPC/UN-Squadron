#ifndef __ENEMY_REDSHIP_H__
#define __ENEMY_REDSHIP_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_RedShip :public Enemy {

public:
	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Enemy_RedShip(int x, int y,int _pattern);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;

	void move();

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;

	// The enemy animation
	Animation fly;				//Vuela hacia la derecha
	Animation flyInvers;		//Vuela hacia la izquierda (hacia nosotros)
	Animation twistToRight;		//Efectua un giro hacaia la derecha ToUp
	Animation twistToLeft;		//Efectua una giro hacia la izquierda ToUp
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

#endif // __ENEMY_REDSHIP_H__
