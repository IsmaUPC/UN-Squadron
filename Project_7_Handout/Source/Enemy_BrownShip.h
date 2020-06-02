#ifndef __ENEMY_BROWNSHIP_H__
#define __ENEMY_BROWNSHIP_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_BrownShip : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_BrownShip(int x, int y,int _pattern);

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
	Animation flyDown;			//Vuela emepzando al revés
	Animation flyAhead;			//Vuela inclinado 90º (se ve toda la cabina)
	Animation flyAback;			//Vuela inclinado 270º (no se ve la cabina)
	Animation twistToRight;		//Efectua un giro hacaia la derecha
	Animation twistToLeft;		//Efectua una giro hacia la izquierda
	Animation loopToRight;		//Gira sobre si mismo moviendose hacia la derecha
	Animation loopToLeft;		//Gira sobre si mismo moviendose hacia la izquierda

	//NEW VARS

	int xRecorrido = 0;
	int yRecorrido = 0;
	float desacelaracion = 3;
	int FASE = 1;
	float angulo = 1;
	bool isTwist = false;
	bool isTwist2 = false;
	int direction = 1;
	int TOP = 100;
};

#endif // __ENEMY_BROWNSHIP_H__