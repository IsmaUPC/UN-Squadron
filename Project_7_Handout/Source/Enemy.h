#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"


struct SDL_Texture;
struct Collider;
enum class status_Enemies
{
	STATE_ENEMY_IDLE = 1,
	STATE_ENEMY_HIT,
	STATE_ENEMY_DEADING,
	STATE_ENEMY_DEAD,
};


class Enemy{
public:
	
	enum TypeShot {
	ENEMY_SHOT,
	MINI_BOSS1,
	};

	// Constructor
	// Saves the spawn position for later movement calculations
	Enemy::Enemy(int x, int y);
	
	Enemy(int x, int y,  int _pattern);

	// Destructor
	virtual ~Enemy();

	// Returns the enemy's collider
	const Collider* GetCollider() const;

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModuleEnemies' Update
	virtual void Draw();

	// Collision response
	// Triggers an animation and a sound fx
	virtual void OnCollision(Collider* collider);

	// Sets flag for deletion and for the collider aswell
	virtual void SetToDelete();

	void CleanUp();
	// The current position in the world
	fPoint position;

	// The enemy's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;

	// A flag for the enemy removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;
	int lives;
	
	status_Enemies stateEnemy;

protected:
	
	Animation* currentAnim = nullptr;
	
	// A ptr to the current animation

	void shotType(TypeShot typeShot= TypeShot::ENEMY_SHOT);
	void resizeCollider();
	//void setCurrentEnemyAnmi();
	// The enemy's collider
	Collider* collider = nullptr;

	// Original spawn position. Stored for movement calculations
	fPoint spawnPos;
	bool isShotDone =false;
	Timer* timerShot;
	void shotEnemy(Particle particle, Collider::Type typeCollider);
	int pattern = 0;

};

#endif // __ENEMY_H__