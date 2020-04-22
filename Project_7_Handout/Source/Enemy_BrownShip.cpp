#include "Enemy_BrownShip.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_BrownShip::Enemy_BrownShip(int x, int y,int _pattern) : Enemy(x, y,_pattern)
{
	flyInvers.PushBack({487,165,61,18});
	flyInvers.speed = 0.01f;

	fly.PushBack({ 559,165,62,18 });
	fly.speed = 0.01f;
	
	twistToRight.PushBack({ 414,169,62, 35 });
	twistToRight.PushBack({ 348,157,62, 47 });
	twistToRight.PushBack({ 295,157,49, 47 });
	twistToRight.PushBack({ 254,157,35, 47 });
	twistToRight.PushBack({ 225,157,20, 47 });
	twistToRight.PushBack({ 186,157,33, 47 });
	twistToRight.PushBack({ 132,157,47, 47 });
	twistToRight.PushBack({ 66,155,62, 49 });
	twistToRight.PushBack({ 0,171,62, 33 });
	twistToRight.PushBack({ 559,165,62, 18 });
	twistToRight.loop = false;
	twistToRight.speed = 0.15f;
	

	twistToLeft.PushBack({ 631,169,62, 35 });
	twistToLeft.PushBack({ 697,157,62, 47 });
	twistToLeft.PushBack({ 763,157,49, 47 });
	twistToLeft.PushBack({ 819,157,35, 47 });
	twistToLeft.PushBack({ 862,157,21, 47 });
	twistToLeft.PushBack({ 889,157,33, 47 });
	twistToLeft.PushBack({ 928,157,47, 47 });
	twistToLeft.PushBack({ 979,155,62, 49 });
	twistToLeft.PushBack({ 1045,171,62, 33 });
	twistToLeft.PushBack({ 487,165,62, 18 });
	twistToLeft.loop = false;
	twistToLeft.speed = 0.15f;

	loopToRight.PushBack({ 559,165,62,18 });
	loopToRight.PushBack({ 631,169,62, 35 });
	loopToRight.PushBack({ 697,157,62, 47 });
	loopToRight.PushBack({ 846,271,62, 35 });
	loopToRight.PushBack({ 559,188,62, 18 });
	loopToRight.PushBack({ 108,271,62, 33 });
	loopToRight.PushBack({ 66,155,62, 49 });
	loopToRight.PushBack({ 0,171,62, 33 });
	loopToRight.loop = true;
	loopToRight.speed = 0.3f;

	loopToLeft.PushBack({ 487,165,61,18 });
	loopToLeft.PushBack({ 414, 169, 62, 35});
	loopToLeft.PushBack({ 348,157,62, 47 });
	loopToLeft.PushBack({ 186,271,62, 35 });
	loopToLeft.PushBack({ 487,188,61, 18 });
	loopToLeft.PushBack({ 923,271,62, 33 });
	loopToLeft.PushBack({ 979,155,62, 49 });
	loopToLeft.PushBack({ 1045,171,62, 33 });
	loopToLeft.loop = true;
	loopToLeft.speed = 0.3f;

	// TODO 3: Have the Brown Cookies describe a path in the screen
	//path.PushBack({-0.8f , -0.5f}, 100, &flyInvers);
	//path.PushBack({ -0.8f , 0.5f }, 100, &flyInvers);
	collider = App->collisions->AddCollider({0, 0, 61, 18}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_BrownShip::Update()
{
	move();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_BrownShip::move() {
	spawnPos.x += SCREEN_SPEED;

	switch (pattern) {
	case 0:
		currentAnim = path.GetCurrentAnimation();
		waveRatio += waveRatioSpeed;
		path.Update();
		position = spawnPos + path.GetRelativePosition();

		position.x -= 1;
		break;

	case 1:
		switch (FASE) {
		case 1:
			currentAnim = &flyInvers;
			if (xRecorrido < 200) {
				xRecorrido = (spawnPos.x - position.x);

				position.x -= 2;

			}
			else
				FASE = 2;
			break;
		case 2:
			currentAnim = &twistToRight;
			if (position.y < SCREEN_HEIGHT/2) {
				xRecorrido = (spawnPos.x - position.x);

				position.y += sqrt(xRecorrido / 100);
				position.x -= 2;
			}
			else
				FASE = 3;

			break;
		case 3:
			if (position.y < 250) {
				xRecorrido = (spawnPos.x - position.x);
				position.y += sqrt(xRecorrido / 150);
				position.x += 4;
			}
			else
				FASE = 4;
			break;

		case 4:
			if (position.y < 255)currentAnim = &fly;
			if (position.y >= 255)currentAnim = &loopToRight;

			xRecorrido = (spawnPos.x - position.x);

			position.y += sqrt(xRecorrido / 150);
			position.x += 6;
			break;
		}

		break;
	case 2:
		switch (FASE) {
		case 1:
			currentAnim = &flyInvers;
			if (xRecorrido < 200) {
				xRecorrido = (spawnPos.x - position.x);

				position.x -= 3;

			}
			else
				FASE = 2;
			break;
		case 2:
			currentAnim = &twistToRight;
			if (position.y > 135) {
				xRecorrido = (spawnPos.x - position.x);

				position.y -= sqrt(xRecorrido / 30);
				position.x -= 3;
			}
			else
				FASE = 5;

			break;
		case 3:
			if (position.y > 180) {
				xRecorrido = (spawnPos.x - position.x);
				position.y -= sqrt(xRecorrido / 50);
				position.x += SCREEN_SPEED;
			}
			else
				FASE = 4;
			break;

		case 4:
			if (position.y > 180) {
				xRecorrido = (spawnPos.x - position.x);

				position.y -= sqrt(xRecorrido / 50);
				position.x += 5;
			}
			else
				FASE = 5;
			break;
		case 5:
			if (position.y > 105)currentAnim = &fly;
			if(position.y<=105)currentAnim = &loopToRight;
			
			xRecorrido = (spawnPos.x - position.x);

			position.y -= sqrt(xRecorrido / 100);
			position.x += 5 + SCREEN_SPEED;
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
