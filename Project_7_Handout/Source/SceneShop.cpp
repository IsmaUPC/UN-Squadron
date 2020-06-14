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

	for (int i = 0; i < 4; i++) {
		shopkeeperTalking.PushBack({ 140* i, 0, 140, 205 });
	}
	shopkeeperTalking.speed = 0.12f;
	shopkeeperTalking.loop = true;

	currentAnimationshopkeeper = nullptr;

	//TEXT
	//bomb
	int frames = 0;
	for (int i = 0; i < 2; i++) 
		for (int j = 0; j < 9; j++){
			frames++;
			bombText.PushBack({ 165 * j, 166*i,165,166});
			if (frames == 7){
				bombText.PushBack({ 165 * j, 166 * i,165,166 });
				bombText.PushBack({ 165 * j, 166 * i,165,166 });
			}
		}
	//sShell
	frames = 0;
	for (int i = 0; i < 5; i++) 
		for (int j = 0; j < 5; j++){
			frames++;
			sShellText.PushBack({ 165 * j, 166 * i,165,166 });
			if (frames == 10) {
				sShellText.PushBack({ 165 * j, 166 * i,165,166 });
				sShellText.PushBack({ 165 * j, 166 * i,165,166 });
			}
		}
		
	//gunPod
	frames = 0;
	for (int i = 0; i < 6; i++) 
		for (int j = 0; j < 6 && frames < 34; j++){
			frames++;
			gunPodText.PushBack({ 165 * j, 166 * i,165,166 });
			if (frames == 8) {
				gunPodText.PushBack({ 165 * j, 166 * i,165,166 });
				gunPodText.PushBack({ 165 * j, 166 * i,165,166 });
			}
		}
	//ceiling
	frames = 0;
	for (int i = 0; i < 5; i++) 
		for (int j = 0; j < 6 && frames < 27; j++){
			frames++;
			ceilingText.PushBack({ 165 * j, 166 * i,165,166 });
			if (frames == 12) {
				ceilingText.PushBack({ 165 * j, 166 * i,165,166 });
				ceilingText.PushBack({ 165 * j, 166 * i,165,166 });
			}
		}
	//thanks
	for (int j = 0; j < 5; j++) {
		thanksText.PushBack({ 165 * j, 0,165,166 });
	}
	//CantBuy
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 7; j++) {
			cantBuyText.PushBack({ 165 * j, 166 * i,165,166 });
		}
	//exit
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 5; j++) {
			exitText.PushBack({ 165 * j, 166 * i,165,166 });
		}
	//bye
	frames = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 6 && frames < 13; j++) {
			frames++;
			byeText.PushBack({ 165 * j, 166 * i,165,166 });
			if (frames == 13) {
				byeText.PushBack({ 165 * j, 166 * i,165,166 });
				byeText.PushBack({ 165 * j, 166 * i,165,166 });
			}
		}

	for (int j = 0; j < 7; j++) {
		lowMoneyText.PushBack({ 165 * j, 0,165,166 });
	}


	thanksText.speed = 0.2f;
	byeText.loop = exitText.loop = cantBuyText.loop = thanksText.loop = lowMoneyText.loop = bombText.loop = sShellText.loop = gunPodText.loop = ceilingText.loop = false;
	byeText.speed=exitText.speed=cantBuyText.speed = lowMoneyText.speed = bombText.speed = sShellText.speed = gunPodText.speed = ceilingText.speed = 0.15f;
}

SceneShop::~SceneShop()
{

}


