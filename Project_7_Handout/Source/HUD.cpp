#include "HUD.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "ModuleInput.h"

#include "ModuleScene.h"

#include <stdio.h>

#include "SDL/include/SDL_scancode.h"

HUD::HUD(bool startEnabled) : Module(startEnabled) {
	//Animations image Player
	for (int i = 0; i < 4; i++){
		joinInPlayer.PushBack({ 0+((4+84)*i), 0, 84, 68 });
	}
	for (int i = 0; i < 8; i++) {
		joinInPlayer.PushBack({ 0 + ((4 + 84) * i), 216, 84, 68 });
	}
	joinInPlayer.speed = 0.35f;
	joinInPlayer.loop = false;
	
	for (int i = 6; i >= 0; i--) {
		deadPlayer.PushBack({ 0 + ((4 + 84) * i), 216, 84, 68 });
	}
	for (int i = 3; i >= 0; i--) {
		deadPlayer.PushBack({ 0 + ((4 + 84) * i), 0, 84, 68 });
	}
	deadPlayer.PushBack({ 0, 0, 0, 0 });
	deadPlayer.speed = 0.35f;
	deadPlayer.loop = false;

	idlePlayer.PushBack({ 0 + ((4 + 84) * 7), 216, 84, 68 });
	idlePlayer.loop = false;

	hitPlayer.PushBack({ 0 + ((4 + 84) * 8), 216, 84, 68 });
	hitPlayer.PushBack({ 0 + ((4 + 84) * 8), 288, 84, 68 });
	hitPlayer.speed = 0.2f;
	hitPlayer.loop = true;

	for (int i = 0; i < 2; i++){
		damagePlayer.PushBack({ 0 + ((4 + 84) * i), 288, 84, 68 });
	}
	damagePlayer.speed = 0.2f;
	damagePlayer.loop = true;

	currentAnimationPlayer = nullptr;
	countToStart = count/60;

	//cap Animations 
	idleCap.PushBack({ 385,39,32,30 });
	idleCap.loop = false;
	damageCap.PushBack({ 385,39,32,30 });
	damageCap.PushBack({ 451,39,32,30 });
	damageCap.speed = 0.2f;
	damageCap.loop = true;

	//BarLive Animation
	//0*384, 130*19
	idleBar.PushBack({ 132 *3,384,132,19});
	idleBar.loop = false;

	for (int i = 1; i <= 3; i++){
		damageBar.PushBack({ 132 * i,384,132,19 });
	}
	damageBar.loop = true;
	damageBar.speed = 0.2f;
	currentAnimationbar = nullptr;

	//Live Animation
	for (int i = 0; i < 8; i++){
		restoredLive.PushBack({4,388,i*17,11});
	}
	restoredLive.PushBack({ 4,388,127,11 });
	fullLive.PushBack({ 4,388,127,11 });
	restoredLive.loop = false;
	restoredLive.speed = 0.35f;

	for (int i = 7; i >= 0; i--) {
		hitLive.PushBack({ 4,388,i * 17,11 });
	}
	hitLive.loop = false;
	hitLive.speed = 0.35f;

	emptyLive.PushBack({ 4,388,0,0 });

	currentAnimationlive = nullptr;

	//weapons Animation
	for (int i = 0; i < 12; i++){
		spriteWeapons[i].PushBack({0,40*i,160,40});
		spriteWeapons[i].loop = false;
	}
	currentWeapon = nullptr;

	animFase = ENY;
}

HUD::~HUD(){

}

bool HUD::Start()
{
	bool ret = true;
	
	/*																																					//720 x 224
	scoreFont = App->fonts->Load("Assets/Fonts/FontY.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,им?!*$%&()+-/:;<=>@__     ", 5,720,224);
	scoreFont2 = App->fonts->Load("Assets/Fonts/FontG.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.,0123456789им?!*$%&()+-/:;<=>@__     ", 5, 720, 224);
	*/																																				//232 x 75
	hudfont = App->fonts->Load("Assets/hud/hud_font2.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.,0123456789им?!*$%&()+-/:;<=>@__     ", 5,235,75);

	hudTexture = App->textures->Load("Assets/hud/hud - copia.png");
	weaponsHUDTexture = App->textures->Load("Assets/hud/Guns.png");
	
	//information of the HUD
	money = App->player->getMoney();
	score = App->player->getScore();
	level = App->player->getLevel();
	pow = App->player->getPow();
	total = App->player->getTotal();
	lives = App->player->getLives();
	indexWeapon = App->player->getindeWeapon();
	godMode = App->player->getGodMode();

	for (int i = 0; i < 11; i++){
		ammo[i]= App->player->getAmmo(i);
	}


	//Animations
	animHUDTexture = App->textures->Load("Assets/hud/hudAnimations.png");

	currentAnimationcap = &idleCap;
	currentAnimationbar = &idleBar;
	currentAnimationlive = &emptyLive;
	currentWeapon = &spriteWeapons[*indexWeapon];

	hitLive.Reset();
	restoredLive.Reset();
	joinInPlayer.Reset();
	deadPlayer.Reset();
	animFase = ENY;
	countToStart = count / 30;
	return ret;
}

