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
		// raiz quadrada es sqrt()
		if (FASE == 1) {
			if (position.y >= SCREEN_HEIGHT / 2) {

				xRecorrido = (spawnPos.x - position.x);
				//if (xRecorrido >= 100)
				//if (xRecorrido > 0)
				position.y -= sqrt(xRecorrido / 50);

				position.x -= 2;
			}
			else {
				FASE = 2;
			}
		}
		else {
			xRecorrido--;

			//if (xRecorrido >= 100) 
			//if (xRecorrido > 0)
			position.y -= sqrt(xRecorrido / 50);

			position.x += 3;
		}

		break;
	case 2:
		/*if (FASE == 1){
			if (xRecorrido < (SCREEN_WIDTH / 2)-66) {
				xRecorrido = (spawnPos.x - position.x);

				position.x -= 1;

			}
			else {
				FASE = 2;
			}
		}else if(FASE == 2){
			position.y -= sqrt(xRecorrido / 50);
			position.x += 2;

		}*/
		switch (FASE) {
		case 1:
			if (xRecorrido < 300) {
				xRecorrido = (spawnPos.x - position.x);

				position.x -= 2;

			}
			else
				FASE = 2;
			break;
		case 2:
			currentAnim = &twistToRight;
			if (position.y < 220) {
				xRecorrido = (spawnPos.x - position.x);

				position.y += sqrt(xRecorrido / 50);
				position.x -= 1;
			}
			else
				FASE = 3;

			break;
		case 3:
			if (position.y < 290) {
				xRecorrido = (spawnPos.x - position.x);
				position.y += sqrt(xRecorrido / 50);
				position.x += SCREEN_SPEED;
			}
			else
				FASE = 4;
			break;

		case 4:
			if (position.y >= 290) {
				xRecorrido = (spawnPos.x - position.x);

				position.y -= sqrt(xRecorrido / 50);
				position.x += 5;
			}
			else
				FASE = 5;
			break;
		case 5:
			if (position.y < 310)currentAnim = &fly;
			if (position.y >= 310)currentAnim = &loopToRight;

			xRecorrido = (spawnPos.x - position.x);

			position.y += sqrt(xRecorrido / 80);
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