bool SceneShop::Start(){
	
	LOG("Loading background assets");

	bool ret = true;
	bgTexture = App->textures->Load("Assets/Shop/BG_shop.png");
	selectorTexture = App->textures->Load("Assets/Shop/selector.png");

	currentTextureText = nullptr;
	Thankstexture = App->textures->Load("Assets/Shop_Text/Thanks.png");
	BombTtexture = App->textures->Load("Assets/Shop_Text/BombText.png");
	sShellTtexture = App->textures->Load("Assets/Shop_Text/SShellText.png");
	gunPodTtexture = App->textures->Load("Assets/Shop_Text/GunpodText.png");
	CeilingTtexture = App->textures->Load("Assets/Shop_Text/CeilingText.png");
	cantBuyTtexture = App->textures->Load("Assets/Shop_Text/cant_handle.png");
	exitTtexture = App->textures->Load("Assets/Shop_Text/leaving.png");
	byeTtexture = App->textures->Load("Assets/Shop_Text/be_careful.png");
	lowMoneyTtexture = App->textures->Load("Assets/Shop_Text/low_money_text.png");

	App->audio->PlayMusic("Assets/sounds/Store.ogg", 1.0f);
	
	OptionSelection = App->audio->LoadFx("Assets/sounds/OptionSelection.wav");
	SelectWeapon = App->audio->LoadFx("Assets/sounds/SelectionWeapon.wav");
	InsuficientMoney = App->audio->LoadFx("Assets/sounds/InsuficientMoney.wav");
	caching = App->audio->LoadFx("Assets/sounds/caching.wav");

	WeaponsSold = App->textures->Load("Assets/Shop/soldWeapons.png");
	//hudfont1 = App->fonts->Load("Assets/Fonts/rtypefont3.png", "!@, . / 0123456789$; < ? abcdefghijklmnopqrstuvwxyz", 2, 192, 16);
	hudfont1 = App->fonts->Load("Assets/hud/hud_font2.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.,0123456789им?!*$%&()+-/:;<=>@__     ", 5, 235, 75);

	shopkeeperTexture = App->textures->Load("Assets/Shop/shopkeeperAnim.png");


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	for (int i = 0; i < 11; i++) {
		weapons[i].selected = false;
	}

	for (int i = 0; i < 11; i++) {
		weapons[i].ammo = 0;
	}

	currentextAnimation = &byeText;
	currentextAnimation->Reset();

	currentextAnimation = nullptr;
	currentAnimationshopkeeper = &shopkeeperTalking;

	tiendaY = 0;
	tiendaX = 0;

	changeScene = false;
	block = 50;
	thaksShopKeeprCount = 0;

	loadInfo();
	return ret;
}
void SceneShop::resetAnim() {
	if (currentextAnimation != &thanksText){
		currentextAnimation->Reset();
	}
}
update_status SceneShop::PreUpdate(){

	if (block > 0){
		block--;
		return update_status::UPDATE_CONTINUE;
	}
	
	GamePad& pad = App->input->pads[0];
	//inputs
	if (!changeScene){

		if ((App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a) && keyDownPad == false) {
			keyDownPad = true;
			select();
		}
		if ((App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN || pad.l_y < -0.2f || pad.up) && keyDownPad == false) {
			tiendaY -= 1;
			if (tiendaY < 0)tiendaY = 1;
			App->audio->PlayFx(OptionSelection);

			resetAnim();
			keyDownPad = true;
		}
		if ((App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_DOWN || pad.l_y > 0.2f || pad.down) && keyDownPad == false) {
			tiendaY += 1;
			if (tiendaY > 1) tiendaY = 0;
			App->audio->PlayFx(OptionSelection);
			resetAnim();
			keyDownPad = true;
		}
		if ((App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN || pad.l_x < -0.2f || pad.left) && keyDownPad == false) {
			tiendaX -= 1;
			if (tiendaX < 0) {
				tiendaX = 5;
				tiendaY += (tiendaY == 1) ? -1 : 1;
			}
			App->audio->PlayFx(OptionSelection);
			resetAnim();
			keyDownPad = true;
		}
		if ((App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN || pad.l_x > 0.2f || pad.right) && keyDownPad == false) {
			tiendaX += 1;
			if (tiendaX > 5) {
				tiendaX = 0;
				tiendaY += (tiendaY == 1) ? -1 : 1;
			}
			App->audio->PlayFx(OptionSelection);
			resetAnim();
			keyDownPad = true;
		}
		if (!infiniteMoney && App->input->keys[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN) {
			App->audio->PlayFx(caching);
			infiniteMoney = true;
		}

		if (pad.l_y >= -0.2f && pad.l_y <= 0.2f && pad.l_x >= -0.2f && pad.l_x <= 0.2f && pad.up == false && pad.down == false && pad.left == false && pad.right == false && pad.a == false) {
			keyDownPad = false;
		}
	}

	return update_status::UPDATE_CONTINUE;

}



update_status SceneShop::Update(){
	
	weaponsition = tiendaX + (6 * tiendaY);
	
	if (infiniteMoney) {
		money += 1000;
		if (money >= 10000)
			money += 10000;
		if (money >= 100000) 
			money += 100000;
		if (money >= 9999990) {
			money = 9999990;
			if (!maxMoney){
				maxMoney = true;
			}
		}
	}

	if (changeScene && thaksShopKeeprCount < 100) {
		(newGame) ? App->fade->FadeToBlack(this, (Module*)App->fade->getLastLevel(), 90) : App->fade->FadeToBlack(this, (Module*)App->level1, 90);
		if (!newGame) newGame = true;
	}else if(changeScene){

	}

	return update_status::UPDATE_CONTINUE;
}

bool SceneShop::CleanUp(){

	saveInfo();
	Mix_HaltMusic();
	//Enable (and properly disable) the player module
	App->textures->Unload(bgTexture);
	App->textures->Unload(selectorTexture);
	App->textures->Unload(WeaponsSold);
	
	//Text
	App->textures->Unload(currentTextureText);
	App->textures->Unload(Thankstexture);
	App->textures->Unload(BombTtexture);
	App->textures->Unload(sShellTtexture);
	App->textures->Unload(gunPodTtexture);
	App->textures->Unload(CeilingTtexture);
	App->textures->Unload(cantBuyTtexture); 
	App->textures->Unload(exitTtexture);
	App->textures->Unload(byeTtexture); 
	App->textures->Unload(lowMoneyTtexture); 

	//FX
	App->audio->UnloadFx(OptionSelection);
	App->audio->UnloadFx(SelectWeapon);
	App->audio->UnloadFx(InsuficientMoney);

	//Font
	App->fonts->UnLoad(hudfont1);

	//App->audio->Disable();
	bgTexture = NULL;
	return true;
}

update_status SceneShop::PostUpdate(){
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	if (block <= 0)
		App->render->Blit(selectorTexture, 17+(79*tiendaX), 238+(96*tiendaY), NULL);

	sprintf_s(moneyText, 10, "%9d", money);
	App->fonts->BlitText(24, 219, hudfont1, moneyText);

	SDL_Rect rect;

	currentAnimationshopkeeper->Update();
	rect = currentAnimationshopkeeper->GetCurrentFrame();
	App->render->Blit(shopkeeperTexture, 193, 31, &rect);

	rect = { 0,0,64,81 };
	if (weapons[S_SHELL].selected == true) {
		App->render->Blit(WeaponsSold, 345, 250, &rect);
	}

	rect = { 0,81,64,81 };
	if (weapons[GUNPOD].selected == true) {
		App->render->Blit(WeaponsSold, 188, 345, &rect);
	}

	rect = { 0,162,64,81 };
	if (weapons[CEILING].selected == true) {
		App->render->Blit(WeaponsSold, 267, 345, &rect);
	}

	rect = { 0,243,64,81 };
	if (weapons[BOMB].selected == true) {
		App->render->Blit(WeaponsSold, 31, 345, &rect);
	}

	printTextAnimation();

	return update_status::UPDATE_CONTINUE;
}

void SceneShop::printTextAnimation(){
	
	if (thaksShopKeeprCount <= 0){
	switch (weaponsition) {
	case CLUSTER:
		//NULL
		currentTextureText = cantBuyTtexture;
		currentextAnimation = &cantBuyText;
		break;
	case PHOENIX:
		//NULL
		currentTextureText = cantBuyTtexture;
		currentextAnimation = &cantBuyText;
		break;
	case FALCON:
		//NULL
		currentTextureText = cantBuyTtexture;
		currentextAnimation = &cantBuyText;
		break;
	case BULLPUP:
		//NULL
		currentTextureText = cantBuyTtexture;
		currentextAnimation = &cantBuyText;
		break;
	case S_SHELL:
		currentTextureText = sShellTtexture;
		currentextAnimation = &sShellText;
		break;
	case T_LASER:
		//NULL
		currentTextureText = cantBuyTtexture;
		currentextAnimation = &cantBuyText;
		break;
	case BOMB:
		currentTextureText = BombTtexture;
		currentextAnimation = &bombText;
		break;
	case NAPALM:
		//NULL
		currentTextureText = cantBuyTtexture;
		currentextAnimation = &cantBuyText;
		break;
	case GUNPOD:
		currentTextureText = gunPodTtexture;
		currentextAnimation = &gunPodText;
		break;
	case CEILING:
		currentTextureText = CeilingTtexture;
		currentextAnimation = &ceilingText;
		break;
	case MEGACRUSH:
		//NULL
		currentTextureText = cantBuyTtexture;
		currentextAnimation = &cantBuyText;
		break;
	case EXIT:
		//NULL
		currentTextureText = exitTtexture;
		currentextAnimation = &exitText;
		break;
	}
	}else{
		thaksShopKeeprCount--;
	}
	

	if (currentextAnimation != nullptr) {
		currentextAnimation->Update();
		SDL_Rect rect;
		rect = currentextAnimation->GetCurrentFrame();
		App->render->Blit(currentTextureText, 312, 42, &rect);
	}
}

void SceneShop::lowMoney(){

	currentextAnimation->Reset();
	App->audio->PlayFx(InsuficientMoney);
	thaksShopKeeprCount = 80;
	currentTextureText = lowMoneyTtexture;
	currentextAnimation = &lowMoneyText;
	currentextAnimation->Reset();
}

void SceneShop::select(){

	switch (weaponsition){
	case CLUSTER:
		break;
	case PHOENIX:
		break;
	case FALCON:
		break;
	case BULLPUP:
		break;
	case S_SHELL:
		if (money >= 10000 || weapons[S_SHELL].selected == true) {
			weapons[S_SHELL].priceWeapon = 10000;
			weapons[S_SHELL].ammo = 20;
			activeSelected(S_SHELL);
		}else {
			lowMoney();
		}
		break;
	case T_LASER:
		break;
	case BOMB:
		if (money >= 5000 || weapons[BOMB].selected == true) {
			weapons[BOMB].priceWeapon = 5000;
			weapons[BOMB].ammo = 50;
			activeSelected(BOMB);
		}else{
			lowMoney();
		}
		break;
	case NAPALM:
		break;
	case GUNPOD:
		if (money >= 15000 || weapons[GUNPOD].selected == true) {
			weapons[GUNPOD].priceWeapon = 15000;
			weapons[GUNPOD].ammo = 20;
			activeSelected(GUNPOD);
		}else {
			lowMoney();
		}
		break;
	case CEILING:
		if (money >= 15000 || weapons[CEILING].selected == true) {
			weapons[CEILING].priceWeapon = 15000;
			weapons[CEILING].ammo = 50;
			activeSelected(CEILING);
		}else {
			lowMoney();
		}
		break;
	case MEGACRUSH:
		break;
	case EXIT:
		if (!newGame){
			thaksShopKeeprCount = 150;
			currentTextureText = byeTtexture;
			currentextAnimation = &byeText;
			changeScene = true;
		}else{
			thaksShopKeeprCount = 150;
			currentTextureText = byeTtexture;
			currentextAnimation = &byeText;
			changeScene = true;
		}

		break;
	}

}

void SceneShop::activeSelected(int _weapon){
	
	weapons[_weapon].selected = !weapons[_weapon].selected;

	if (weapons[_weapon].selected == true) {
		App->audio->PlayFx(SelectWeapon);
		money -= weapons[_weapon].priceWeapon;
		thaksShopKeeprCount = 80;
		currentTextureText = Thankstexture;
		currentextAnimation = &thanksText;
		currentextAnimation->Reset();
	}else{
		thaksShopKeeprCount = 0;
		weapons[_weapon].ammo = 0;
		money += weapons[_weapon].priceWeapon;
	}
}

void SceneShop::loadInfo(){

	if (begin == false){
		money = 30000;
		score = 0;
		level = 1;
		pow = 3;
		total = 0;
		lives = 2;
		damage = 1;
		infiniteMoney = false;
		maxMoney = false;
		newGame = false;
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
		SDL_RWread(f, &damage, sizeof(int), 1);
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
	SDL_RWwrite(f, &damage, sizeof(int), 1);
	for (int i = 0; i < 11; i++){
		SDL_RWwrite(f, &weapons[i].ammo, sizeof(int), 1);
	}
	SDL_RWclose(f);
}



