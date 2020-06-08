#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Animation.h"
#include "p2Point.h"
#include "Path.h"
#include "Timer.h"
struct Collider;
enum class status_Particle
{
	STATE_PARTICLE_IDLE,
	STATE_PARTICLE_HIT,
	STATE_PARTICLE_DEADING,
	STATE_PARTICLE_DEAD,
};
struct Particle
{
public:
	// Constructor
	Particle();

	// Copy constructor
	Particle(const Particle& p);

	// Destructor
	~Particle();

	// Called in ModuleParticles' Update
	// Handles the logic of the particle
	// Returns false when the particle reaches its lifetime
	bool Update();
	status_Particle GetStateParticle() { return stateParticle; }
	void SetStateParticle(); 
	// Sets flag for deletion and for the collider aswell
	void SetToDelete();

public:
	// Defines the position in the screen
	fPoint position;

	// Defines the speed at which the particle will move (pixels per second)
	fPoint speed;

	Path path ;
	fPoint spawnPos;
	Timer* timerHitParticle = nullptr;
	// A set of rectangle sprites
	Animation anim;

	// Defines wether the particle is alive or not
	// Particles will be set to not alive until "spawnTime" is reached
	bool isAlive = false;
	int lives = 0;
	status_Particle stateParticle;
	// Defines the amout of frames this particle has been active
	// Negative values mean the particle is waiting to be activated
	int frameCount = 0;

	// Defines the total amount of frames during which the particle will be active
	uint lifetime = 0;

	// The particle's collider
	Collider* collider = nullptr;

	// A flag for the particle removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;
};

#endif //__PARTICLE_H__