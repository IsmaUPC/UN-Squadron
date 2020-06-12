#include "SceneWin.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "ModuleScene2.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include "HUD.h"
#include <SDL_mixer\include\SDL_mixer.h>

SceneWin::SceneWin(bool startEnabled) : Module(startEnabled)
{

}

SceneWin::~SceneWin()
{

}

// Load assets
bool SceneWin::Start()
{
	LOG("Loading background assets");


	bool ret = true;
	App->hud->Disable();
	App->player->Disable();
	App->level1->Disable();
	App->level2->Disable();
	bgTexture = App->textures->Load("Assets/16_Stage_Clear.png");
	App->audio->PlayMusic("Assets/16_Stage_Clear.ogg", 1.0f);
	App->render->cameraSpeed=0;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

update_status SceneWin::Update()
{
	GamePad& pad = App->input->pads[0];


	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a){
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
	App->render->Blit(bgTexture, 0, 0, NULL);
	return update_status::UPDATE_CONTINUE;
}

bool SceneWin::CleanUp()
{
	//Enable (and properly disable) the player module
	App->textures->Unload(bgTexture);
	//App->audio->Disable();

	return true;
}