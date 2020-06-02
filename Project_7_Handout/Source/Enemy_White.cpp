#include "Enemy_White.h"

#include "Application.h"
#include "ModuleCollisions.h"


Enemy_White::Enemy_White(int x, int y, int _pattern) :Enemy(x, y, _pattern)
{
	//Animation
	FirsAnim.PushBack({ 891,394,52,19 });
	currentAnim = &FirsAnim;

	Up.PushBack({ 951,394,52,23 });

	Down.PushBack({ 1011, 394, 52, 21 });


	collider = App->collisions->AddCollider({ 0, 0, 52, 39 }, Collider::Type::ENEMY, (Module*)App->enemies);
}


void Enemy_White::Update() {

	move();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_White::move() {

	switch (pattern) {
	case 0:
		currentAnim = path.GetCurrentAnimation();
		waveRatio += waveRatioSpeed;
		path.Update();
		position = spawnPos + path.GetRelativePosition();

		position.x -= 1;
		break;

	case 1:

		break;
	}


}