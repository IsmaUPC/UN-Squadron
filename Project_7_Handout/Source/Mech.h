#ifndef __MECH_H__
#define __MECH_H__

#include "Enemy.h"
#include "Path.h"

class Mech :public Enemy{

	public:

		// Constructor (x y coordinates in the world)
		// Creates animation data and the collider
		Mech(int x, int y);

		// The enemy is going to perform a sinusoidal movement
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

		// The enemy animation
		Animation walk;
		Animation walkBack;
	};

#endif // __MECH_H__