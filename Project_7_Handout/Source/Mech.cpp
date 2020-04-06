#include "Mech.h"

#include "Application.h"
#include "ModuleCollisions.h"
Mech::Mech(int x, int y) : Enemy(x, y)
{
	
	walk.PushBack({ 5,107,30,30 });
	walk.PushBack({ 67,105,30,30 });
	walk.PushBack({ 36,107,30,30 });
	walk.speed = 0.1f;

	walkBack.PushBack({ 139,107,30,30 });
	walkBack.PushBack({ 108,104,30,30 });
	walkBack.PushBack({170,107,30,30 });
	walkBack.speed = 0.1f;

	path.PushBack({ -0.5f , 0.0f }, 125, &walk);

	path.PushBack({ 1.0f , 0.0f }, 250, &walkBack);
	collider = App->collisions->AddCollider({ 0, 0, 30, 30 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Mech::Update()
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
