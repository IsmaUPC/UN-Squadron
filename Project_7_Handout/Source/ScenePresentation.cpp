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
	for (int i = 0; i < 21; i++) {
		Presentation_Anim.PushBack({ 503 * i,0,503,443 });
		if (i == 4 || i == 12 || i == 21){
			for (int j = 0; j < 6; j++){
				Presentation_Anim.PushBack({ 503 * i,0,503,443 });
			}
		}
	}

	Presentation_Anim.speed = 0.15f;
	Presentation_Anim.loop = false;
	currentAnim = nullptr;

}

ScenePresentation::~ScenePresentation()
{

}


// Load assets
bool ScenePresentation::Start()
{
	LOG("Loading background assets");


	bool ret = true;

	bgTexture = App->textures->Load("Assets/Presentation_sprite.png");
	//App->audio->PlayMusic("Assets/01_Introduction.ogg", 1.0f);

	currentAnim = &Presentation_Anim;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

update_status ScenePresentation::Update() {
	GamePad& pad = App->input->pads[0];
	currentAnim->Update();

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

	App->render->Blit(bgTexture, 0, 0, &(currentAnim->GetCurrentFrame()));

	return update_status::UPDATE_CONTINUE;
}


bool ScenePresentation::CleanUp()
{
	//Enable (and properly disable) the player module
	App->textures->Unload(bgTexture);
	bgTexture = NULL;

	return true;
}