#include "ScenePresentation.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include <SDL_mixer\include\SDL_mixer.h>

ScenePresentation::ScenePresentation(bool startEnabled) : Module(startEnabled)
{

}

ScenePresentation::~ScenePresentation()
{

}


// Load assets
bool ScenePresentation::Start()
{
	LOG("Loading background assets");



	bool ret = true;

	bgTexture = App->textures->Load("Assets/Presentation.png");
	App->audio->PlayMusic("Assets/01_Introduction.ogg", 1.0f);

	App->render->camera.x, App->render->camera.y = 0;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

update_status ScenePresentation::Update() {
	GamePad& pad = App->input->pads[0];

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a) {
		Mix_HaltMusic();
		//Mix_FreeMusic(App->audio->getMusic());

		//Empezar Nivel
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 60.0f);
		//App->fade->FadeToBlack(this, (Module*)App->level2, 60.0f);
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ScenePresentation::PostUpdate()
{

	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	return update_status::UPDATE_CONTINUE;
}


bool ScenePresentation::CleanUp()
{
	//Enable (and properly disable) the player module
	App->textures->Unload(bgTexture);
	bgTexture = NULL;

	return true;
}