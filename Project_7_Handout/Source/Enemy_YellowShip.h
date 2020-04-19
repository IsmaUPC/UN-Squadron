#ifndef __ENEMY_YELLOWNSHIP_H__
#define __ENEMY_YELLOWNSHIP_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_YellowShip : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_YellowShip(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

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

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation fly;				//Vuela hacia la derecha
	Animation flyInvers;		//Vuela hacia la izquierda (hacia nosotros)
	Animation twistToRight;		//Efectua un giro hacaia la derecha
	Animation twistToLeft;		//Efectua una giro hacia la izquierda
};

#endif // __ENEMY_YELLOWSHIP_H__
