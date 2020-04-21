#include "Enemy_YellowShip.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_YellowShip::Enemy_YellowShip(int x, int y,int _pattern):Enemy(x,y,_pattern)
{
	flyInvers.PushBack({ 790,105,66,39 });
	currentAnim = &flyInvers;
	flyInvers.speed = 0.01f;

	fly.PushBack({ 252,105,66,39 });
	//currentAnim = &fly;
	fly.speed = 0.01f;

	twistToRight.PushBack({ 722,107,62, 37 });
	twistToRight.PushBack({ 670,93,48, 52 });
	twistToRight.PushBack({ 633,82,31, 62 });
	twistToRight.PushBack({ 610,76,19, 68 });
	twistToRight.PushBack({ 579,76,25, 68 });
	twistToRight.PushBack({ 534,76,39, 68 });
	twistToRight.PushBack({ 503,76,25, 68 });
	twistToRight.PushBack({ 478,76,19, 68 });
	twistToRight.PushBack({ 443,82,31, 62 });
	twistToRight.PushBack({ 390,93,47, 52 });
	twistToRight.PushBack({ 324,107,52, 37 });
	twistToRight.PushBack({ 252,105,66,39 });
	twistToRight.loop = false;
	twistToRight.speed = 0.02f;

	twistToLeft.PushBack({ 324,107,52, 37 });
	twistToLeft.PushBack({ 390,93,47, 52 });
	twistToLeft.PushBack({ 443,82,31, 62 });
	twistToLeft.PushBack({ 478,76,19, 68 });
	twistToLeft.PushBack({ 503,76,25, 68 });
	twistToLeft.PushBack({ 534,76,39, 68 });
	twistToLeft.PushBack({ 579,76,25, 68 });
	twistToLeft.PushBack({ 610,76,19, 68 });
	twistToLeft.PushBack({ 633,82,31, 62 });
	twistToLeft.PushBack({ 670,93,48, 52 });
	twistToLeft.PushBack({ 722,107,62, 37 });
	twistToLeft.PushBack({ 790,105,66,39 });
	twistToLeft.loop = false;
	twistToLeft.speed = 0.02f;

	twistToRightToDown.PushBack({ 722,393,62, 37 });
	twistToRightToDown.PushBack({ 670,393,48, 52 });
	twistToRightToDown.PushBack({ 633,393,31, 62 });
	twistToRightToDown.PushBack({ 610,393,19, 68 });
	twistToRightToDown.PushBack({ 579,393,25, 68 });
	twistToRightToDown.PushBack({ 534,393,39, 68 });
	twistToRightToDown.PushBack({ 503,393,25, 68 });
	twistToRightToDown.PushBack({ 478,393,19, 68 });
	twistToRightToDown.PushBack({ 443,393,31, 62 });
	twistToRightToDown.PushBack({ 390,393,47, 52 });
	twistToRightToDown.PushBack({ 324,393,52, 37 });
	twistToRightToDown.PushBack({ 252,393,66,39 });
	twistToRightToDown.loop = false;
	twistToRightToDown.speed = 0.02f;

	twistToLeftToDown.PushBack({ 324,393,52, 37 });
	twistToLeftToDown.PushBack({ 390,393,47, 52 });
	twistToLeftToDown.PushBack({ 443,393,31, 62 });
	twistToLeftToDown.PushBack({ 478,393,19, 68 });
	twistToLeftToDown.PushBack({ 503,393,25, 68 });
	twistToLeftToDown.PushBack({ 534,393,39, 68 });
	twistToLeftToDown.PushBack({ 579,393,25, 68 });
	twistToLeftToDown.PushBack({ 610,393,19, 68 });
	twistToLeftToDown.PushBack({ 633,393,31, 62 });
	twistToLeftToDown.PushBack({ 670,393,48, 52 });
	twistToLeftToDown.PushBack({ 722,393,62, 37 });
	twistToLeftToDown.PushBack({ 790,393,66,39 });
	twistToLeftToDown.loop = false;
	twistToLeftToDown.speed = 0.02f;

	path.PushBack({ -0.5f , 0.0f }, 125, &flyInvers);
	collider = App->collisions->AddCollider({ 0, 0, 66, 39 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_YellowShip::Update()
{
	move();
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_YellowShip::move(){

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

