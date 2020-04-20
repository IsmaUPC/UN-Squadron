#include "Enemy_GreenShip.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_GreenShip::Enemy_GreenShip(int x, int y, int _pattern) : Enemy(x, y,_pattern)
{
	flyInvers.PushBack({ 497,213,54,16 });
	currentAnim = &flyInvers;
	flyInvers.speed = 0.01f;

	fly.PushBack({ 557,213,53,16 });
	//currentAnim = &fly;
	fly.speed = 0.01f;

	twistToRight.PushBack({ 435,221,54, 20 });
	twistToRight.PushBack({ 373,214,54, 31 });
	twistToRight.PushBack({ 328,214,39, 31 });
	twistToRight.PushBack({ 289,212,29, 35 });
	twistToRight.PushBack({ 264,210,18, 39 });
	twistToRight.PushBack({ 237,212,23, 35 });
	twistToRight.PushBack({ 196,214,37, 31 });
	twistToRight.PushBack({ 134,214,54, 31 });
	twistToRight.PushBack({ 74,219,54, 20 });
	twistToRight.PushBack({ 557,213,53,16 });
	twistToRight.loop = false;
	twistToRight.speed = 0.02f;

	twistToLeft.PushBack({ 619,221,53, 20 });
	twistToLeft.PushBack({ 680,214,54, 31 });
	twistToLeft.PushBack({ 740,214,39, 31 });
	twistToLeft.PushBack({ 790,212,29, 35 });
	twistToLeft.PushBack({ 825,210,18, 39 });
	twistToLeft.PushBack({ 847,212,23, 35 });
	twistToLeft.PushBack({ 874,214,37, 31 });
	twistToLeft.PushBack({ 920,214,53, 31 });
	twistToLeft.PushBack({ 979,219,54, 20 });
	twistToLeft.PushBack({ 497,213,54,16 });
	twistToLeft.loop = false;
	twistToLeft.speed = 0.02f;

	loopToRight.PushBack({ 557,213,53,16 });
	loopToRight.PushBack({ 680,214,54, 31 });
	loopToRight.PushBack({ 557,233,53, 16 });
	loopToRight.PushBack({ 134,214,54, 31 });
	loopToRight.loop = true;
	loopToRight.speed = 0.02f;

	loopToLeft.PushBack({ 497,213,54,16 });
	loopToLeft.PushBack({ 373,214,54, 31 });
	loopToLeft.PushBack({ 497,233,54,16 });
	loopToLeft.PushBack({ 920,214,53, 31 });
	loopToLeft.loop = true;
	loopToLeft.speed = 0.02f;

	collider = App->collisions->AddCollider({0, 0, 54, 16}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_GreenShip::Update()
{
	waveRatio += waveRatioSpeed;

	position.y = spawnPos.y + (waveHeight * sinf(waveRatio));
	position.x -= 1;

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_GreenShip::move(){
	switch (pattern) {
	case 0:
		waveRatio += waveRatioSpeed;

		position.y = spawnPos.y + (waveHeight * sinf(waveRatio));
		position.x -= 1;

		break;

	case 1:

		break;
	}

}


