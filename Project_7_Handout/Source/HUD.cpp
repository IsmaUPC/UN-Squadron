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


	animFase = ENY;
}

HUD::~HUD(){
	CleanUp();
}

bool HUD::Start()
{
	bool ret = true;
	
																																						//720 x 224
	scoreFont = App->fonts->Load("Assets/Fonts/FontY.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,им?!*$%&()+-/:;<=>@__     ", 5,720,224);
	scoreFont2 = App->fonts->Load("Assets/Fonts/FontG.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.,0123456789им?!*$%&()+-/:;<=>@__     ", 5, 720, 224);
																																					//276 x 86
	hudfont = App->fonts->Load("Assets/hud/hud_font2.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.,0123456789им?!*$%&()+-/:;<=>@__     ", 5,235,75);

	hudTexture = App->textures->Load("Assets/hud/hud - copia.png");

	
	//information of the HUD
	info.money = App->player->getMoney();
	info.score = App->player->getScore();
	info.level = App->player->getLevel();
	info.pow = App->player->getPow();
	info.total = App->player->getTotal();
	info.lives = App->player->getLives();

	//Animations
	animTexturePlayer = App->textures->Load("Assets/hud/hudAnimations.png");

	currentAnimationcap = &idleCap;
	currentAnimationbar = &idleBar;
	currentAnimationlive = &emptyLive;

	hitLive.Reset();
	restoredLive.Reset();

	return ret;
}

update_status HUD::Update() {

	if (App->input->keys[SDL_SCANCODE_H] == KEY_STATE::KEY_DOWN){
		countToStart = 900 / 30;
		animFase = HIT;
		currentAnimationPlayer = &hitPlayer;
		hitLive.Reset();
		currentAnimationlive = &hitLive;
	}

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
		//currentAnimationPlayer = &idlePlayer;
		break;
	case HIT:
		//currentAnimationPlayer = &hitPlayer;
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
		countToStart--;
		if (countToStart <= 0) {
			animFase = IDLE;
			currentAnimationPlayer = &idlePlayer;
			currentAnimationcap = &idleCap;
			currentAnimationbar = &idleBar;
			restoredLive.Reset();
			currentAnimationlive = &restoredLive;
		}
		break;
	case DEAD:
		break;
	}
	return update_status::UPDATE_CONTINUE;
}

update_status HUD::PostUpdate(){

	App->render->Blit(hudTexture, 0,0, NULL, 0,false);

	sprintf_s(moneyText, 10, "%7d", *info.money);
	sprintf_s(scoreText, 10, "%7d", *info.score);
	sprintf_s(levelText, 5, "%3d", *info.level);
	sprintf_s(powText, 5, "%3d", *info.pow);
	sprintf_s(totalText, 5, "%3d", *info.total);
	sprintf_s(livesText, 5, "%3d", *info.lives);

	App->fonts->BlitText(20, 61, hudfont, scoreText);
	App->fonts->BlitText(262, 61, hudfont, moneyText);
	App->fonts->BlitText(322, 30, hudfont, levelText);
	App->fonts->BlitText(390, 61, hudfont, powText);
	App->fonts->BlitText(447, 61, hudfont, totalText);
	App->fonts->BlitText(54,412, hudfont, livesText);

	/*-------------------------------------------------*/
	SDL_Rect rect;
	if (animFase != ENY){
		currentAnimationPlayer->Update();
		rect = currentAnimationPlayer->GetCurrentFrame();
		App->render->Blit(animTexturePlayer, 142+(App->render->camera.x), 12, &rect);
	}
	currentAnimationcap->Update();
	rect = currentAnimationcap->GetCurrentFrame();
	App->render->Blit(animTexturePlayer, 30 + (App->render->camera.x),402, &rect);

	currentAnimationbar->Update();
	rect = currentAnimationbar->GetCurrentFrame();
	App->render->Blit(animTexturePlayer, 110 + (App->render->camera.x), 412, &rect);

	
	currentAnimationlive->Update();
	rect = currentAnimationlive->GetCurrentFrame();
	App->render->Blit(animTexturePlayer, 114 + (App->render->camera.x), 416, &rect);
	

	/*
	switch (anim){
	case JOIN:
		break;
	case IDLE:
		break;
	case HIT:
		break;
	case DAMAGE:
		break;
	case DEAD:
		break;
	default:
		break;
	}
	*/
	/*
	short int x = 200 ;
	short int y = 350 ;

	uint32_t pixel = *( ( uint32_t * )screen->pixels + y * screen->w + x ) ;

	uint8_t r ;
	uint8_t g ;
	uint8_t b ;

	SDL_GetRGB( pixel, screen->format ,  &r, &g, &b );
	*/

	return update_status::UPDATE_CONTINUE;
}

bool HUD::CleanUp()
{
	
	App->fonts->UnLoad(scoreFont);
	App->fonts->UnLoad(scoreFont2);
	App->fonts->UnLoad(hudfont);


	App->textures->Unload(hudTexture);

	return true;
}
