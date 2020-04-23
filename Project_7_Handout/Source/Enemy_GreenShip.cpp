#include "Enemy_GreenShip.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_GreenShip::Enemy_GreenShip(int x, int y, int _pattern) : Enemy(x, y,_pattern)
{
	flyInvers.PushBack({ 497,213,54,16 });
	//currentAnim = &flyInvers;
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
	twistToRight.speed = 0.15f;

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
	twistToLeft.speed = 0.15f;

	loopToRight.PushBack({ 557,213,53,16 });
	loopToRight.PushBack({ 619,221,53, 20 });
	loopToRight.PushBack({ 680,214,54, 31 });
	loopToRight.PushBack({ 846,315,54, 21 });
	loopToRight.PushBack({ 557,233,53, 16 });
	loopToRight.PushBack({ 108,315,53, 20 });
	loopToRight.PushBack({ 134,214,54, 31 });
	loopToRight.PushBack({ 74,219,54, 20  });
	loopToRight.loop = true;
	loopToRight.speed = 0.3f;

	loopToLeft.PushBack({ 497,213,54,16 });
	loopToLeft.PushBack({ 435,221,54, 20 });
	loopToLeft.PushBack({ 373,214,54, 31 });
	loopToLeft.PushBack({ 194,315,54, 20 });
	loopToLeft.PushBack({ 497,233,54,16 });
	loopToLeft.PushBack({ 923,315,54,20 });
	loopToLeft.PushBack({ 920,214,53, 31 });
	loopToLeft.PushBack({ 979,219,54, 20 });
	loopToLeft.loop = true;
	loopToLeft.speed = 0.3f;

	collider = App->collisions->AddCollider({0, 0, 54, 16}, Collider::Type::ENEMY, (Module*)App->enemies);
	
}

void Enemy_GreenShip::Update()
{
	move();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_GreenShip::move() {
	//spawnPos.x += SCREEN_SPEED;


	switch (pattern) {
	case 0:
		switch (FASE)
		{
		case 1:
			currentAnim = &flyInvers;
			if (xRecorrido < 350)
			{
				xRecorrido += 4;
				position.y -= 1;
				position.x -= 4;
			}
			else FASE = 2;
			break;
		case 2:
			currentAnim = &twistToRight;
			if (yRecorrido < 100)
			{
				yRecorrido += 2;
				position.y += 2;
				position.x -= 1;
			}
			else FASE = 3;
			break;
		case 3:
			if (xRecorrido > 380) currentAnim = &loopToRight;
			xRecorrido += 2;
			position.y = position.y;
			position.x += 6;
		}
		break;

	case 1:
		switch (FASE)
		{
		case 1:
			currentAnim = &flyInvers;
			if (xRecorrido < 290)
			{
				xRecorrido += 3;
				position.y -= 0.3;
				position.x -= 4;
			}
			else FASE = 2;
			break;
		case 2:
			currentAnim = &twistToRight;
			if (yRecorrido < 60)
			{
				yRecorrido += 1;
				position.y -= 0.5;
				position.x += 0.5;
			}
			else FASE = 3;
			break;
		case 3:
			if (xRecorrido > 350) currentAnim = &loopToRight;
			xRecorrido += 2;
			position.y = position.y;
			position.x += 7;
		}
		break;
	case 2:
		switch (FASE)
		{
		case 1:
			currentAnim = &flyInvers;
			if (xRecorrido < 290)
			{
				xRecorrido += 3;
				position.y += 1;
				position.x -= 4;
			}
			else FASE = 2;
			break;
		case 2:
			currentAnim = &twistToRight;
			if (yRecorrido < 60)
			{
				yRecorrido += 1;
				position.y += 0.5;
				position.x += 0.5;
			}
			else FASE = 3;
			break;
		case 3:
			if (xRecorrido > 350) currentAnim = &loopToRight;
			xRecorrido += 2;
			position.y = position.y;
			position.x += 7;
			break;
		}
		break;

	case 3:

		if (FASE == 1) {
			if (!startmove) {
				startmove = true;
				n = 270;
			}

			if (n <= 360) {

				xRecorrido = (spawnPos.x - position.x);
				n += 5;
				alpha = n * M_PI / 180.0f;

				position.x += (position.y * cos(alpha)) / 40;
				position.y -= 2;
			}
			else {
				FASE = 2;
				startmove = false;
			}
		}
		if (FASE == 2) {
			if (!startmove) {
				startmove = true;
				n = 0;
			}
			xRecorrido = (spawnPos.x - position.x);
			n += 3;
			alpha = n * M_PI / 180.0f;
			position.x += (position.y * cos(alpha)) / 40;
			position.y -= 2;

		}


		break;

	}
}


