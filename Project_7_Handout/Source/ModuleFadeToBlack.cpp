#include "ModuleFadeToBlack.h"

#include "Application.h"
#include "ModuleScene.h"
#include "ModuleScene2.h"
#include "SceneIntro.h"
#include "ModulePlayer.h"
#include "SceneShop.h"
#include "SceneWin.h"
#include "ModuleRender.h"

#include "SDL/include/SDL_render.h"

ModuleFadeToBlack::ModuleFadeToBlack(bool startEnabled) : Module(startEnabled)
{
	screenRect = { 0, 0, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE };

}

ModuleFadeToBlack::~ModuleFadeToBlack()
{

}

bool ModuleFadeToBlack::Start()
{
	LOG("Preparing Fade Screen");
	// Enable blending mode for transparency
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);
	return true;
}

update_status ModuleFadeToBlack::Update()
{
	// Exit this function if we are not performing a fade
	if (currentStep == Fade_Step::NONE) return update_status::UPDATE_CONTINUE;

	if (currentStep == Fade_Step::TO_BLACK)
	{
		++frameCount;
		if (frameCount >= maxFadeFrames)
		{
			// TODO 1: Enable / disable the modules received when FadeToBlacks() gets called

			currentStep = Fade_Step::FROM_BLACK;
			moduleToDisable->Disable();
			moduleToEnable->Enable();
		}
	}
	else
	{
		--frameCount;
		if (frameCount <= 0)
		{
			currentStep = Fade_Step::NONE;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleFadeToBlack::PostUpdate()
{
	// Exit this function if we are not performing a fade
	if (currentStep == Fade_Step::NONE) return update_status::UPDATE_CONTINUE;

	float fadeRatio = (float)frameCount / (float)maxFadeFrames;

	// Render the black square with alpha on the screen
	SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, (Uint8)(fadeRatio * 255.0f));
	SDL_RenderFillRect(App->render->renderer, &screenRect);

	return update_status::UPDATE_CONTINUE;
}

bool ModuleFadeToBlack::FadeToBlack(Module* _moduleToDisable, Module* _moduleToEnable, float frames) {

	bool ret = false;

	if (_moduleToDisable == (Module*)App->level2 || _moduleToDisable == (Module*)App->level1) {
		lastLevel = _moduleToDisable;
	}

	if (_moduleToEnable == NULL && lastLevel == NULL) {
		_moduleToEnable = (Module*)App->level1;
	}



	if (_moduleToDisable == (Module*)App->sceneWin && lastLevel == (Module*)App->level2) {
		lastLevel = (Module*)App->level1;
		moduleToDisable = _moduleToDisable;
		App->sceneShop->begin = false;
		moduleToEnable = (Module*)App->sceneIntro;
	}else{

		if (_moduleToDisable == (Module*)App->sceneWin && lastLevel == (Module*)App->level1){
			lastLevel = (Module*)App->level2;
			moduleToDisable = _moduleToDisable;
			moduleToEnable = _moduleToEnable;
		}else{
			moduleToDisable = _moduleToDisable;
			moduleToEnable = _moduleToEnable;
		}
	}

	if (*App->player->getLives() < 0 && _moduleToDisable == (Module*)App->sceneGameover){
		*App->player->getLives() = 2;
		App->sceneShop->begin = false;
		moduleToDisable = _moduleToDisable;
		moduleToEnable = (Module*)App->sceneIntro;
		lastLevel = (Module*)App->level1;
	}


	App->SetActualScene(_moduleToEnable);
	// If we are already in a fade process, ignore this call
	if (currentStep == Fade_Step::NONE){

		currentStep = Fade_Step::TO_BLACK;
		frameCount = 0;
		maxFadeFrames = frames;

		// TODO 1: We need to keep track of the modules received in FadeToBlack(...)
	
		if (_moduleToEnable->IsEnabled()) {
			_moduleToEnable->Init();
		}
		ret = true;
	}

	return ret;
}