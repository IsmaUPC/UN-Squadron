#include "Enemy_BlueShip.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_BlueShip::Enemy_BlueShip(int x, int y) : Enemy(x, y)
{
	flyInvers.PushBack({ 419,258,61,18 });
	currentAnim = &flyInvers;
	flyInvers.speed = 0.01f;

	fly.PushBack({ 627,258,62,18 });
	//currentAnim = &fly;
	fly.speed = 0.01f;

	upAnimToRight.PushBack({ 695, 254, 62, 26 });
	upAnimToRight.loop = false;
	upAnimToRight.speed = 0.1f;

	downAnimToRight.PushBack({ 559, 258, 62, 29 });
	downAnimToRight.loop = false;
	downAnimToRight.speed = 0.1f;

	upAnimToLeft.PushBack({ 351, 254, 61, 26 });
	upAnimToLeft.loop = false;
	upAnimToLeft.speed = 0.1f;

	downAnimToLeft.PushBack({ 487, 258, 61, 29 });
	downAnimToLeft.loop = false;
	downAnimToLeft.speed = 0.1f;

	path.PushBack({ -0.8f , -0.5f }, 100, &flyInvers);
	collider = App->collisions->AddCollider({ 0, 0, 61, 18 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_BlueShip::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
