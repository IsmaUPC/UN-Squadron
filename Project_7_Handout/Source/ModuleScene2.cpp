#include "ModuleScene2.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"


ModuleScene2::ModuleScene2(bool startEnabled) : Module(startEnabled)
{

}

ModuleScene2::~ModuleScene2() {
	CleanUp();
	App->textures->Unload(bgTexture);


}
// Load assets
bool ModuleScene2::Start()
{
	App->player->Enable();
	App->enemies->Enable();
	App->collisions->Enable();
	LOG("Loading background assets");

	bool ret = true;
	
	//bgTexture = App->textures->Load("Assets/BG2.png");
	bgTexture = App->textures->Load("Assets/centro_1_2.png");


	if (bgTexture == nullptr)
	{
		LOG("ERROR");
	}
	
	//Music
	//App->audio->PlayMusic("Assets/EnemyAirforce.ogg", 6);

	/*
	App->enemies->spawningEnemies(4, ENEMY_TYPE::BROWNSHIP, 600, 135, 30, 1);	//WAVE 1
	App->enemies->spawningEnemies(4, ENEMY_TYPE::BROWNSHIP, 740, 330, 30, 2);	//WAVE 1
	App->enemies->spawningEnemies(3, ENEMY_TYPE::REDSHIP, 940, 350, 50, 3);		//WAVE 2
	App->enemies->spawningEnemies(3, ENEMY_TYPE::YELLOWSHIP, 1100, 100, 50, 4);	//WAVE 2
	App->enemies->spawningEnemies(3, ENEMY_TYPE::BLUESHIP, 1400, 100, 30, 0);	//WAVE 3
	App->enemies->spawningEnemies(3, ENEMY_TYPE::BLUESHIP, 1400, 350, 30, 1);	//WAVE 3
	App->enemies->spawningEnemies(3, ENEMY_TYPE::REDSHIP, 1650, 100, 50, 4);	//WAVE 4
	App->enemies->spawningEnemies(3, ENEMY_TYPE::YELLOWSHIP, 1650, 350, 50, 3);	//WAVE 4
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 2000, 260, 90, 0);	//WAVE 5
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 2000, 200, 90, 0);	//WAVE 5
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 2020, 320, 90, 1);	//WAVE 5
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 2020, 120, 90, 2);	//WAVE 5
	*/

	App->render->camera.x = 0;
	App->render->camera.y = 0;



	return ret;
}

update_status ModuleScene2::Update() {

	App->render->camera.x += SCREEN_SPEED;
	updateBackground();

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background

update_status ModuleScene2::PostUpdate() {

	// Draw everything --------------------------------------
	//App->render->Blit(bgTexture, 0, 0, NULL);

	App->render->Blit(bgTexture, 0, 0, NULL);
	

	return update_status::UPDATE_CONTINUE;
}


void ModuleScene2::updateBackground() {

}


bool ModuleScene2::CleanUp()
{
	//Enable (and properly disable) the player module
	App->player->Disable();
	App->enemies->Disable();
	App->collisions->Disable();
	//App->textures->Disable();
	//App->audio->Disable();

	App->textures->Unload(bgTexture);

	return true;
}


