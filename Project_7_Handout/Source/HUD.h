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

	update_status PostUpdate() override;

	bool CleanUp() override;

private:

	struct informatin
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
};


#endif // !__HUD_H__

