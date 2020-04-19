#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"

ModuleScene::ModuleScene()
{

}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTextures[0] = App->textures->Load("Assets/centro_1_2.png");
	bgTextures[1] = App->textures->Load("Assets/centro_2_2.png");
	bgTextures[2] = App->textures->Load("Assets/centro_3_2.png");
	bgTextures[3] = App->textures->Load("Assets/centro_4_2.png");

	App->audio->PlayMusic("Assets/EnemyAirforce.ogg", 1.0f);

	//Bottomside collider
	//App->collisions->AddCollider({ 0, 224, 3930, 16 }, Collider::Type::WALL);
	

	// Enemies ---
	

	App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 600, 130);
	App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 700, 130);
	App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 800, 130);
	App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 900, 130);
	
	App->enemies->AddEnemy(ENEMY_TYPE::REDSHIP, 600, 180);
	App->enemies->AddEnemy(ENEMY_TYPE::REDSHIP, 700, 180);
	App->enemies->AddEnemy(ENEMY_TYPE::REDSHIP, 800, 180);
	App->enemies->AddEnemy(ENEMY_TYPE::REDSHIP, 900, 180);
	
	App->enemies->AddEnemy(ENEMY_TYPE::GREENSHIP, 1200, 300);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENSHIP, 1290, 300);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENSHIP, 1380, 300);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENSHIP, 1470, 300);

	App->enemies->AddEnemy(ENEMY_TYPE::YELLOWSHIP, 1200, 150);
	App->enemies->AddEnemy(ENEMY_TYPE::YELLOWSHIP, 1290, 150);
	App->enemies->AddEnemy(ENEMY_TYPE::YELLOWSHIP, 1380, 150);
	App->enemies->AddEnemy(ENEMY_TYPE::YELLOWSHIP, 1470, 150);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUESHIP, 1200, 350);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUESHIP, 1290, 350);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUESHIP, 1380, 200);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUESHIP, 1470, 200);
	

	/*
	App->enemies->AddEnemy(ENEMY_TYPE::Enemy_RedShip, 375, SCREEN_HEIGHT-46);
	*/

	return ret;
}

update_status ModuleScene::Update()
{
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
