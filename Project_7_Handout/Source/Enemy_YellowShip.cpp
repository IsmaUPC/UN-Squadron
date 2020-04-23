#include "Enemy_YellowShip.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_YellowShip::Enemy_YellowShip(int x, int y,int _pattern):Enemy(x,y,_pattern)
{
	flyInvers.PushBack({ 790,105,66,39 });
	currentAnim = &flyInvers;
	flyInvers.speed = 0.01f;

	fly.PushBack({ 252,105,66,39 });
	fly.speed = 0.015f;

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
	twistToRight.speed = 0.13f;

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
	twistToLeft.speed = 0.13f;

	twistToRightToDown.PushBack({ 722,393,62, 37 });
	twistToRightToDown.PushBack({ 670,393,48, 52 });
	twistToRightToDown.PushBack({ 633,393,31, 62 });
	twistToRightToDown.PushBack({ 610,393,19, 68 });
	twistToRightToDown.PushBack({ 579,393,25, 68 });
	twistToRightToDown.PushBack({ 534,393,39, 68 });
	twistToRightToDown.PushBack({ 503,393,25, 68 });
	twistToRightToDown.PushBack({ 478,393,19, 68 });
	twistToRightToDown.PushBack({ 443,393,31, 62 });
	twistToRightToDown.PushBack({ 390,393,47, 52 });
	twistToRightToDown.PushBack({ 324,393,52, 37 });
	twistToRightToDown.PushBack({ 252,393,66,39 });
	twistToRightToDown.loop = false;
	twistToRightToDown.speed = 0.13f;

	twistToLeftToDown.PushBack({ 324,393,52, 37 });
	twistToLeftToDown.PushBack({ 390,393,47, 52 });
	twistToLeftToDown.PushBack({ 443,393,31, 62 });
	twistToLeftToDown.PushBack({ 478,393,19, 68 });
	twistToLeftToDown.PushBack({ 503,393,25, 68 });
	twistToLeftToDown.PushBack({ 534,393,39, 68 });
	twistToLeftToDown.PushBack({ 579,393,25, 68 });
	twistToLeftToDown.PushBack({ 610,393,19, 68 });
	twistToLeftToDown.PushBack({ 633,393,31, 62 });
	twistToLeftToDown.PushBack({ 670,393,48, 52 });
	twistToLeftToDown.PushBack({ 722,393,62, 37 });
	twistToLeftToDown.PushBack({ 790,393,66,39 });
	twistToLeftToDown.loop = false;
	twistToLeftToDown.speed = 0.13f;

			
	//path.PushBack({ -0.5f , 0.0f }, 125, &flyInvers);
	collider = App->collisions->AddCollider({ 0, 0, 66, 39 }, Collider::Type::ENEMY, (Module*)App->enemies);

	position.x -= SCREEN_WIDTH +100;
}

void Enemy_YellowShip::Update()
{
	move();
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_YellowShip::move() {
	spawnPos.x += SCREEN_SPEED;


	if (collider->pendingToDelete != true)
		resizeCollider();

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
			if (xRecorrido < 200) {
				xRecorrido = (spawnPos.x - position.x);

				position.x -= 2;

			}
			else
				FASE = 2;
			break;
		case 2:
			currentAnim = &twistToRight;
			if (position.y < SCREEN_HEIGHT / 2) {
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
			//if (position.y < 255)currentAnim = &fly;
			//if (position.y >= 255)currentAnim = &loopToRight;
			currentAnim = &fly;
			xRecorrido = (spawnPos.x - position.x);

			position.y += sqrt(xRecorrido / 150);
			position.x += 6;
			break;
		}

		break;
	case 2:
		switch (FASE) {
		case 1:
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
			//if (position.y > 105)currentAnim = &fly;
			//if (position.y <= 105)currentAnim = &loopToRight;
			currentAnim = &fly;
			xRecorrido = (spawnPos.x - position.x);

			position.y -= sqrt(xRecorrido / 100);
			position.x += 5 + SCREEN_SPEED;
			break;
		}

		break;
	case 3:
		switch (FASE) {
		case 1:
			currentAnim = &fly;
			if (xRecorrido < 300) {
				xRecorrido += 4;

				position.x += 4;

			}
			else
				FASE = 2;
			break;
		case 2:
			currentAnim = &twistToLeft;
			if (position.y > SCREEN_HEIGHT / 2) {
				xRecorrido += 5;

				position.y -= sqrt(position.x / 150);
				position.x += 5;
			}
			else
				FASE = 3;

			break;
		case 3:
			if (position.y > 100) {
				xRecorrido += 3;
				position.y -= sqrt(position.x / 100);
				position.x += 3;
			}
			else
				FASE = 4;
			break;

		case 4:
			if (xRecorrido < 700) {
				xRecorrido += 3;

				position.y = position.y; // sqrt(xRecorrido / 50);
				position.x -= 3;
			}
			else
				FASE = 5;
			break;
		case 5:
			//if (position.y > 105)currentAnim = &fly;
			//if (position.y <= 105)currentAnim = &loopToRight;
			currentAnim = &flyInvers;
			xRecorrido = position.x;

			position.y += sqrt(xRecorrido / 500);
			position.x -= 5;
			break;
		}
		break;
	case 4:
		switch (FASE) {
		case 1:
			currentAnim = &fly;
			if (xRecorrido < 760) {
				xRecorrido = position.x;

				position.x += 4;

			}
			else
				FASE = 2;
			break;
		case 2:
			currentAnim = &twistToLeftToDown;
			if (position.y < SCREEN_HEIGHT / 2) {
				xRecorrido = position.x;

				position.y += sqrt(xRecorrido / 150);
				position.x += 4;
			}
			else
				FASE = 3;

			break;
		case 3:
			if (position.y < 330) {
				xRecorrido = position.x;
				position.y += sqrt(xRecorrido / 200);
				position.x -= 1;
			}
			else
				FASE = 4;
			break;

		case 4:
			if (xRecorrido > 960) {
				xRecorrido = position.x;

				position.y = position.y; // sqrt(xRecorrido / 50);
				position.x -= 3;
			}
			else
				FASE = 5;
			break;
		case 5:
			//if (position.y > 105)currentAnim = &fly;
			//if (position.y <= 105)currentAnim = &loopToRight;
			currentAnim = &flyInvers;
			xRecorrido = position.x;

			position.y -= sqrt(xRecorrido / 500);
			position.x -= 5;
			break;
		}
		break;
	}
}

