#include "SceneGameover.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneGameover::SceneGameover(bool startEnabled) : Module(startEnabled)
{

}

SceneGameover::~SceneGameover()
{

}

// Load assets
bool SceneGameover::Start()
{
	LOG("Loading background assets");



	bool ret = true;

	bgTexture = App->textures->Load("Assets/17_Game_Over.png");
	App->audio->PlayMusic("Assets/17_Game_Over.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

update_status SceneGameover::Update()
{

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneGameover::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	return update_status::UPDATE_CONTINUE;
}

bool SceneGameover::CleanUp()
{
	//Enable (and properly disable) the player module
	
	//App->textures->Unload(bgTexture);
	bgTexture = NULL;
	
	return true;
}