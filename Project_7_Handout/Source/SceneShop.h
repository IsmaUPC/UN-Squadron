#ifndef _SCENESHOP_H_
#define _SCENESHOP_H_

#include "Module.h"
#include "Animation.h"
#include"Path.h"

struct SDL_Texture;


enum class SHOP_SLOT
{
	CLUSTER,
	PHOENIX,
	FALCON,
	BULLPUP,
	S_SHELL,
	T_LASER,
	BOMB,
	NAPALM,
	GUNPOD,
	CEILING,
	MEGACRUSH,
	EXIT,

};
class SceneShop : public Module
{
public:
	//Constructor
	SceneShop(bool startEnabled);

	//Destructor
	~SceneShop();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update() override;
	bool CleanUp();

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;
	void select();

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* selectorTexture = nullptr;
	int tienda[6][2];
	int tiendaX = 0, tiendaY = 0;
	int weaponsition = 0;
	uint OptionSelection = 0;
	uint SelectWeapon = 0;
	uint InsuficientMoney = 0;
};
#endif // !_SCENESHOP_H_
