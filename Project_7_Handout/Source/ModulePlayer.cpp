#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"

#include <stdio.h>

#include "SDL/include/SDL_scancode.h"


ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 80, 4, 68, 20 });

	// move upwards
	downAnim.PushBack({ 155, 4, 68, 24 });
	//upAnim.PushBack({ 132, 0, 32, 14 });
	upAnim.loop = false;
	upAnim.speed = 0.1f;
	

	// Move down
	upAnim.PushBack({ 5, 4, 68, 22 });
	//downAnim.PushBack({ 0, 1, 32, 14 });
	downAnim.loop = false;
	downAnim.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");


	bool ret = true;
	destroyedCountdown = 120;
	destroyed = false;
	godMode = false;
	score = 0;

	
	texture = App->textures->Load("Assets/PlayerSprites.png");
	currentAnimation = &idleAnim;

	laserFx = App->audio->LoadFx("Assets/PlayerShoot.wav");
	explosionFx = App->audio->LoadFx("Assets/explosion.wav");

	position.x = 80;
	position.y = 230;


	//FONTS
	scoreFont = App->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);
	scoreFont2 = App->fonts->Load("Assets/Fonts/rtype_font3.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 2);
	

	collider = App->collisions->AddCollider({ position.x, position.y, PLAYER_WIDTH, PLAYER_HEIGHT }, Collider::Type::PLAYER, this);


	return ret;
}

update_status ModulePlayer::Update()
{
	//Save the position camera X
	currentCameraX = App->render->camera.x;

	// Moving the player with the camera scroll
	App->player->position.x += SCREEN_SPEED;

	//Activate god mode
	if (App->input->keys[SDL_SCANCODE_G] == KEY_STATE::KEY_DOWN)
		godModeUpdate();
	

	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		//Check that the position does not exceed the screen limit :D
		if ( position.x > currentCameraX) {
			position.x -= speed;
		}
		else {
			position.x = currentCameraX;
		}
	}

	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		/*check that the player is not in a position larger than the screen size 
		  in reference to the current camera position*/
		if (position.x < (currentCameraX + (SCREEN_WIDTH  - PLAYER_WIDTH))){
			position.x += speed;
		}
		else {
			position.x = currentCameraX + (SCREEN_WIDTH - PLAYER_WIDTH);
		}
	}

	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		/*controls the limit of the position "y" in which the player is,
		taking into account the height of the player*/
		if (position.y < (SCREEN_HEIGHT - PLAYER_HEIGHT)) {
			position.y += speed;
			if (currentAnimation != &downAnim) {
				downAnim.Reset();
				currentAnimation = &downAnim;
			}
		}
		else {
			position.y = SCREEN_HEIGHT - PLAYER_HEIGHT;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		/*Does not allow movements less than 0, in case it exceeds it 
		places the player to position 0*/
		if (position.y > 0) {
			position.y -= speed;
			if (currentAnimation != &upAnim)
			{
				upAnim.Reset();
				currentAnimation = &upAnim;
			}
		}
		else {
			position.y = 0;
		}
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && cooldown == 11 && !destroyed)
	{
		App->particles->AddParticle(App->particles->playerLaser, position.x + 35, position.y+10, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(laserFx);
		cooldown--;
	}
	if (App->input->keys[SDL_SCANCODE_M] == KEY_STATE::KEY_DOWN ){
		destroyed = true;
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);
	}
	if(cooldown<11) cooldown--;
	if (cooldown == 0)cooldown = 11;
	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE)
		currentAnimation = &idleAnim;

	collider->SetPos(position.x, position.y);

	currentAnimation->Update();

	if (destroyed)
	{
		destroyedCountdown--;
		if (destroyedCountdown <= 0){
			App->fade->FadeToBlack((Module*)App->scene, (Module*)App->sceneGameover, 60);
			//return update_status::UPDATE_STOP;
		}
	}
	else if (position.x ==2050 )
	{
		App->fade->FadeToBlack((Module*)App->scene, (Module*)App->sceneWin, 60);
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	if (!destroyed){
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", score);

	//Blit the text of the score at the bottom of the screen
	
	App->fonts->BlitText(10, 10, scoreFont, scoreText);
		
	

	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false && godMode==false)
	{
		/*
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);
		*/
		App->audio->PlayFx(explosionFx);

		destroyed = true;
		collider->pendingToDelete = true;
		//App->particles->Disable();
		
	}
	

}
void ModulePlayer::godModeUpdate(){
	godMode = !godMode;

	}