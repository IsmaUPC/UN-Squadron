#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "Timer.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	update_status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	update_status PostUpdate() override;

	void godModeUpdate();

	int* getMoney() { return &money; };
	int* getScore() { return &score; };
	int* getLevel() { return &level; };
	int* getPow() { return &pow; };
	int* getTotal() { return &total; };
	int* getLives() { return &lives; };
	void playerShot();

	void MovePlayer();
	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	void timeRegeneration();

	bool CleanUp() override;

private:
	int currentCameraX;
	Timer* timer;

	int countTimeToShield;

public:
	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	int speed = 5;
	int cooldown = 11;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	SDL_Texture* explosion = nullptr;
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleAnim;
	Animation upAnim;
	Animation downAnim;

	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;
	bool oneHit = false;
	bool godMode = false;

	// A countdown to when the player gets destroyed. After a while, the game exits
	uint destroyedCountdown = 120;

	// Sound effects indices
	uint laserFx = 0;
	uint explosionFx = 0;



	// hud information
	int money = 0;
	int score = 0;
	int level = 1;
	int pow = 0;
	int total = 0;
	int lives = 0;

};

#endif //!__MODULE_PLAYER_H__