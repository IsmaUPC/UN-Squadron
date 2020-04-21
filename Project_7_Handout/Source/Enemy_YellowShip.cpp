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

