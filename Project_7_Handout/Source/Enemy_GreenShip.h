#ifndef __Enemy_GreenShip_H__
#define __Enemy_GreenShip_H__

#include "Enemy.h"

class Enemy_GreenShip : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Enemy_GreenShip(int x, int y, int _pattern);

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

	// The enemy animation
	Animation fly;				//Vuela hacia la derecha
	Animation flyInvers;		//Vuela hacia la izquierda (hacia nosotros)
	Animation twistToRight;		//Efectua un giro hacaia la derecha
	Animation twistToLeft;		//Efectua una giro hacia la izquierda
	Animation loopToRight;		//Gira sobre si mismo moviendose hacia la derecha
	Animation loopToLeft;		//Gira sobre si mismo moviendose hacia la izquierda
};

#endif // __Enemy_GreenShip_H__