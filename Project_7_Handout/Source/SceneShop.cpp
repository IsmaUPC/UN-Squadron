#include "SceneShop.h"

#include "Application.h"
#include "stdio.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFonts.h"
#include "ModuleFadeToBlack.h"
#include "HUD.h"
#include "ModulePlayer.h"
#include <SDL_mixer\include\SDL_mixer.h>
#include <SDL\include\SDL_keyboard.h>


SceneShop::SceneShop(bool startEnabled) : Module(startEnabled){

}

SceneShop::~SceneShop()
{

}


bool SceneShop::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	App->hud->Disable();
	bgTexture = App->textures->Load("Assets/shop_bg2.png");
	selectorTexture = App->textures->Load("Assets/selector_shop.png");
	App->audio->PlayMusic("Assets/Store.ogg", 1.0f);

	OptionSelection = App->audio->LoadFx("Assets/OptionSelection.wav");
	SelectWeapon = App->audio->LoadFx("Assets/SelectionWeapon.wav");
	InsuficientMoney = App->audio->LoadFx("Assets/InsuficientMoney.wav");

	hudfont1 = App->fonts->Load("Assets/hud/hud_font2.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.,0123456789им?!*$%&()+-/:;<=>@__     ", 5, 235, 75);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	for (int i = 0; i < 11; i++) {
		weapons[i].selected = false;
	}

	loadInfo();
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
	saveInfo();
	//Enable (and properly disable) the player module
	App->textures->Unload(bgTexture);
	App->textures->Unload(selectorTexture);

	App->audio->UnloadFx(OptionSelection);
	App->audio->UnloadFx(SelectWeapon);
	App->audio->UnloadFx(InsuficientMoney);

	App->fonts->UnLoad(hudfont1);


	//App->audio->Disable();
	bgTexture = NULL;
	return true;
}

update_status SceneShop::PostUpdate(){
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(selectorTexture, 17+(79*tiendaX), 238+(96*tiendaY), NULL);

	sprintf_s(moneyText, 10, "%9d", money);
	App->fonts->BlitText(24, 219, hudfont1, moneyText);
	return update_status::UPDATE_CONTINUE;
}

void SceneShop::select()
{

	switch (weaponsition)
	{
	case CLUSTER:
		
		break;
	case PHOENIX:
		
		break;
	case FALCON:
		
		
		break;
	case BULLPUP:
		
		
		break;
	case S_SHELL:
		if (money > 10000) {
			weapons[S_SHELL].priceWeapon = 10000;
			weapons[S_SHELL].ammo = 5;
			activeSelected(S_SHELL);
		}
		break;
	case T_LASER:
		
		break;
	case BOMB:
		
		break;
	case NAPALM:
		
		break;
	case GUNPOD:
		if (money > 15000) {
			weapons[GUNPOD].priceWeapon = 15000;
			weapons[GUNPOD].ammo = 15;
			activeSelected(GUNPOD);
		}
		break;
	case CEILING:
		if (money > 15000) {
			weapons[CEILING].priceWeapon = 15000;
			weapons[CEILING].ammo = 10;
			activeSelected(CEILING);
		}
		break;
	case MEGACRUSH:
		
		break;
	case EXIT:

		/*for (int i = 0; i < 11; i++){
			if (weapons[i].selected == true) {
				AMMO[i] = weapons[i].ammo;
			}
		}*/

		Mix_HaltMusic();
		App->fade->FadeToBlack(this, (Module*)App->level1, 90);
		break;
	}
}

void SceneShop::activeSelected(int _weapon){
	weapons[_weapon].selected = !weapons[_weapon].selected;
	if (weapons[_weapon].selected == true) {
		money -= weapons[_weapon].priceWeapon;
	}
	else {
		money += weapons[_weapon].priceWeapon;
	}
}

void SceneShop::loadInfo(){

	if (begin == false){
		begin = true;
		return;
	}

	SDL_RWops* f = SDL_RWFromFile("INFO.txt", "r+b");

	if (f != NULL) {
		SDL_RWread(f, &money, sizeof(int), 1);
		SDL_RWread(f, &score, sizeof(int), 1);
		SDL_RWread(f, &level, sizeof(int), 1);
		SDL_RWread(f, &pow, sizeof(int), 1);
		SDL_RWread(f, &total, sizeof(int), 1);
		SDL_RWread(f, &lives, sizeof(int), 1);
		for (int i = 0; i < 11; i++) {
			SDL_RWread(f, &weapons[i].ammo, sizeof(int), 1);
		}
		SDL_RWclose(f);
	}

}

void SceneShop::saveInfo(){
	SDL_RWops* f = SDL_RWFromFile("INFO.txt", "w+");

	SDL_RWwrite(f, &money, sizeof(int), 1);
	SDL_RWwrite(f, &score, sizeof(int), 1);
	SDL_RWwrite(f, &level, sizeof(int), 1);
	SDL_RWwrite(f, &pow, sizeof(int), 1);
	SDL_RWwrite(f, &total, sizeof(int), 1);
	SDL_RWwrite(f, &lives, sizeof(int), 1);
	for (int i = 0; i < 11; i++){
		SDL_RWwrite(f, &weapons[i].ammo, sizeof(int), 1);
	}
	
	SDL_RWclose(f);
}



