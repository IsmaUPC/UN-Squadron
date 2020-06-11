#ifndef __HUD_H__
#define __HUD_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class HUD : public Module
{
public:

	HUD(bool startEnabled);

	~HUD();

	bool Start() override;

	update_status Update() override;

	update_status PostUpdate() override;

	bool CleanUp() override;

	//hit the player
	void hitOnPlayer();

	//the player recovers the shield
	void shield();
	enum anim { ENY, JOIN, IDLE, HIT, DAMAGE, DEAD };
	int animFase = ENY;

private:

	//information of the HUD
	int* money = nullptr;
	int* score = nullptr;
	int* level = nullptr;
	int* pow = nullptr;
	int* total = nullptr;
	int* lives = nullptr;
	int* indexWeapon = nullptr;
	int* ammo[11] = { nullptr };


	SDL_Texture* hudTexture = nullptr;

	/*int scoreFont = 0;
	int scoreFont2 = 0;*/
	int hudfont = 0;

	char moneyText[10] = { "\0" };
	char scoreText[10] = { "\0" };
	char levelText[10] = { "\0" };
	char powText[10] = { "\0" };
	char totalText[10] = { "\0" };
	char livesText[10] = { "\0" };
	char ammoText[10] = { "\0" };

	bool damage = false;

	//Animations image Player
	SDL_Texture* animHUDTexture = nullptr;
	Animation* currentAnimationPlayer = nullptr;
	Animation joinInPlayer;
	Animation idlePlayer;
	Animation hitPlayer;
	Animation damagePlayer;
	Animation deadPlayer;
	
	int count = 1000;
	int countToStart = 0;
	
	//Animations of cap
	Animation* currentAnimationcap = nullptr;
	Animation idleCap;
	Animation damageCap;

	//Animations of livebar
	Animation* currentAnimationbar = nullptr;
	Animation idleBar;
	Animation damageBar;

	Animation* currentAnimationlive = nullptr;
	Animation emptyLive;
	Animation fullLive;
	Animation hitLive;
	Animation restoredLive;

	//Special Weapon
	SDL_Texture* weaponsHUDTexture = nullptr;
	Animation* currentWeapon = nullptr;
	Animation spriteWeapons[12];
};


#endif // !__HUD_H__

