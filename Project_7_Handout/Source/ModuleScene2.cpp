#include "ModuleScene2.h"

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
#include <SDL_mixer\include\SDL_mixer.h>


ModuleScene2::ModuleScene2(bool startEnabled) : Module(startEnabled)
{

}

ModuleScene2::~ModuleScene2() {

}
// Load assets
bool ModuleScene2::Start(){
	App->player->Enable();
	App->hud->Enable();
	App->enemies->Enable();
	App->collisions->Enable();

	LOG("Loading background assets\n");

	bool ret = true;
	changeScene = false;
	//1538 * 585
	bgTexture = App->textures->Load("Assets/BG2.png");

	App->audio->PlayMusic("Assets/EnemyAirforce.ogg", 6);



	// Enemies ---	
	
	App->enemies->spawningEnemies(1,ENEMY_TYPE::GREEN, 600, 340, 30, 1);	//WAVE 1
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREEN, 1440, 340, 30, 1);	//WAVE 1
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREEN, 1520, 340, 30, 1);	//WAVE 1
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREEN, 1600, 340, 30, 1);	//WAVE 1
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREEN, 1720, 340, 30, 1);	//WAVE 1
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREEN, 2100, 340, 30, 1);	//WAVE 1
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREEN, 2400, 340, 30, 1);	//WAVE 1
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREEN, 2440, 340, 30, 1);	//WAVE 1
	
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREEN, 690, 80, 30, 1);	//WAVE 2
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREEN, 950, 80, 30, 1);	//WAVE 2
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREEN, 1200, 80, 30, 1);	//WAVE 2
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREEN, 2000, 80, 30, 1);	//WAVE 2
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREEN, 2150, 80, 30, 1);	//WAVE 2
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREEN, 2250, 80, 30, 1);	//WAVE 2
	
	
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREEN, 920,-20, 30, 0);	//WAVE 3
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREEN, 1130,-20, 30, 0);	//WAVE 3
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREEN, 2050,-20, 30, 0);	//WAVE 3
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREEN, 2300,-20, 30, 0);	//WAVE 3
	App->enemies->spawningEnemies(1, ENEMY_TYPE::GREEN, 2600,-20, 30, 0);	//WAVE 3

	App->enemies->spawningEnemies(1, ENEMY_TYPE::WHITE, 940, 130, 30, 0);	//WAVE 4
	App->enemies->spawningEnemies(1, ENEMY_TYPE::WHITE, 1000, 130, 30, 0);	//WAVE 4
	App->enemies->spawningEnemies(1, ENEMY_TYPE::WHITE, 1550, 130, 30, 0);	//WAVE 4
	App->enemies->spawningEnemies(1, ENEMY_TYPE::WHITE, 1750, 130, 30, 0);	//WAVE 4
	App->enemies->spawningEnemies(1, ENEMY_TYPE::WHITE, 1850, 220, 30, 0);	//WAVE 4
	App->enemies->spawningEnemies(1, ENEMY_TYPE::WHITE, 2000, 130, 30, 0);	//WAVE 4
	
	int testBoss2 = 0;
	App->enemies->spawningEnemies(1, ENEMY_TYPE::BOSS2, 2800-testBoss2, 220, 30, 0);	//BOSS
	App->enemies->spawningEnemies(1, ENEMY_TYPE::BOSS2, 2800 - testBoss2, 300, 30, 1);	//BOSS
	App->enemies->spawningEnemies(1, ENEMY_TYPE::BOSS2, 2850 - testBoss2, 300, 30, 2);	//BOSS
	
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	moveBG1 = 0;
	moveBG2 = 1;
	loopBG = -1;
	limitBG = 0;

	return ret;
}

void ModuleScene2::Win() {
	//CleanUp();
	bosses--;
	if (bosses <= 0)
	{
		bosses = 3;
		Mix_HaltMusic();
		App->fade->FadeToBlack((Module*)App->GetActualScene(), (Module*)App->sceneWin, 60);
	}
}
update_status ModuleScene2::Update() {

	if (App->hud->animFase >= App->hud->IDLE && !changeScene) {
		if (App->input->keys[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN) {
			changeScene = true;
			App->player->CleanUp();
			bosses = 0;
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

bool ModuleScene2::CleanUp(){

	//Enable (and properly disable) the player module
	App->player->Disable();
	App->enemies->Disable();
	App->collisions->Disable();
	App->hud->Disable();
	//App->textures->Disable();
	//App->audio->Disable();
	App->textures->Unload(bgTexture);
	App->enemies->CleanUp();

	return true;
}


