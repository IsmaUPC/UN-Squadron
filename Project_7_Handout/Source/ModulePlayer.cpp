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
#include "SceneShop.h"
#include "HUD.h"
#include "Timer.h"

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

ModulePlayer::~ModulePlayer(){

	if (collider != nullptr)
		collider->pendingToDelete = true;
	App->textures->Unload(texture);

	CleanUp();
}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	timer= new Timer(500);
	timerHit = new Timer(2000);
	countTimeToShield = 5000 / 30;

	bool ret = true;
	destroyedCountdown = 120;
	oneHit = false;
	destroyed = false;
	godMode = false;
	/*
	money = MONEY;
	score = SCORE;
	level = LEVEL;
	pow = POW;
	total = TOTAL;
	lives = LIVES;
	*/
	loadInfo();

	// select a Weapon for start, if exist ammo for someone
	bool noAmmo = false;
	for (int i = 0; i < 11 && noAmmo == false; i++) {
		if (ammo[i] > 0) {
			indexWeapon = i;
			noAmmo = true;
		}else {
			indexWeapon = 12;
		}
	}

	texture = App->textures->Load("Assets/PlayerSprites.png");
	currentAnimation = &idleAnim;

	laserFx = App->audio->LoadFx("Assets/PlayerShoot.wav");
	
	explosionFx = App->audio->LoadFx("Assets/10_Effect_Die.wav");

	position.x = 80;
	position.y = 230;

	collider = App->collisions->AddCollider({ position.x, position.y, PLAYER_WIDTH, PLAYER_HEIGHT }, Collider::Type::PLAYER, this);


	return ret;
}

update_status ModulePlayer::Update(){
	timerHit->update();
	if (timerHit->check())statusPlayer = status_player::STATE_IDLE;
	//Save the position camera X
	currentCameraX = App->render->camera.x;
	timer->update();
	timeRegeneration();
	// Moving the player with the camera scroll
	App->player->position.x += SCREEN_SPEED;

	//Move player with AWSD
	if (destroyed == false) {
		MovePlayer();
		SpecialWeapons();
	}
	//Update the player collider 
	collider->SetPos(position.x, position.y);

	GamePad& pad = App->input->pads[0];
	//Activate God mode
	if (App->input->keys[SDL_SCANCODE_G] == KEY_STATE::KEY_DOWN) godModeUpdate();

	//Shot Player
	if (cooldown == 11 && !destroyed) {
		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a) playerShot();
		else if (timer->ready() && timer->check()) 
		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT || pad.a) playerShot();
	}

	//Suicide Player
	if (App->input->keys[SDL_SCANCODE_M] == KEY_STATE::KEY_DOWN ){
		
		App->hud->animFase = App->hud->DEAD;
		destroyed = true;

		OnCollision(collider,collider);

		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE);
		//App->audio->PlayFx(explosionFx);
	}

	if(cooldown<11) cooldown--;
	if (cooldown == 0)cooldown = 11;


	

	currentAnimation->Update();
	if (destroyed){
		destroyedCountdown--;
		if (destroyedCountdown <= 0){
			CleanUp();
			App->fade->FadeToBlack((Module*)App->GetActualScene(), (Module*)App->sceneGameover, 60);
			//return update_status::UPDATE_STOP;
		}
	}
	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	if (!destroyed){
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2){
	if (c1 == collider && destroyed == false && godMode==false)	{
		
		if (oneHit == false){
			oneHit = true;
			App->hud->hitOnPlayer();
			statusPlayer = status_player::STATE_HIT;
		}else if(statusPlayer==status_player::STATE_IDLE){
			if (App->hud->animFase == App->hud->DAMAGE){
				App->hud->hitOnPlayer();
				destroyed = true;
				collider->pendingToDelete = true;
				App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE);
				//App->audio->PlayFx(explosionFx);
			}
		}
	}

}
void ModulePlayer::timeRegeneration(){
	if (oneHit == true){
		countTimeToShield--;
		if (countTimeToShield <=0) {
			oneHit = false;
			countTimeToShield = 5900 / 30;
			App->hud->shield();
		}
	}

}
bool ModulePlayer::CleanUp(){
	saveInfo();
	App->textures->Unload(texture);
	App->audio->UnloadFx(laserFx);
	App->audio->UnloadFx(explosionFx);
	return true;
}
void ModulePlayer::godModeUpdate(){
	godMode = !godMode;
	}

void ModulePlayer::playerShot() {
	App->particles->AddParticle(App->particles->playerLaser, position.x + 35, position.y + 10, Collider::Type::PLAYER_SHOT);
	App->audio->PlayFx(laserFx);
	cooldown--;
}

