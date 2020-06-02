#include "ModuleScene2.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "HUD.h"


ModuleScene2::ModuleScene2(bool startEnabled) : Module(startEnabled)
{

}

ModuleScene2::~ModuleScene2() {
	CleanUp();

}
// Load assets
bool ModuleScene2::Start()
{
	App->player->Enable();
	App->hud->Enable();
	App->enemies->Enable();
	App->collisions->Enable();

	LOG("Loading background assets\n");

	bool ret = true;
	
	//1538 * 585
	bgTexture = App->textures->Load("Assets/BG2.png");

	App->audio->PlayMusic("Assets/EnemyAirforce.ogg", 6);

	// Enemies ---	
	
	App->enemies->spawningEnemies(1,ENEMY_TYPE::GREEN, 600, 340, 30, 1);	//WAVE 1
	/*
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREEN, 600, 340, 30, 1);	//WAVE 1
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREEN, 600, 340, 30, 1);	//WAVE 1
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREEN, 600, 340, 30, 1);	//WAVE 1
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREEN, 600, 340, 30, 1);	//WAVE 1
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREEN, 600, 340, 30, 1);	//WAVE 1
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREEN, 600, 340, 30, 1);	//WAVE 1
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREEN, 600, 340, 30, 1);	//WAVE 1
	*/
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREEN, 680, 90, 30, 1);	//WAVE 1

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	moveBG1 = 0;
	moveBG2 = 1;
	loopBG = -1;
	limitBG = 0;

	return ret;
}

update_status ModuleScene2::Update() {

	App->render->camera.x += SCREEN_SPEED;
	updateBackground();
	
	limitBG = App->render->camera.x + SCREEN_WIDTH;


	return update_status::UPDATE_CONTINUE;
}

void ModuleScene2::updateBackground() {


	if ((limitBG % (1538/2)) == 0) {
		loopBG +=1;
		if (loopBG > 1){
			((loopBG % 2) == 0) ? moveBG1 += 2 : moveBG2 += 2;
		}
	}

	//move Background_y
	Y_BG = -(App->player->position.y * 0.45f) + 27;

}


// Update: draw background

update_status ModuleScene2::PostUpdate() {

	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 1538 * moveBG1, Y_BG, NULL, 2);
	App->render->Blit(bgTexture, 1538 * moveBG2, Y_BG, NULL, 2);
	//App->render->Blit(bgTexture, 1538 * (cont+1), Y_BG, NULL, 1.4f);

	

	return update_status::UPDATE_CONTINUE;
}

bool ModuleScene2::CleanUp()
{
	//Enable (and properly disable) the player module
	App->player->Disable();
	App->enemies->Disable();
	App->collisions->Disable();
	App->hud->Disable();
	//App->textures->Disable();
	//App->audio->Disable();

	App->textures->Unload(bgTexture);


	return true;
}


