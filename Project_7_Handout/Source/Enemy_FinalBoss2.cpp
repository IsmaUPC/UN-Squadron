#include "Enemy_FinalBoss2.h"

#include "Application.h"
#include "ModuleCollisions.h"


Enemy_FinalBoss2::Enemy_FinalBoss2(int x, int y, int _pattern) :Enemy(x, y, _pattern)
{
	//Animation
	FirsAnim.PushBack({ 2,34,85,32 });
	currentAnim = &FirsAnim;

	Inclined.PushBack({ 99,26,86,40 });

	Down.PushBack({ 195,13,85,53 });

	collider = App->collisions->AddCollider({ 0, 0, 66, 39 }, Collider::Type::ENEMY, (Module*)App->enemies);
}


void Enemy_FinalBoss2::Update() {

	move();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_FinalBoss2::move() {

	switch (pattern) {
	case 0:
		
		break;

	case 1:

		break;
	}


}