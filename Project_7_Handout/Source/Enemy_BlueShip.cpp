#include "Enemy_BlueShip.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_BlueShip::Enemy_BlueShip(int x, int y,int _pattern) : Enemy(x, y, _pattern)
{
	flyInvers.PushBack({ 419,258,61,18 });
	//currentAnim = &flyInvers;
	flyInvers.speed = 0.01f;

	fly.PushBack({ 627,258,62,18 });
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
	position.x -= SCREEN_WIDTH + 100;
}

void Enemy_BlueShip::Update()
{
	move();


	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_BlueShip::move(){
	switch (pattern) {
	case 0:
		currentAnim = &fly;
		//path.Update();
		//position = spawnPos + path.GetRelativePosition();
		switch (FASE) {
		case 1:
			if (xRecorrido < 250) {
				xRecorrido += 4;
				position.y = position.y;
				position.x += 5;

			}
			else
				FASE = 2;
			break;
		case 2:
			currentAnim = &downAnimToRight;
			position.y += 3;
			position.x += 5;

			break;
		}
		break;

	case 1:
		currentAnim = &fly;
		switch (FASE) {
		case 1:
			if (xRecorrido < 300) {
				xRecorrido += 4;
				position.y = position.y;
				position.x += 5;

			}
			else
				FASE = 2;
			break;
		case 2:
			currentAnim = &upAnimToRight;
			position.y -= 3;
			position.x += 5;

			break;
		}
		break;
	}
}