void ModulePlayer::MovePlayer() {

	GamePad& pad = App->input->pads[0];

	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT || pad.l_x < 0){
		//Check that the position does not exceed the screen limit :D
		if (position.x > currentCameraX) {
			position.x -= speed;
		}
		else position.x = currentCameraX;
	}

	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT || pad.l_x > 0){
		/*check that the player is not in a position larger than the screen size
		  in reference to the current camera position*/
		if (position.x < (currentCameraX + (SCREEN_WIDTH - PLAYER_WIDTH))) {
			position.x += speed;
		}
		else position.x = currentCameraX + (SCREEN_WIDTH - PLAYER_WIDTH);
	}

	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT || pad.l_y > 0){
		/*controls the limit of the position "y" in which the player is,
		taking into account the height of the player*/
		if (position.y < (SCREEN_HEIGHT - (PLAYER_HEIGHT + 40))) {
			position.y += speed;
			if (currentAnimation != &downAnim) {
				downAnim.Reset();
				currentAnimation = &downAnim;
			}
		} else position.y = SCREEN_HEIGHT - (PLAYER_HEIGHT + 40);
	
	}

	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT || pad.l_y < 0){
		/*Does not allow movements less than 0, in case it exceeds it
		places the player to position 0*/
		if (position.y > 82) {
			position.y -= speed;
			if (currentAnimation != &upAnim){
				upAnim.Reset();
				currentAnimation = &upAnim;
			}
		} else position.y = 82;
	}
	// If no up/down movement detected, set the current animation back to idle
	if ((App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE || pad.l_y > 0)
		&& (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE || pad.l_y < 0))
		currentAnimation = &idleAnim;


}

void ModulePlayer::SpecialWeapons(){

	if (indexWeapon != 12){

		//change weapon
		if (App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_DOWN) {
			int actualWeapon = indexWeapon;
			for (int i = actualWeapon+1; i < 11; i++){
				if (ammo[i] > 0){
					indexWeapon = i;
				}
			}
			for (int i = 0; i < actualWeapon; i++){
				if (ammo[i] > 0) {
					indexWeapon = i;
				}
			}
		}

		//use weapon
		if (App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_DOWN) {
			ammo[indexWeapon]--;

			switch (indexWeapon){
			case App->sceneShop->CLUSTER:

				break;
			case App->sceneShop->PHOENIX:

				break;
			case App->sceneShop->FALCON:

				break;
			case App->sceneShop->BULLPUP:

				break;
			case App->sceneShop->S_SHELL:

				break;
			case App->sceneShop->T_LASER:

				break;
			case App->sceneShop->BOMB:
				App->particles->AddSWParticle(App->particles->SpecialWeapon[indexWeapon], indexWeapon, position.x + 35, position.y + 10, Collider::Type::SW_BOMB);

				break;
			case App->sceneShop->NAPALM:

				break;
			case App->sceneShop->GUNPOD:

				break;
			case App->sceneShop->CEILING:

				break;
			case App->sceneShop->MEGACRUSH:

				break;
			}

			if (ammo[indexWeapon] <= 0) {
				bool noAmmo = false;
				for (int i = 0; i < 11 && noAmmo == false; i++) {
					if (ammo[i] > 0) {
						indexWeapon = i;
						noAmmo = true;
					}
					else {
						indexWeapon = 12;
					}
				}
			}
		}
	}


}

void ModulePlayer::loadInfo() {
	SDL_RWops* f = SDL_RWFromFile("INFO.txt", "r+b");

	if (f != NULL) {
		SDL_RWread(f, &money, sizeof(int), 1);
		SDL_RWread(f, &score, sizeof(int), 1);
		SDL_RWread(f, &level, sizeof(int), 1);
		SDL_RWread(f, &pow, sizeof(int), 1);
		SDL_RWread(f, &total, sizeof(int), 1);
		SDL_RWread(f, &lives, sizeof(int), 1);
		for (int i = 0; i < 11; i++) {
			SDL_RWread(f, &ammo[i], sizeof(int), 1);
		}
		SDL_RWclose(f);
	}

}

void ModulePlayer::saveInfo() {
	SDL_RWops* f = SDL_RWFromFile("INFO.txt", "w+");

	SDL_RWwrite(f, &money, sizeof(int), 1);
	SDL_RWwrite(f, &score, sizeof(int), 1);
	SDL_RWwrite(f, &level, sizeof(int), 1);
	SDL_RWwrite(f, &pow, sizeof(int), 1);
	SDL_RWwrite(f, &total, sizeof(int), 1);
	SDL_RWwrite(f, &lives, sizeof(int), 1);
	for (int i = 0; i < 11; i++) {
		SDL_RWwrite(f, &ammo[i], sizeof(int), 1);
	}

	SDL_RWclose(f);
}