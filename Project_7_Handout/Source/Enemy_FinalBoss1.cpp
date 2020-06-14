#include "Enemy_FinalBoss1.h"

#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "SDL_mixer/include/SDL_mixer.h"

Enemy_FinalBoss1::Enemy_FinalBoss1(int x, int y, int _pattern) :Enemy(x, y, _pattern)
{
	lives = 138; //60 fire //yotal lives=138
	timerState = new Timer(60);
	timerStateCollision = new Timer(2000);
	timerAnim = new Timer(100);
	timerBallShot = new Timer(6000);
	timerBurstShot = new Timer(150);
	timerMoabShot = new Timer(2000);

	//Animation
	FirsAnim.PushBack({ 7,10,261,160 });
	currentAnim = &FirsAnim;
	FirsAnim.speed = 0.1;

	ShootBack.PushBack({ 7,178,261,160 });
	ShootBack.PushBack({ 7,346,261,160 });
	ShootBack.PushBack({ 7,513,261,160 });
	ShootBack.loop = true;
	ShootBack.speed = 0.5;

	ShootBombs.PushBack({ 285,10,261,160 });
	ShootBombs.PushBack({ 285,178,261,160 });
	ShootBombs.PushBack({ 285,346,261,160 });
	ShootBombs.PushBack({ 285,513,261,160 });
	ShootBombs.PushBack({ 285,178,261,160 });
	ShootBombs.PushBack({ 285,10,261,160 });
	ShootBombs.loop = false;
	ShootBombs.speed = 0.08;

	//
	openWings.PushBack({ 113,32,28,91 });
	openWings.PushBack({ 390,32,28,91 });
	openWings.PushBack({ 390,200,28,91 });
	openWings.PushBack({ 390,368,28,91 });//Sale bala
	openWings.PushBack({ 390,536,28,91 });
	openWings.PushBack({ 390,368,28,91 });
	openWings.PushBack({ 390,200,28,91 });
	openWings.PushBack({ 390,200,28,91 });
	openWings.PushBack({ 390,32,28,91 });
	openWings.PushBack({ 390,32,28,91 });
	openWings.PushBack({ 113,32,28,91 });
	openWings.speed = 0.2;
	openWings.loop = false;

	for (int i = 0; i < 4; i++) {
		Burstshot.PushBack({ 0,698,40,48 });
		Burstshot.PushBack({ 40,698,40,48 });
		Burstshot.PushBack({ 80,698,40,48 });
		Burstshot.PushBack({ 120,698,40,48 });
	}

	Burstshot.speed = 1.40f;
	Burstshot.loop = true;
	//
	Hit.PushBack({ 562,513,261,160 });
	Hit.loop = false;
	Hit.speed = 0.1;

	collider = App->collisions->AddCollider({ 0, 0, 261, 60 }, Collider::Type::BOSS1, (Module*)App->enemies);

	position.x -= SCREEN_WIDTH + 280;
	App->audio->PlayMusic("Assets/sounds/Boss 1.ogg", 0);

	finalBoss1Texture = App->textures->Load("Assets/Enemies/FinalBoss1.png");

}


void Enemy_FinalBoss1::Update() {
	updateAllTimers();
	Burstshot.Update();
	openWings.Update();

	if (App->player->position.x > position.x&& App->player->position.x > position.x)pasXtoBoss = true;
	else if (App->player->position.x < position.x)pasXtoBoss = false;


	if (stateEnemy == status_Enemies::STATE_ENEMY_HIT)timerState->update();
	if (timerState->check()) stateEnemy = status_Enemies::STATE_ENEMY_IDLE;

	if (stateEnemy == status_Enemies::STATE_ENEMY_HIT_COLLISION)timerStateCollision->update();
	if (timerStateCollision->check()) stateEnemy = status_Enemies::STATE_ENEMY_IDLE;

	if (timerAnim->check())currentAnim = &FirsAnim;
	move();
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	//Draw();

}



void Enemy_FinalBoss1::updateAllTimers()
{
	timerBallShot->update();
	timerBurstShot->update();
	timerMoabShot->update();
	timerAnim->update();
}
void Enemy_FinalBoss1::OnCollision(Collider* collider) {
	if (collider->type == Collider::PLAYER_SHOT && stateEnemy != status_Enemies::STATE_ENEMY_HIT)lives--, stateEnemy = status_Enemies::STATE_ENEMY_HIT, currentAnim = &Hit;
	else if (collider->type == Collider::PLAYER && stateEnemy != status_Enemies::STATE_ENEMY_HIT_COLLISION)lives--, stateEnemy = status_Enemies::STATE_ENEMY_HIT_COLLISION, currentAnim = &Hit;

	//SW
	if (collider->type == Collider::SW_BOMB && stateEnemy != status_Enemies::STATE_ENEMY_HIT)lives--, stateEnemy = status_Enemies::STATE_ENEMY_HIT, currentAnim = &Hit;
	if (collider->type == Collider::SW_CEILING && stateEnemy != status_Enemies::STATE_ENEMY_HIT)lives--, stateEnemy = status_Enemies::STATE_ENEMY_HIT, currentAnim = &Hit;
	if (collider->type == Collider::SW_GUNPOD && stateEnemy != status_Enemies::STATE_ENEMY_HIT)lives--, stateEnemy = status_Enemies::STATE_ENEMY_HIT, currentAnim = &Hit;
	if (collider->type == Collider::SW_S_SHELL && stateEnemy != status_Enemies::STATE_ENEMY_HIT)lives--, stateEnemy = status_Enemies::STATE_ENEMY_HIT, currentAnim = &Hit;
	if (lives <= 0 && App->player->destroyed == false) App->level1->Win();
}