update_status HUD::Update() {

	/*
	if (App->input->keys[SDL_SCANCODE_H] == KEY_STATE::KEY_DOWN){
		hitOnPlayer();
	}
	if (App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_DOWN) {
		shield();
	}*/

	switch (animFase){
	case ENY:

		countToStart--;
		if (countToStart <= 0){
			countToStart = 2000/30;
			animFase = JOIN;
			currentAnimationPlayer = &joinInPlayer;
			restoredLive.Reset();
			currentAnimationlive = &restoredLive;
		}
		break;
	case JOIN:
		//currentAnimationPlayer = &joinInPlayer;
		countToStart--;
		if (countToStart <= 0) {
			countToStart = 4000/30;
			animFase = IDLE;
			currentAnimationPlayer = &idlePlayer;
			currentAnimationlive = &fullLive;
		}
		break;
	case IDLE:
		break;
	case HIT:
		countToStart--;
		if (countToStart <= 0) {
			countToStart = 5000 / 30;
			animFase = DAMAGE;
			currentAnimationPlayer = &damagePlayer;
			currentAnimationcap = &damageCap;
			currentAnimationbar = &damageBar;
			currentAnimationlive = &emptyLive;
		}
		break;
	case DAMAGE:
		break;
	case DEAD:
		currentAnimationlive = &emptyLive;
		currentAnimationbar = &idleBar;
		currentAnimationcap = &idleCap;
		currentAnimationPlayer = &deadPlayer;
		break;
	}


	return update_status::UPDATE_CONTINUE;
}


update_status HUD::PostUpdate(){

	App->render->Blit(hudTexture, 0,0, NULL, 0,false);

	sprintf_s(moneyText, 10, "%7d", *money);
	sprintf_s(scoreText, 10, "%7d", *score);
	sprintf_s(powText, 5, "%3d",	*pow);
	sprintf_s(totalText, 5, "%3d",	*total);
	sprintf_s(livesText, 5, "%3d",	*lives);
	sprintf_s(levelText, 5, "%3d",	*level);

	if (*indexWeapon != 12){
		sprintf_s(ammoText, 5, "%3d",	*ammo[*indexWeapon]);
		App->fonts->BlitText(446, 414, hudfont, ammoText);
	}
	
	if (*godMode == true){
		sprintf_s(levelText, 4, "GOD");
		App->fonts->BlitText(327, 29, hudfont, levelText);
	}else{
		App->fonts->BlitText(322, 30, hudfont, levelText);
	}


	App->fonts->BlitText(20, 61, hudfont, scoreText);
	App->fonts->BlitText(262, 61, hudfont, moneyText);
	App->fonts->BlitText(390, 61, hudfont, powText);
	App->fonts->BlitText(447, 61, hudfont, totalText);

	if (*lives < 0){
		sprintf_s(livesText, 5, "%3d", 0);
	}
		App->fonts->BlitText(54,412, hudfont, livesText);

	/*-------------------------------------------------*/
	SDL_Rect rect;
	if (animFase != ENY){
		currentAnimationPlayer->Update();
		rect = currentAnimationPlayer->GetCurrentFrame();
		App->render->Blit(animHUDTexture, 142+(App->render->camera.x), 12, &rect);
	}
	currentAnimationcap->Update();
	rect = currentAnimationcap->GetCurrentFrame();
	App->render->Blit(animHUDTexture, 30 + (App->render->camera.x),402, &rect);

	currentAnimationbar->Update();
	rect = currentAnimationbar->GetCurrentFrame();
	App->render->Blit(animHUDTexture, 110 + (App->render->camera.x), 412, &rect);

	
	currentAnimationlive->Update();
	rect = currentAnimationlive->GetCurrentFrame();
	App->render->Blit(animHUDTexture, 114 + (App->render->camera.x), 416, &rect);
	
	currentWeapon = &spriteWeapons[*indexWeapon];
	currentWeapon->Update();
	rect = currentWeapon->GetCurrentFrame();
	App->render->Blit(weaponsHUDTexture, 300 + (App->render->camera.x), 400, &rect);
	

	return update_status::UPDATE_CONTINUE;
}

bool HUD::CleanUp()
{
	
	/*App->fonts->UnLoad(scoreFont);
	App->fonts->UnLoad(scoreFont2);*/
	App->fonts->UnLoad(hudfont);
	App->textures->Unload(hudTexture);
	App->textures->Unload(animHUDTexture);
	App->textures->Unload(weaponsHUDTexture);


	return true;
}

void HUD::hitOnPlayer(){

	if (animFase == IDLE) {
		countToStart = 900 / 30;
		animFase = HIT;
		currentAnimationPlayer = &hitPlayer;
		hitLive.Reset();
		currentAnimationlive = &hitLive;
	}else if(animFase == DAMAGE){
		animFase = DEAD;
	}
}

void HUD::shield(){
	if (animFase == DAMAGE){
		animFase = IDLE;
		currentAnimationPlayer = &idlePlayer;
		currentAnimationcap = &idleCap;
		currentAnimationbar = &idleBar;
		restoredLive.Reset();
		currentAnimationlive = &restoredLive;
	}
}
