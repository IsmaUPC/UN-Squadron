#include "ModuleScene2.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"


ModuleScene2::ModuleScene2(bool startEnabled) : Module(startEnabled)
{

}

ModuleScene2::~ModuleScene2() {
	CleanUp();
	App->textures->Unload(bgTexture);


}
// Load assets
bool ModuleScene2::Start()
{
	App->player->Enable();
	App->enemies->Enable();
	App->collisions->Enable();

	LOG("Loading background assets");

	bool ret = true;
	
	//1538 * 585
	bgTexture = App->textures->Load("Assets/BG2.png");

	cont = 0;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

update_status ModuleScene2::Update() {

	App->render->camera.x += SCREEN_SPEED;
	updateBackground();

	return update_status::UPDATE_CONTINUE;
}

void ModuleScene2::updateBackground() {


	if ((((App->render->camera.x + SCREEN_WIDTH) % 1538) == 0)) {
		cont+=1;
	}

	//move y Background
	Y_BG = -(App->player->position.y * 0.35);

}


// Update: draw background

update_status ModuleScene2::PostUpdate() {
	//1538
	// Draw everything --------------------------------------
	//App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(bgTexture, 1538 * (cont-1), Y_BG, NULL, 1.4f);
	App->render->Blit(bgTexture, 1538 * cont, Y_BG, NULL, 1.4f);
	App->render->Blit(bgTexture, 1538 * (cont+1), Y_BG, NULL, 1.4f);
	//App->render->Blit(bgTexture, 1538 * (cont-1), 0, NULL, 1);
	//App->render->Blit(bgTexture, 1538 * cont, 0, NULL, 1);

	/*
	for (int i = 0; i < N_GB; i++) {
		App->render->Blit(bgTextures[i], SCREEN_WIDTH * cont[i], 0, NULL, i + 1);
		//App->render->Blit(bgTextures[i], 1538 * cont[i], 0, NULL, 1);
		//App->render->Blit(bgTextures[i], 1538 * (cont[i] + 1), 0, NULL, 1);
	}*/

	

	return update_status::UPDATE_CONTINUE;
}

bool ModuleScene2::CleanUp()
{
	//Enable (and properly disable) the player module
	App->player->Disable();
	App->enemies->Disable();
	App->collisions->Disable();
	//App->textures->Disable();
	//App->audio->Disable();

	App->textures->Unload(bgTexture);


	return true;
}


