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

	// The enemy animation
	Animation fly;				//Vuela hacia la derecha
	Animation flyInvers;		//Vuela hacia la izquierda (hacia nosotros)
	Animation twistToRight;		//Efectua un giro hacaia la derecha ToUp
	Animation twistToLeft;		//Efectua una giro hacia la izquierda ToUp
	Animation twistToRightToDown;
	Animation twistToLeftToDown;


	//NEW VARS
	bool startmove = false;
	float countmove = 1;

	int xRecorrido = 0;
	int yRecorrido = 0;

	int FASE = 1;

	int n = 0;
	float alpha = 0;

};

#endif // __ENEMY_REDSHIP_H__
