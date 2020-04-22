#include "Enemy_RedShip.h"
#include "Application.h"
#include "ModuleCollisions.h"

#include "ModuleRender.h"


Enemy_RedShip::Enemy_RedShip(int x, int y,int _pattern) : Enemy(x, y,_pattern)
{
	flyInvers.PushBack({ 790,29,66,39 });
	//currentAnim = &flyInvers;
	flyInvers.speed = 0.01f;


	fly.PushBack({ 252,29,66,39 });
	currentAnim = &fly;
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
	twistToRight.speed = 0.15f;
	

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
	twistToLeft.speed = 0.15f;

	twistToRightToDown.PushBack({ 722,469,62, 37 });
	twistToRightToDown.PushBack({ 670,469,48, 52 });
	twistToRightToDown.PushBack({ 633,469,31, 62 });
	twistToRightToDown.PushBack({ 610,469,19, 68 });
	twistToRightToDown.PushBack({ 579,469,25, 68 });
	twistToRightToDown.PushBack({ 534,469,39, 68 });
	twistToRightToDown.PushBack({ 503,469,25, 68 });
	twistToRightToDown.PushBack({ 478,469,19, 68 });
	twistToRightToDown.PushBack({ 443,469,31, 62 });
	twistToRightToDown.PushBack({ 390,469,47, 52 });
	twistToRightToDown.PushBack({ 324,469,52, 37 });
	twistToRightToDown.PushBack({ 252,469,66,39 });
	twistToRightToDown.loop = false;
	twistToRightToDown.speed = 0.15f;

	twistToLeftToDown.PushBack({ 324,469,52, 37 });
	twistToLeftToDown.PushBack({ 390,469,47, 52 });
	twistToLeftToDown.PushBack({ 443,469,31, 62 });
	twistToLeftToDown.PushBack({ 478,469,19, 68 });
	twistToLeftToDown.PushBack({ 503,469,25, 68 });
	twistToLeftToDown.PushBack({ 534,469,39, 68 });
	twistToLeftToDown.PushBack({ 579,469,25, 68 });
	twistToLeftToDown.PushBack({ 610,469,19, 68 });
	twistToLeftToDown.PushBack({ 633,469,31, 62 });
	twistToLeftToDown.PushBack({ 670,469,48, 52 });
	twistToLeftToDown.PushBack({ 722,469,62, 37 });
	twistToLeftToDown.PushBack({ 790,469,66,39 });
	twistToLeftToDown.loop = false;
	twistToLeftToDown.speed = 0.15f;

	//path.PushBack({ -0.5f , 0.0f }, 125, &flyInvers);

	//path.PushBack({ 1.0f , 0.0f }, 250, &walkBack);
	collider = App->collisions->AddCollider({ 0, 0, 66, 39 }, Collider::Type::ENEMY, (Module*)App->enemies);
	position.x -= SCREEN_WIDTH;
}

void Enemy_RedShip::Update()
{

	move();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();

}

void Enemy_RedShip::move() {
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
			if (xRecorrido < 600) {
				xRecorrido = position.x;

				position.x += 4;

			}
			else
				FASE = 2;
			break;
		case 2:
			currentAnim = &twistToLeft;
			if (position.y > SCREEN_HEIGHT/2) {
				xRecorrido = position.x;

				position.y -= sqrt(xRecorrido / 30);
				position.x += 4;
			}
			else
				FASE = 3;

			break;
		case 3:
			if (position.y > 150) {
				xRecorrido = position.x;
				position.y -= sqrt(xRecorrido / 50);
				position.x -= 3;
			}
			else
				FASE = 4;
			break;

		case 4:
			if (xRecorrido > 200) {
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
			currentAnim = &fly;
			xRecorrido = position.x;

			position.y += sqrt(xRecorrido / 100);
			position.x -= 3;
			break;
		}
		break;
	}
}
