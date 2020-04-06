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

	App->audio->PlayMusic("Assets/stage1.ogg", 1.0f);

	//Bottomside collider
	/*App->collisions->AddCollider({ 0, 224, 3930, 16 }, Collider::Type::WALL);
	
	//First two columns colliders
	App->collisions->AddCollider({ 1375, 0, 111, 96 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1375, 145, 111, 96 }, Collider::Type::WALL);*/

	// Enemies ---
	/*
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 600, 80);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 625, 80);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 640, 80);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 665, 80);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 825, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 840, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 865, 100);

	App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 825, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 850, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 875, 100);

	App->enemies->AddEnemy(ENEMY_TYPE::MECH, 375, SCREEN_HEIGHT-46);
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
