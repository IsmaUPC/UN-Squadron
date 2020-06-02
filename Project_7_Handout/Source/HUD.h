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

	void setDamage(bool _damage) { damage = _damage; };

private:

	//information of the HUD
	struct information
	{
		int* money = nullptr;
		int* score = nullptr;
		int* level = nullptr;
		int* pow = nullptr;
		int* total = nullptr;
		int* lives = nullptr;

	}info;

	SDL_Texture* hudTexture = nullptr;

	int scoreFont = 0;
	int scoreFont2 = 0;
	int hudfont = 0;

	char moneyText[10] = { "\0" };
	char scoreText[10] = { "\0" };
	char levelText[10] = { "\0" };
	char powText[10] = { "\0" };
	char totalText[10] = { "\0" };
	char livesText[10] = { "\0" };

	bool damage = false;

	//Animations image Player
	SDL_Texture* animTexturePlayer = nullptr;
	Animation* currentAnimationPlayer = nullptr;
	Animation joinInPlayer;
	Animation idlePlayer;
	Animation hitPlayer;
	Animation damagePlayer;
	Animation deadPlayer;
	
	enum anim {ENY,JOIN,IDLE,HIT,DAMAGE,DEAD};
	int animFase = ENY;
	int count = 2000;
	int countToStart = count;
	
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
};


#endif // !__HUD_H__

