#include "Enemy_BlueShip.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_BlueShip::Enemy_BlueShip(int x, int y,int _pattern) : Enemy(x, y, _pattern)
{
	flyInvers.PushBack({ 419,258,61,18 });
	currentAnim = &flyInvers;
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
	if(pattern<=3)position.x -= SCREEN_WIDTH + 100;
	if (pattern == 2)TOP = 410, pattern = 0;
	else if (pattern == 3)TOP = 410, pattern = 1;
	else TOP = 250;
	if (pattern == 4)toLeft=true,direction=-1, pattern = 0;
	if (pattern == 5)toLeft = true, direction = -1, pattern = 1;
	if (pattern == 6)noUp=true,toLeft = true, direction = -1, pattern = 1;
}

void Enemy_BlueShip::Update()
{
	move();


	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_BlueShip::move(){

	if(collider->pendingToDelete != true)
		resizeCollider();

	switch (pattern) {
	case 0:
		if(toLeft==true)currentAnim = &flyInvers;
		else currentAnim = &fly;
	
		//path.Update();
		//position = spawnPos + path.GetRelativePosition();
		switch (FASE) {
		case 1:
			if (xRecorrido < TOP) {
				xRecorrido += 4;
				position.y = position.y;
				position.x += direction*5;

			}
			else
				FASE = 2;
			break;
		case 2:
			if (toLeft == true)currentAnim = &downAnimToLeft;
			else currentAnim = &downAnimToRight;
			
			position.y += 3;
			position.x += direction*5;

			break;
		}
		break;

	case 1:
		if (toLeft == true)currentAnim = &flyInvers;
		else currentAnim = &fly;
		switch (FASE) {
		case 1:
			if (xRecorrido < TOP+50) {
				xRecorrido += 4;
				position.y = position.y;
				position.x += direction*5;

			}
			else
				FASE = 2;
			break;
		case 2:
			if (toLeft == true)currentAnim = &upAnimToLeft;
			else currentAnim = &upAnimToRight;
			position.x += direction * 5;
			if (noUp == false) position.y -= 3;
			else position.y -= 0.2;
			break;
		}
		break;
	case 7:
		position.x -= direction * 5;
		break;
	}
	
}

