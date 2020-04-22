#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Enemy
{

public:
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
	void CleanUp();

public:
	// The current position in the world
	iPoint position;

	// The enemy's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;

protected:
	
	
	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	void  shotPattern();

	// The enemy's collider
	Collider* collider = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;
	bool isShotDone =false;
	void shotEnemy();
	int pattern = 0;

};

#endif // __ENEMY_H__