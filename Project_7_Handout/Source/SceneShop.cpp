#include "SceneShop.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "HUD.h"
#include <SDL_mixer\include\SDL_mixer.h>


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
	
	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN)
	{
		tiendaY -= 1;
		if (tiendaY <0)
		{
			tiendaY = 1;
		}
		App->audio->PlayFx(OptionSelection);
	}
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_DOWN)
	{
		tiendaY += 1;
		if(tiendaY>1)
		{
			tiendaY = 0;
		}
		App->audio->PlayFx(OptionSelection);
	}
	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN)
	{
		tiendaX -= 1;
		if (tiendaX <0)
		{
			tiendaX = 5;
		}
		App->audio->PlayFx(OptionSelection);
	}
	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN)
	{
		tiendaX += 1;
		if (tiendaX > 5)
		{
			tiendaX = 0;
		}
		App->audio->PlayFx(OptionSelection);
	}
	
	weaponsition = tiendaX + (6 * tiendaY);
	
	
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
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

update_status SceneShop::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(selectorTexture, 19+(79*tiendaX), 240+(96*tiendaY), NULL);
	return update_status::UPDATE_CONTINUE;
}

void SceneShop::select()
{
	switch (weaponsition)
	{
	case Cluster:
		break;
	case Phoenix:
		break;
	case Falcon:
		break;
	case Bullpup:
		break;
	case S_Shell:
		break;
	case T_Laser:
		break;
	case Bomb:
		break;
	case Napalm:
		break;
	case Gunpod:
		break;
	case Ceiling:
		break;
	case MegaCrush:
		break;
	case Exit:
		Mix_HaltMusic();
		App->fade->FadeToBlack(this, (Module*)App->level1, 90);
		break;
	}
}
