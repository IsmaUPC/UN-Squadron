#include "SceneGameover.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleScene.h"
#include "ModuleScene2.h"
#include "HUD.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Timer.h"
#include <SDL_mixer\include\SDL_mixer.h>

SceneGameover::SceneGameover(bool startEnabled) : Module(startEnabled){

	for (int i = 0; i < 4; i++) {
		GameOverbg.PushBack({ 503 * i,0,503,443 });
	}

	GameOverbg.speed = 0.1f;
	GameOverbg.loop = true;
}

SceneGameover::~SceneGameover(){

}

// Load assets
bool SceneGameover::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	App->hud->Disable();
	App->player->Disable();
	App->level1->Disable();
	App->level2->Disable();

	//GObgTexture = App->textures->Load("Assets/17_Game_Over.png");
	GObgTexture = App->textures->Load("Assets/GameOver.png");
	App->audio->PlayMusic("Assets/17_Game_Over.ogg", 1.0f);

	GameOvercurrentAnim = &GameOverbg;

	fade = new Timer(3500);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

update_status SceneGameover::Update(){


	fade->update();
	if (GameOvercurrentAnim != nullptr) {
		GameOvercurrentAnim->Update();
	}

	//if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a) {
	if (fade->check()){
		Mix_HaltMusic();
		App->fade->FadeToBlack(this, (Module*)App->sceneShop, 60);
	}
	
	


	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneGameover::PostUpdate(){

	// Draw everything --------------------------------------
	//App->render->Blit(GObgTexture, 0, 0, NULL);

	App->render->Blit(GObgTexture, 0, 0, NULL);
	App->render->Blit(GObgTexture, 0, 0, &(GameOvercurrentAnim->GetCurrentFrame()));

	return update_status::UPDATE_CONTINUE;
}


bool SceneGameover::CleanUp(){

	//Enable (and properly disable) the player module
	App->textures->Unload(GObgTexture);
	GObgTexture = NULL;

	return true; 
}