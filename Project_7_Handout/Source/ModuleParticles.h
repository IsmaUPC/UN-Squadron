#ifndef __MODULE_PARTICLES_H__
#define __MODULE_PARTICLES_H__

#include "Module.h"

#include "Globals.h"
#include "Particle.h"
#include "Collider.h"
#include "Enemy.h"
#include "Path.h"
#include "ModuleEnemies.h"
#include "ModuleAudio.h"

#define MAX_ACTIVE_PARTICLES 64

struct SDL_Texture;
struct Collider;

class ModuleParticles : public Module
{
public:
	// Constructor
	// Initializes all the particles in the array to nullptr
	ModuleParticles(bool startEnabled);

	//Destructor
	~ModuleParticles();

	// Called when the module is activated
	// Loads the necessary textures for the particles
	bool Start() override;

	// Called at the beginning of the application loop
	// Removes all particles pending to delete
	update_status PreUpdate() override;

	// Called at the middle of the application loop
	// Iterates all the particles and calls its Update()
	// Removes any "dead" particles
	update_status Update() override;

	// Called at the end of the application loop
	// Iterates all the particles and draws them
	update_status PostUpdate() override;

	void resizeParticle(Particle* particle);

	// Called on application exit
	// Destroys all active particles left in the array
	bool CleanUp() override;

	// Called when a particle collider hits another collider
	void OnCollision(Collider* c1, Collider* c2) override;
	Particle* setShotDirection(Particle* p, int x, int y);

	void ChekParticlesDespawn(Particle* _particle);

	// Creates a new particle and adds it to the array
	// Param particle	- A template particle from which the new particle will be created
	// Param x, y		- Position x,y in the screen (upper left axis)
	// Param delay		- Delay time from the moment the function is called until the particle is displayed in screen
	Particle* AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType = Collider::Type::NONE, uint delay = 0);

	Particle* AddSWParticle(const Particle& particle, int _indexWeapon, int x, int y, Collider::Type colliderType = Collider::Type::NONE, uint delay = 0);
private:
	// Particles spritesheet loaded into an SDL Texture
	SDL_Texture* playerShotTexture = nullptr;
	SDL_Texture* playerExplosionTexture = nullptr;
	SDL_Texture* enemyShotTexture = nullptr;
	SDL_Texture* miniBoss1ShotTx = nullptr;

	float xPlayer , yPlayer = 0;
	float escalar = 0;
	float magnitudPlayer = 0;
	float magnitudEnemy = 0;
	float angulo=0;
	int velShotEnemy = 0;
	
	uint explosionFx;
	// An array to store and handle all the particles
	Particle* particles[MAX_ACTIVE_PARTICLES] = { nullptr };

public:
	//Template particle for an explosion
	Particle explosion;

	//Template particle for a laser
	Particle playerLaser;
	Particle enemyLaser;
	Particle mBoss1Shot;
	Particle explosionEnemies;
	Animation mBoss1ShotOpen;
	Animation mBoss1ShotOpening;
	Animation mBoss1ShotClose;
	Animation hit;

	int soundExplosion;

	Particle SpecialWeapon[11];
	Animation SpecialWeaponAnim[11];


	//Animation* currentAnim = nullptr;
};

#endif // !__MODULEPARTICLES_H__