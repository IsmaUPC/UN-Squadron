#include "SceneWin.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "ModuleScene2.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Timer.h"
#include "ModuleCollisions.h"
#include "Animation.h"
#include "HUD.h"

#include <SDL_mixer\include\SDL_mixer.h>

SceneWin::SceneWin(bool startEnabled) : Module(startEnabled){

	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 10 && numFrames < 144; j++) {
			win_screen1.PushBack({ SCREEN_WIDTH * j,SCREEN_HEIGHT * i,SCREEN_WIDTH,SCREEN_HEIGHT });
			numFrames += 1;
		}
	win_screen1.loop = false;
	win_screen1.speed = 0.50f;
}

SceneWin::~SceneWin(){

	CleanUp();
}

// Load assets
bool SceneWin::Start()
{
	LOG("Loading background assets");

	win_screen1.Reset();
	bool ret = true;
	App->hud->Disable();
	App->player->Disable();
	App->level1->Disable();
	App->level2->Disable();
	//App->particles->Disable();

	winTexture = App->textures->Load("Assets/win_animation.png");
	App->audio->PlayMusic("Assets/16_Stage_Clear.ogg", 1.0f);
	App->render->cameraSpeed=0;


	fade = new Timer(6500);

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	return ret;
}

update_status SceneWin::Update()
{
	//currentAnim->Update();
	fade->update();

	if (fade->check()) {
		Mix_HaltMusic();
		App->fade->FadeToBlack(this, (Module*)App->sceneShop, 60);
	}


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneWin::PostUpdate()
{
	// Draw everything --------------------------------------

	App->render->Blit(winTexture, 0, 0, &(win_screen1.GetCurrentFrame()));


	return update_status::UPDATE_CONTINUE;
}

bool SceneWin::CleanUp()
{
	//Enable (and properly disable) the player module

	App->textures->Unload(winTexture);
	//App->audio->Disable();

	return true;
}