#include "Enemy_Green2.h"

#include "Application.h"
#include "ModuleCollisions.h"


Enemy_Green2::Enemy_Green2(int x, int y, int _pattern) :Enemy(x, y, _pattern)
{
	//Animation
	FirsAnim.PushBack({ 891,421,54,14 });
	currentAnim = &FirsAnim;

	Up.PushBack({ 1011,421,54,19});
	Up.speed = 0.08;
	Up.loop = false;

	Down.PushBack({951, 421, 54, 21});
	Down.speed = 0.08;
	Down.loop = false;

	collider = App->collisions->AddCollider({ 0, 0, 54, 14 }, Collider::Type::ENEMY, (Module*)App->enemies);
}


void Enemy_Green2::Update() {

	move();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_Green2::move() {

	switch (pattern) {
	case 0:
		currentAnim = path.GetCurrentAnimation();
		waveRatio += waveRatioSpeed;
		path.Update();
		position = spawnPos + path.GetRelativePosition();

		position.x -= 1;
		break;

	case 1:
		if (xRecorrido < 110)
		{
			xRecorrido++;
			position.x += -1;
		}
		else pattern = 2;
		break;
	case 2:
		if(yRecorrido < 10)currentAnim = &Down;
		else currentAnim = &FirsAnim;
		if (yRecorrido < 25)
		{
			yRecorrido++;
			position.y += 2;
			position.x += 1;
		}
		else pattern = 3;
		break;
	case 3:
		if (yRecorrido < 55)currentAnim = &Up;
		else currentAnim = &FirsAnim;
		if (yRecorrido < 75)
		{
			yRecorrido++;
			position.y -= 2;
			position.x += 1;
		}
		else pattern = 4;
		break;
	case 4:
		if (yRecorrido < 105)currentAnim = &Down;
		else currentAnim = &FirsAnim;
		if (yRecorrido < 125)
		{
			yRecorrido++;
			position.y += 2;
			position.x += 1;
		}
		else pattern = 5;
		break;
	case 5:
		if (yRecorrido < 155)currentAnim = &Up;
		else currentAnim = &FirsAnim;
		if (yRecorrido < 175)
		{
			yRecorrido++;
			position.y -= 2;
			position.x += 1;
		}
		else pattern = 6;
		break;
	case 6:
		position.x += 1;

	}


}