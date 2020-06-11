#include "Enemy_FinalBoss1.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "SDL_mixer/include/SDL_mixer.h"
Enemy_FinalBoss1::Enemy_FinalBoss1(int x, int y, int _pattern) :Enemy(x, y, _pattern)
{
	lives = 138; //60 fire //yotal lives=138
	timerState = new Timer(60);
	timerStateCollision = new Timer(2000);
	timerAnim = new Timer(100);
	timerBallShot = new Timer(5000);
	timerBurstShot = new Timer(150);

	//Animation
	FirsAnim.PushBack({ 7,10,261,160 });
	currentAnim = &FirsAnim;
	FirsAnim.speed = 0.1;

	ShootBack.PushBack({7,178,261,160});
	ShootBack.PushBack({ 7,346,261,160 });
	ShootBack.PushBack({ 7,513,261,160 });
	ShootBack.loop = true;
	ShootBack.speed = 0.5;
	//currentAnim = &ShootBack;

	ShootBombs.PushBack({ 285,10,261,160 });
	ShootBombs.PushBack({ 285,178,261,160 });
	ShootBombs.PushBack({ 285,346,261,160 });
	ShootBombs.PushBack({ 285,513,261,160 });
	ShootBombs.PushBack({ 285,178,261,160 });
	ShootBombs.PushBack({ 285,10,261,160 });
	ShootBombs.loop = false;
	ShootBombs.speed = 0.08;
	//currentAnim = &ShootBombs;

	Hit.PushBack({562,513,261,160});
	Hit.loop = false;
	Hit.speed = 0.1;

	collider = App->collisions->AddCollider({ 0, 0, 261, 60 }, Collider::Type::BOSS1, (Module*)App->enemies);

	position.x -= SCREEN_WIDTH+280;
	App->audio->PlayMusic("Assets/Boss 1.ogg", 0);
}


void Enemy_FinalBoss1::Update() {
	timerBallShot->update();
	timerBurstShot->update();
	
	

	if(stateEnemy == status_Enemies::STATE_ENEMY_HIT)timerState->update();
	if (timerState->check()) stateEnemy = status_Enemies::STATE_ENEMY_IDLE;

	if (stateEnemy == status_Enemies::STATE_ENEMY_HIT_COLLISION)timerStateCollision->update();
	if (timerStateCollision->check()) stateEnemy = status_Enemies::STATE_ENEMY_IDLE;

	timerAnim->update();
	if (timerAnim->check())currentAnim = &FirsAnim;
	move();
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Draw();
}
void Enemy_FinalBoss1::OnCollision(Collider* collider){
	if (collider->type == Collider::PLAYER_SHOT && stateEnemy != status_Enemies::STATE_ENEMY_HIT)lives--, stateEnemy = status_Enemies::STATE_ENEMY_HIT;
	else if (collider->type == Collider::PLAYER && stateEnemy != status_Enemies::STATE_ENEMY_HIT_COLLISION)lives--, stateEnemy = status_Enemies::STATE_ENEMY_HIT_COLLISION;
	currentAnim = &Hit;
	if(lives<=0 && App->player->destroyed==false) App->level1->Win();
}


void Enemy_FinalBoss1::move() {

	burstShot();
	float vecX[4] = { 0.75 ,SCREEN_SPEED ,1.25 ,SCREEN_SPEED };
	float vecY[4] = { 0.55, 0, -0.55, 0 };
	if (collider->pendingToDelete != true)	collider->SetPos(position.x, position.y + ((*currentAnim).GetCurrentFrame().h / 3) - (collider->rect.h / 3));
	if (pattern > 1 && timerBallShot->check())ballShot(), burst = 0;
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
		else xRecorrido = 0, change=false,pattern = 3;
		break;
	}
}


void Enemy_FinalBoss1::ballShot() {

	App->particles->AddParticle(App->particles->ballShotBoss1, position.x+105, position.y+70, Collider::Type::BOSS1_SHOT_BALL);
	App->particles->AddParticle(App->particles->ballShotBoss1, position.x+105, position.y+10, Collider::Type::BOSS1_SHOT_BALL);


}
void Enemy_FinalBoss1::burstShot() {

	if (timerBurstShot->check() && burst < 4) {
		App->particles->AddParticle(App->particles->pBurstshotBallBoss1, position.x, position.y + 60, Collider::Type::BOSS_BURSTSHOT);
		//Insert sound here
		++burst;
	}
}