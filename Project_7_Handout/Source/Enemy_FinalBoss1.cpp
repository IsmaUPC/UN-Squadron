#include "Enemy_FinalBoss1.h"

#include "Application.h"
#include "ModuleCollisions.h"


Enemy_FinalBoss1::Enemy_FinalBoss1(int x, int y, int _pattern) :Enemy(x, y, _pattern)
{
	//Animation
	FirsAnim.PushBack({ 7,10,261,160 });
	currentAnim = &FirsAnim;
	FirsAnim.speed = 0.1;



	collider = App->collisions->AddCollider({ 0, 0, 261, 160 }, Collider::Type::ENEMY, (Module*)App->enemies);
	position.x -= SCREEN_WIDTH+280;
}


void Enemy_FinalBoss1::Update() {
	move();
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
void Enemy_FinalBoss1::OnCollision(Collider* collider){
	//App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	App->level1->Win();
	//isDead = false;
}

void Enemy_FinalBoss1::move() {
	if (collider->pendingToDelete != true)
		resizeCollider();
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
		else pattern = 3;
		break;
	case 3:
		if (xRecorrido < SCREEN_WIDTH + 550)
		{
			xRecorrido += 1;
			position.y += 0.55;
			position.x += 0.75;
		}
		else pattern = 4;
		break;
	case 4:
		if (xRecorrido < SCREEN_WIDTH + 740)
		{
			xRecorrido += 1;
			position.y -= 0.55;
			position.x += 1.25;
		}
		//else pattern = 4;
		break;
	}
}//3 2 4 2, la diferencia es de 90