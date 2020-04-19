#include "Enemy_RedShip.h"
#include "Application.h"
#include "ModuleCollisions.h"


Enemy_RedShip::Enemy_RedShip(int x, int y) : Enemy(x, y)
{
	flyInvers.PushBack({ 790,29,66,39 });
	currentAnim = &flyInvers;
	flyInvers.speed = 0.01f;

	fly.PushBack({ 252,29,66,39 });
	//currentAnim = &fly;
	fly.speed = 0.01f;

	twistToRight.PushBack({ 722,31,62, 37 });
	twistToRight.PushBack({ 670,16,48, 52 });
	twistToRight.PushBack({ 633,6,31, 62 });
	twistToRight.PushBack({ 610,0,19, 68 });
	twistToRight.PushBack({ 579,0,25, 68 });
	twistToRight.PushBack({ 534,0,39, 68 });
	twistToRight.PushBack({ 503,0,25, 68 });
	twistToRight.PushBack({ 478,0,19, 68 });
	twistToRight.PushBack({ 443,6,31, 62 });
	twistToRight.PushBack({ 390,16,47, 52 });
	twistToRight.PushBack({ 324,31,52, 37 });
	twistToRight.PushBack({ 252,29,66,39 });
	twistToRight.loop = false;
	twistToRight.speed = 0.02f;


	twistToLeft.PushBack({ 324,31,52, 37 });
	twistToLeft.PushBack({ 390,16,47, 52 });
	twistToLeft.PushBack({ 443,6,31, 62 });
	twistToLeft.PushBack({ 478,0,19, 68 });
	twistToLeft.PushBack({ 503,0,25, 68 });
	twistToLeft.PushBack({ 534,0,39, 68 });
	twistToLeft.PushBack({ 579,0,25, 68 });
	twistToLeft.PushBack({ 610,0,19, 68 });
	twistToLeft.PushBack({ 633,6,31, 62 });
	twistToLeft.PushBack({ 670,16,48, 52 });
	twistToLeft.PushBack({ 722,31,62, 37 });
	twistToLeft.PushBack({ 790,29,66,39 });
	twistToLeft.loop = false;
	twistToLeft.speed = 0.02f;

	path.PushBack({ -0.5f , 0.0f }, 125, &flyInvers);

	//path.PushBack({ 1.0f , 0.0f }, 250, &walkBack);
	collider = App->collisions->AddCollider({ 0, 0, 66, 39 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_RedShip::Update()
{

	currentAnim = path.GetCurrentAnimation();
	waveRatio += waveRatioSpeed;
	path.Update();
	position = spawnPos + path.GetRelativePosition();

	position.x -= 1;

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();

}
