#include "SceneShop.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "HUD.h"
#include <SDL_mixer\include\SDL_mixer.h>
#include <SDL\include\SDL_keyboard.h>


SceneShop::SceneShop(bool startEnabled) : Module(startEnabled)
{

}

SceneShop::~SceneShop()
{

}

bool SceneShop::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	App->hud->Disable();
	bgTexture = App->textures->Load("Assets/shop_bg.png");
	selectorTexture = App->textures->Load("Assets/selector_shop.png");
	App->audio->PlayMusic("Assets/Store.ogg", 1.0f);

	OptionSelection = App->audio->LoadFx("Assets/OptionSelection.wav");
	SelectWeapon = App->audio->LoadFx("Assets/SelectionWeapon.wav");
	InsuficientMoney = App->audio->LoadFx("Assets/InsuficientMoney.wav");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

update_status SceneShop::Update()
{
	GamePad& pad = App->input->pads[0];

	if ((App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN || pad.l_y < 0 || pad.up) && keyDownPad == false){
		tiendaY -= 1;
		if (tiendaY <0)tiendaY = 1;
		App->audio->PlayFx(OptionSelection);
		keyDownPad = true;
	}
	if ((App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_DOWN || pad.l_y > 0 || pad.down) && keyDownPad == false){
		tiendaY += 1;
		if(tiendaY>1) tiendaY = 0;
		App->audio->PlayFx(OptionSelection);
		keyDownPad = true;
	}
	if ((App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN || pad.l_x < 0 || pad.left) && keyDownPad == false){
		tiendaX -= 1;
		if (tiendaX < 0) {
			tiendaX = 5;
			tiendaY += (tiendaY == 1) ? -1 : 1;
		}
		App->audio->PlayFx(OptionSelection);
		keyDownPad = true;
	}
  	if ((App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN || pad.l_x > 0 || pad.right) && keyDownPad == false){
		tiendaX += 1;
		if (tiendaX > 5) {
			tiendaX = 0;
			tiendaY += (tiendaY == 1) ? -1 : 1;
		}
		App->audio->PlayFx(OptionSelection);
		keyDownPad = true;
	}
	
	if (pad.l_y == 0 && pad.l_x == 0 && pad.up == false && pad.down == false && pad.left == false && pad.right == false) {
		keyDownPad = false;
	}

	weaponsition = tiendaX + (6 * tiendaY);
	
	
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a)
	{
		select();
	}
	LOG("Weapon Position %d \n",weaponsition);
	return update_status::UPDATE_CONTINUE;
}

bool SceneShop::CleanUp()
{
	//Enable (and properly disable) the player module
	App->textures->Unload(bgTexture);
	App->textures->Unload(selectorTexture);
	//App->audio->Disable();
	bgTexture = NULL;
	return true;
}

update_status SceneShop::PostUpdate(){
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(selectorTexture, 19+(79*tiendaX), 240+(96*tiendaY), NULL);
	return update_status::UPDATE_CONTINUE;
}

void SceneShop::select()
{
	switch ((SHOP_SLOT)weaponsition)
	{
	case SHOP_SLOT::CLUSTER:
		break;
	case SHOP_SLOT::PHOENIX:
		break;
	case SHOP_SLOT::FALCON:
		break;
	case SHOP_SLOT::BULLPUP:
		break;
	case SHOP_SLOT::S_SHELL:
		break;
	case SHOP_SLOT::T_LASER:
		break;
	case SHOP_SLOT::BOMB:
		break;
	case SHOP_SLOT::NAPALM:
		break;
	case SHOP_SLOT::GUNPOD:
		break;
	case SHOP_SLOT::CEILING:
		break;
	case SHOP_SLOT::MEGACRUSH:
		break;
	case SHOP_SLOT::EXIT:
		Mix_HaltMusic();
		App->fade->FadeToBlack(this, (Module*)App->level1, 90);
		break;
	}
}
