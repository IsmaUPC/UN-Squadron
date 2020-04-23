#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"


ModuleScene::ModuleScene(bool startEnabled) : Module(startEnabled)
{

}

ModuleScene::~ModuleScene(){
	CleanUp();
	for each (SDL_Texture* texture in bgTextures){
	App->textures->Unload(texture);

	}
	
}
// Load assets
bool ModuleScene::Start()
{
	App->player->Enable();
	App->enemies->Enable();
	App->collisions->Enable();
	//App->textures-> Enable();
	//App->audio->Enable();
	//App->textures->Init();
	

	LOG("Loading background assets");

	bool ret = true;

	bgTextures[0] = App->textures->Load("Assets/centro_1_2.png");
	bgTextures[1] = App->textures->Load("Assets/centro_2_2.png");
	bgTextures[2] = App->textures->Load("Assets/centro_3_2.png");
	bgTextures[3] = App->textures->Load("Assets/centro_4_2.png");

	App->audio->PlayMusic("Assets/EnemyAirforce.ogg", 6);

	//Bottomside collider
	//App->collisions->AddCollider({ 0, 224, 3930, 16 }, Collider::Type::WALL);
	
	// Enemies ---	
	//App->enemies->spawningEnemies(4, ENEMY_TYPE::REDSHIP, 600, 130, 100, 0);

	//	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 250, 250, 90, 1);	//WAVE 5

	App->enemies->spawningEnemies(4,ENEMY_TYPE::BROWNSHIP, 600, 135, 30, 1);	//WAVE 1
	App->enemies->spawningEnemies(4, ENEMY_TYPE::BROWNSHIP, 740, 330, 30, 2);	//WAVE 1
	App->enemies->spawningEnemies(3, ENEMY_TYPE::REDSHIP, 940, 350, 50, 3);		//WAVE 2
	App->enemies->spawningEnemies(3, ENEMY_TYPE::YELLOWSHIP, 1100, 100, 50, 4);	//WAVE 2
	App->enemies->spawningEnemies(3, ENEMY_TYPE::BLUESHIP, 1400, 100, 30, 0);	//WAVE 3
	App->enemies->spawningEnemies(3, ENEMY_TYPE::BLUESHIP, 1400, 350, 30, 1);	//WAVE 3
	App->enemies->spawningEnemies(3, ENEMY_TYPE::REDSHIP, 1650, 100, 50, 4);	//WAVE 4
	App->enemies->spawningEnemies(3, ENEMY_TYPE::YELLOWSHIP,1650, 350, 50, 3);	//WAVE 4
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 2000, 260, 90, 0);	//WAVE 5
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 2000, 200, 90, 0);	//WAVE 5
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 2020, 320, 90, 1);	//WAVE 5
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 2020, 120, 90, 2);	//WAVE 5

	
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	
	for (int i = 0; i < 4; i++){
		cont[i] = 0;
	}




	return ret;
}

update_status ModuleScene::Update(){


	App->render->camera.x += SCREEN_SPEED;
	updateBackground();

	//if (cen) {
	//}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background

update_status ModuleScene::PostUpdate(){
	
	// Draw everything --------------------------------------
	//App->render->Blit(bgTexture, 0, 0, NULL);
	
	for (int i = 0; i < 4; i++){
		App->render->Blit(bgTextures[i], SCREEN_WIDTH * cont[i], 0, NULL, i+1);
		App->render->Blit(bgTextures[i], SCREEN_WIDTH * (cont[i] + 1), 0, NULL, i+1);
		App->render->Blit(bgTextures[i], SCREEN_WIDTH * (cont[i] + 2), 0, NULL, i+1);
	}
	
	return update_status::UPDATE_CONTINUE;
}


void ModuleScene::updateBackground() {
	
	for (int i = 0; i < 4; i++){
		if (((App->render->camera.x) % ((SCREEN_WIDTH / (i+1)) + 1)) == 0) {
			cont[i]++;
		}
	}
}
bool ModuleScene::CleanUp()
{
//Enable (and properly disable) the player module
	App->player->Disable();
	App->enemies->Disable();
	App->collisions->Disable();
	//App->textures->Disable();
	//App->audio->Disable();
	
	return true;
}


