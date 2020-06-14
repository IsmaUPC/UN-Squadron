#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "HUD.h"
#include "Enemy.h"
#include "Enemy_FinalBoss1.h"
#include <SDL_mixer\include\SDL_mixer.h>


ModuleScene::ModuleScene(bool startEnabled) : Module(startEnabled)
{

}

ModuleScene::~ModuleScene(){
	
}
// Load assets
bool ModuleScene::Start(){

	App->player->Enable();
	App->hud->Enable();
	App->enemies->Enable();
	App->collisions->Enable();
	//App->textures-> Enable();
	//App->audio->Enable();
	//App->textures->Init();
	

	LOG("Loading background assets");
	bool ret = true;
	changeScene = false;
	bgTextures[0] = App->textures->Load("Assets/centro_1_2.png");
	bgTextures[1] = App->textures->Load("Assets/centro_2_2.png");
	bgTextures[2] = App->textures->Load("Assets/centro_3_2.png");
	bgTextures[3] = App->textures->Load("Assets/centro_4_2.png");

	for (int i = 0; i < 4; i++) {
		cont[i] = 0;
	}

	App->audio->PlayMusic("Assets/EnemyAirforce.ogg", 6);
	//Bottomside collider
	//App->collisions->AddCollider({ 0, 224, 3930, 16 }, Collider::Type::WALL);
	
	// Enemies ---	
	//
	//App->enemies->spawningEnemies(4,ENEMY_TYPE::BROWNSHIP, 600, 135, 30, 1);	//WAVE 1
	//App->enemies->spawningEnemies(4, ENEMY_TYPE::BROWNSHIP, 740, 330, 20, 2);	//WAVE 1
	//App->enemies->spawningEnemies(3, ENEMY_TYPE::REDSHIP, 940, 350, 40, 3);		//WAVE 2
	//App->enemies->spawningEnemies(3, ENEMY_TYPE::YELLOWSHIP, 1100, 100, 40, 4);	//WAVE 2
	//App->enemies->spawningEnemies(3, ENEMY_TYPE::BLUESHIP, 1400, 100, 30, 0);	//WAVE 3
	//App->enemies->spawningEnemies(3, ENEMY_TYPE::BLUESHIP, 1400, 350, 30, 1);	//WAVE 3
	//App->enemies->spawningEnemies(3, ENEMY_TYPE::REDSHIP, 1650, 100, 50, 4);	//WAVE 4
	//App->enemies->spawningEnemies(3, ENEMY_TYPE::YELLOWSHIP,1650, 340, 50, 3);	//WAVE 4
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 2000, 260, 90, 0);	//WAVE 5
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 2000, 200, 90, 0);	//WAVE 5
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 2020, 320, 90, 1);	//WAVE 5
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 2020, 120, 90, 2);	//WAVE 5
	//
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::MINIBOOS1, 2170, -80, 0, 0);			//MINIBOSS 2170
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::MINIBOOS1, 2750, SCREEN_HEIGHT, 0, 1);//MINIBOSS 2750
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::MINIBOOS1, 3100, -80, 0, 2);			//MINIBOSS 3100
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::MINIBOOS1, 3870, SCREEN_HEIGHT, 0, 3);	//MINIBOSS  3820
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::MINIBOOS1, 4470, SCREEN_HEIGHT, 0, 4);	//MINIBOSS 412
	//
	//App->enemies->spawningEnemies(2, ENEMY_TYPE::BLUESHIP, 2500 , 90, 30, 2);	//WAVE 6 2500
	//App->enemies->spawningEnemies(2, ENEMY_TYPE::BLUESHIP, 2500 , 350, 30, 3);	//WAVE 6 2500
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 2690 , 190, 90, 4);	//WAVE 7 2690
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 2690 , 270, 90, 3);	//WAVE 7 2690
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 2710 , 120, 90, 6);	//WAVE 7 2710
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 2720 , 320, 90, 5);	//WAVE 7 2720
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::BLUESHIP, 2900 , 150, 30, 2);	//WAVE 8 2900
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::BLUESHIP, 2880 , 350, 30, 3);	//WAVE 8 2880
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 3030, 180, 90, 4);	//WAVE 9 
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 3030, 230, 90, 3);	//WAVE 9 
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 3050, 178, 90, 7);	//WAVE 9
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 3050, 246, 90, 8);	//WAVE 9

	//App->enemies->spawningEnemies(1, ENEMY_TYPE::BLUESHIP, 3220 , 100, 30, 4);	//WAVE 10 
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::BLUESHIP, 3210 , 230, 30, 6);	//WAVE 10 
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::BLUESHIP, 3220 , 350, 30, 5);	//WAVE 10 
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 3340 , 190, 90, 4);	//WAVE 11 
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 3340 , 270, 90, 3);	//WAVE 11 
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 3360 , 120, 90, 6);	//WAVE 11 
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 3360 , 320, 90, 5);	//WAVE 11 
	//App->enemies->spawningEnemies(4, ENEMY_TYPE::BROWNSHIP, 3540 , 330, 20, 2);	//WAVE 12
	//App->enemies->spawningEnemies(3, ENEMY_TYPE::YELLOWSHIP, 3660 , 100, 35, 4);//WAVE 12
	//App->enemies->spawningEnemies(3, ENEMY_TYPE::YELLOWSHIP, 3670 , 350, 35, 3);//WAVE 12
	//App->enemies->spawningEnemies(4, ENEMY_TYPE::BROWNSHIP, 3820, 210, 20, 0);	//WAVE 13 
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::BROWNSHIP, 3930, 160, 30, 3);	//WAVE 13 Aback
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::BROWNSHIP, 3935, 150, 30, 3);	//WAVE 13 FlyInvers
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::BROWNSHIP, 3935, 200, 30, 4);	//WAVE 13 FlyDown
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::BROWNSHIP, 3940 , 160, 30, 4);	//WAVE 13 Ahead
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::BROWNSHIP, 4100, 100, 30, 3);	//WAVE 13 Aback
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::BROWNSHIP, 4105, 90, 30, 3);	//WAVE 13 FlyInvers
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::BROWNSHIP, 4105, 140, 30, 4);	//WAVE 13 FlyDown
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::BROWNSHIP, 4110, 100, 30, 4);	//WAVE 13 Ahead
	//App->enemies->spawningEnemies(4, ENEMY_TYPE::REDSHIP, 4230, 100, 20, 2);	//WAVE 13
	//App->enemies->spawningEnemies(4, ENEMY_TYPE::YELLOWSHIP, 4510, 100, 20, 2);	//WAVE 14
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::BLUESHIP, 4600, 200, 30, 7);	//WAVE 14 
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::BLUESHIP, 4620, 220, 30, 6);	//WAVE 14 
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::BLUESHIP, 4640, 200, 30, 7);	//WAVE 14 
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 4700, 260, 90, 0);	//WAVE 15
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 4700, 200, 90, 0);	//WAVE 15
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 4720, 320, 90, 1);	//WAVE 15
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 4720, 120, 90, 2);	//WAVE 15
	//
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 4950, 260, 90, 8);	//WAVE 16
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 4950, 200, 90, 7);	//WAVE 16
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 4970, 260, 90, 8);	//WAVE 16
	//App->enemies->spawningEnemies(1, ENEMY_TYPE::GREENSHIP, 4970, 200, 90, 7);	//WAVE 16
	//App->enemies->spawningEnemies(4, ENEMY_TYPE::YELLOWSHIP, 5250, 100, 20, 2);	//WAVE 17
	//App->enemies->spawningEnemies(4, ENEMY_TYPE::REDSHIP, 5250, 340, 20, 1);	//WAVE 17
	//
	int testBoss = 4800;//  4800;
	App->enemies->spawningEnemies(1, ENEMY_TYPE::BOSS1, 5700-testBoss, SCREEN_HEIGHT-90, 0, 0);	//FINAL BOSS
	
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	
	return ret;
}
update_status ModuleScene::PreUpdate(){

	return update_status::UPDATE_CONTINUE;

}
void ModuleScene::Win() {	
	//CleanUp();
	Mix_HaltMusic();
	App->fade->FadeToBlack((Module*)App->GetActualScene(), (Module*)App->sceneWin, 60);
	
}
update_status ModuleScene::Update(){

	if (App->hud->animFase >= App->hud->IDLE && !changeScene){
		if (App->input->keys[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN) {
			changeScene = true;
			App->player->CleanUp();
			Win();
		}

		if (App->input->keys[SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN) {
			changeScene = true;
			App->player->godMode = true;
			App->player->DEAD();
			App->player->CleanUp();
			Mix_HaltMusic();
			App->fade->FadeToBlack((Module*)App->GetActualScene(), (Module*)App->sceneGameover, 60);
		}
	}


	App->render->camera.x += SCREEN_SPEED;
	updateBackground();
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
	App->hud->Disable();
	//App->textures->Disable();
	//App->audio->Disable();
	App->textures->Unload(bgTextures[0]);
	App->textures->Unload(bgTextures[1]);
	App->textures->Unload(bgTextures[2]);
	App->textures->Unload(bgTextures[3]);

	for each (SDL_Texture * texture in bgTextures) {
		App->textures->Unload(texture);
	}

	App->enemies->CleanUp();

	return true;
}