void Enemy_FinalBoss1::move() {

	burstShot();
	float vecX[4] = { 0.75 ,SCREEN_SPEED ,1.25 ,SCREEN_SPEED };
	float vecY[4] = { 0.55, 0, -0.55, 0 };
	if (collider->pendingToDelete != true)	collider->SetPos(position.x, position.y + ((*currentAnim).GetCurrentFrame().h / 3) - (collider->rect.h / 3));
	if (pattern > 2) {
		if (timerBallShot->check()) {
			openWings.Reset();
			openWingscount = 40;
			//ballShot(), 
			burst = 0;
		}
		if (timerMoabShot->check()) moab();

	}
	switch (pattern) {
	case 0:
		if (xRecorrido < SCREEN_WIDTH + 90)
		{
			xRecorrido += 1;
			position.y -= 0.15f;
			position.x += 1.8f;
		}
		else pattern = 1;
		break;

	case 1:
		//Quedarse quieto un momento
		if (xRecorrido < SCREEN_WIDTH + 115)
		{
			xRecorrido += SCREEN_SPEED;
			position.y = position.y;
			position.x += SCREEN_SPEED;
		}
		else pattern = 2;
		break;
	case 2:
		if (xRecorrido < SCREEN_WIDTH + 360)
		{
			xRecorrido += 1;
			position.y -= 0.55;
			position.x += 0.75;
		}
		else pattern = 3, xRecorrido = 0;
		break;
	case 3:
		//Quedarse quieto un momento
		if (xRecorrido < 25)
		{
			xRecorrido += SCREEN_SPEED;
			position.y = position.y;
			position.x += SCREEN_SPEED;
		}
		else
		{
			xRecorrido = 0;
			if (change == false)pattern = 4;
			else pattern = 5;
		}
		break;
	case 4:
		if (xRecorrido < 190)
		{
			xRecorrido += 1;
			position.y += 0.55;
			position.x += 0.78;
		}
		else xRecorrido = 0, change = true, pattern = 3;
		break;
	case 5:
		if (xRecorrido < 190)
		{
			xRecorrido += 1;
			position.y -= 0.55;
			position.x += 1.25;
		}
		else xRecorrido = 0, change = false, pattern = 3;
		break;
	}
}



void Enemy_FinalBoss1::Draw() {

	App->render->Blit(finalBoss1Texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));

	if (Burntimecount > 0) {
		Burntimecount--;
		App->render->Blit(finalBoss1Texture, position.x, position.y + 42, &(Burstshot.GetCurrentFrame()));
	}
	else {
		Burntimecount = 0;
	}

	if (openWingscount > 0) {
		openWingscount--;
		if (openWingscount == 25) {
			ballShot();
		}
		App->render->Blit(finalBoss1Texture, position.x + 107, position.y + 22, &(openWings.GetCurrentFrame()));
	}
	else {
		openWingscount = 0;
	}

}

void Enemy_FinalBoss1::ballShot() {
	App->particles->AddParticle(App->particles->ballShotBoss1, position.x + 105, position.y + 70, Collider::Type::BOSS1_SHOT_BALL);
	App->particles->AddParticle(App->particles->ballShotBoss1, position.x + 105, position.y + 10, Collider::Type::BOSS1_SHOT_BALL);
}
void Enemy_FinalBoss1::burstShot() {

	if (timerBurstShot->check() && burst < 4) {
		App->particles->AddParticle(App->particles->pBurstshotBallBoss1, position.x, position.y + 60, Collider::Type::BOSS_BURSTSHOT);
		//Insert sound here
		if (burst == 0) {
			Burntimecount = 30;
		}
		++burst;
	}


}void Enemy_FinalBoss1::moab() {
	delay = 20;
	randMoab = (rand() % 4) + 1;
	if (pasXtoBoss && App->player->position.y > position.y) {
		if ((pattern % 2) != 0) for (int i = 0; i < randMoab; i++) App->particles->AddParticle(App->particles->pMoabBoss1, position.x + 105 + (i * delay), position.y + 120 - (delay * i), Collider::Type::BOSS_MOAB, delay * i);
		else for (int i = 0; i < randMoab; i++) App->particles->AddParticle(App->particles->pMoabDownBoss1, (position.x - 15) + (i * delay), position.y + 90, Collider::Type::BOSS_MOAB, delay * i);
	}
}