#include "Enemy_MiniBoss1.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleInput.h"


Enemy_MiniBoss1::Enemy_MiniBoss1(float x, float y, int _pattern) :Enemy(x, y, _pattern)
{
	lives = 45;
	//Animation
	FirsAnim.PushBack({ 559,299,220,80 });
	currentAnim = &FirsAnim;
	Hit.PushBack({320,299,220,80});
	Hit.loop = false;

	timerShoting= new Timer(750);
	timerState = new Timer(60);
	timerStateCollision = new Timer(2000);
	timerAnim = new Timer(100);
	collider = App->collisions->AddCollider({ 0, 0, 220, 80 }, Collider::Type::M_BOSS1, (Module*)App->enemies);   
	if(pattern!=4)position.x -= 330;
	if(pattern==4)position.x -= 420;
	
}


void Enemy_MiniBoss1::Update() {

	timerShoting->update();
	if (stateEnemy == status_Enemies::STATE_ENEMY_HIT)timerState->update();

	if (timerState->check()) stateEnemy = status_Enemies::STATE_ENEMY_IDLE;

	if (stateEnemy == status_Enemies::STATE_ENEMY_HIT_COLLISION)timerStateCollision->update();
	if (timerStateCollision->check()) stateEnemy = status_Enemies::STATE_ENEMY_IDLE;
	timerAnim->update();
	if (timerAnim->check())currentAnim = &FirsAnim;

	if (App->input->keys[SDL_SCANCODE_E] == KEY_STATE::KEY_DOWN) {
		//shotType(TypeShot::MINI_BOSS1);
		shotMissil();
	}
	move();
	//if (stateEnemy == status_Enemies::STATE_ENEMY_HIT) currentAnim = &Hit ;
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
void Enemy_MiniBoss1::OnCollision(Collider* collider) {
	
	if (collider->type == Collider::PLAYER_SHOT && stateEnemy != status_Enemies::STATE_ENEMY_HIT)lives--, stateEnemy = status_Enemies::STATE_ENEMY_HIT, currentAnim = &Hit;
	else if (collider->type == Collider::PLAYER && stateEnemy != status_Enemies::STATE_ENEMY_HIT_COLLISION)lives--, stateEnemy = status_Enemies::STATE_ENEMY_HIT_COLLISION, currentAnim = &Hit;
	if (collider->type == Collider::SW_BOMB && stateEnemy != status_Enemies::STATE_ENEMY_HIT)lives--, stateEnemy = status_Enemies::STATE_ENEMY_HIT, currentAnim = &Hit;
	if (collider->type == Collider::SW_CEILING && stateEnemy != status_Enemies::STATE_ENEMY_HIT)lives--, stateEnemy = status_Enemies::STATE_ENEMY_HIT, currentAnim = &Hit;
	if (collider->type == Collider::SW_GUNPOD && stateEnemy != status_Enemies::STATE_ENEMY_HIT)lives--, stateEnemy = status_Enemies::STATE_ENEMY_HIT, currentAnim = &Hit;
	if (collider->type == Collider::SW_S_SHELL && stateEnemy != status_Enemies::STATE_ENEMY_HIT)lives--, stateEnemy = status_Enemies::STATE_ENEMY_HIT, currentAnim = &Hit;

}
void Enemy_MiniBoss1::move() 
{
	float speedPatternX[6] = { 1.5f, 1.25f, 1, 1.25f, 0.4f, 1.5f };
	float speedPatternY[6] = { 2.f, -2.f, 2.f, -2.f, 2.f, -2.f };
	float speedPatternX2[6] = { 1.5f, 0.15f, 0.8f, 1.f, 0.6f, 0.6f };
	float speedPatternY2[6] = { -2.f, 2.f, -2.f, 2.f, -2.f, +2.f };
	float speedPatternX3[6] = { 1.2f, 1.2f, 1.3f, 1.5f, 1.f, 1.4f };
	float speedPatternY3[6] = { 2.f, -2.f, 2.f, -2.2f, 2.0f, -2.f };
	float speedPatternX4[6] = { 1.3f, 1.3f, 1.3f, 0.6f, 0.8f, 1.3f };
	float speedPatternY4[6] = { -1.6f, 1.6f, -1.6f, 1.6f, -1.6f, +1.6f };
	float speedPatternX5[6] = { 1.2f, 1.f, 0.7f, 0.7f, 0.7f, 1.3f };
	float speedPatternY5[6] = { -1.6f, 1.6f, -1.6f, 1.6f, -1.6f, +1.6f };
	int i = FASE;

	if (i != 0&& !stateShoting)stateShoting=true;

	if(stateShoting && timerShoting->check())shotMissil();

	if (collider->pendingToDelete != true)
		resizeCollider();

	switch (pattern) {
	case 0:
		if (position.y > 0) inMap = true;
		if (inMap == true) yRecorrido += 2;
		if (yRecorrido >= i * TOP && yRecorrido < (i+1) * TOP){
			position.y += speedPatternY[i];
			position.x += speedPatternX[i];
			if (yRecorrido >= ((i+1) * TOP)-2) FASE++;
			if (yRecorrido == 300) TOP = 270;
			if (yRecorrido == 1600) TOP = 300;
		}
		break;
	case 1:
		if (position.y+80 < SCREEN_HEIGHT) inMap = true;
		if (inMap == true) yRecorrido += 2;
		if (yRecorrido >= i * TOP && yRecorrido < (i + 1) * TOP)
		{
			position.y += speedPatternY2[i];
			position.x += speedPatternX2[i];
			if (yRecorrido >= ((i + 1) * TOP) - 2) FASE++;
			if (yRecorrido == 300) TOP = 270;
			if (yRecorrido == 1600) TOP = 300;
		}
		break;
	case 2:
		
		if (position.y > 0) inMap = true;
		if (inMap == true ) yRecorrido += 2 / multiSpeed;
		if (yRecorrido >= i * TOP && yRecorrido < (i + 1) * TOP)
		{
			position.y += multiSpeed * speedPatternY3[i];
			position.x += multiSpeed * speedPatternX3[i];
			if (yRecorrido >= ((i + 1) * TOP) - 2) FASE++;
			if (yRecorrido == 300) TOP = 270;
			if (yRecorrido == 1600) TOP = 300;
		}
		break;
	case 3:
		if (position.y + 80 < SCREEN_HEIGHT) inMap = true;
		if (inMap == true) yRecorrido += 1.6;
		if (yRecorrido >= i * TOP && yRecorrido < (i + 1) * TOP)
		{
			position.y += 1 * speedPatternY4[i];
			position.x += 1 * speedPatternX4[i];
			if (yRecorrido >= ((i + 1) * TOP) - 2) FASE++;
		}
		break;
	case 4:
		if (position.y + 80 < SCREEN_HEIGHT) inMap = true;
		if (inMap == true) yRecorrido += 1.6;
		if (yRecorrido >= i * TOP && yRecorrido < (i + 1) * TOP)
		{
			position.y += 1 * speedPatternY5[i];
			position.x += 1 * speedPatternX5[i];
			if (yRecorrido >= ((i + 1) * TOP) - 2) FASE++;
		}
		break;
	}
}

void Enemy_MiniBoss1::shotMissil() {
	App->particles->AddParticle(App->particles->mBoss1Shot, position.x, position.y , Collider::Type::M_BOSS1_SHOT);

}