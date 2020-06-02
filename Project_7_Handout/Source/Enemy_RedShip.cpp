#include "Enemy_RedShip.h"
#include "Application.h"
#include "ModuleCollisions.h"

#include "ModuleRender.h"


Enemy_RedShip::Enemy_RedShip(int x, int y,int _pattern) : Enemy(x, y,_pattern)
{
	flyInvers.PushBack({ 790,29,66,39 });
	currentAnim = &flyInvers;
	flyInvers.speed = 0.01f;


	fly.PushBack({ 252,29,66,39 });
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
	twistToRight.speed = 0.13f;
	

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
	twistToLeft.speed = 0.13f;

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
	twistToRightToDown.speed = 0.13f;

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
	twistToLeftToDown.speed = 0.13f;

	//path.PushBack({ -0.5f , 0.0f }, 125, &flyInvers);

	//path.PushBack({ 1.0f , 0.0f }, 250, &walkBack);
	collider = App->collisions->AddCollider({ 0, 0, 66, 39 }, Collider::Type::ENEMY, (Module*)App->enemies);
	int w = collider->rect.w;
	int h = collider->rect.h;
	if(pattern>=3)position.x -= SCREEN_WIDTH+100;
	if (pattern == 2)pattern = 4, toRight = true, direction = -1, TOP = 250;
	if (pattern == 1)pattern = 3 , toRight = true, direction = -1, TOP = 250;
	
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

	if (collider->pendingToDelete != true)
		resizeCollider();

	switch (pattern) {
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
			if(toRight==true)currentAnim = &flyInvers;
			else currentAnim = &fly;
			if (xRecorrido < 253-TOP) {
				xRecorrido += 5;
				position.x += multiSpeed * 4 * direction;
			}
			else
				FASE = 2;
			break;
		case 2:
			if (toRight == true) currentAnim = &twistToRight;
			else currentAnim = &twistToLeft;
			if (position.y > SCREEN_HEIGHT / 2) {
				xRecorrido += 5;
				position.y -= multiSpeed * 2;
				position.x += multiSpeed * 4 * direction;
			}
			else
				FASE = 3;

			break;
		case 3:
			if (position.y > 110) {
				xRecorrido += 2;
				position.y -= multiSpeed * 2;
				position.x -= multiSpeed * 2 * direction;
			}
			else
				FASE = 4;
			break;

		case 4:
			if (toRight == true) currentAnim = &fly;
			else currentAnim = &flyInvers;
			position.y += multiSpeed * 1 * direction;
			position.x -= multiSpeed * 5 * direction;
			break;
		}
		break;
	case 4:
		switch (FASE) {
		case 1:
			if(toRight==true) currentAnim = &flyInvers;
			else currentAnim = &fly;
			if (xRecorrido < 253-TOP) {
				xRecorrido += 5;
				position.x += multiSpeed * 4 * direction;
			}
			else
				FASE = 2;
			break;
		case 2:
			if (toRight == true) currentAnim = &twistToRightToDown;
			else currentAnim = &twistToLeftToDown;
			if (position.y < SCREEN_HEIGHT / 2) {
				xRecorrido += 5;
				position.y += multiSpeed * 2;
				position.x += multiSpeed * 4*direction;
			}
			else
				FASE = 3;

			break;
		case 3:
			if (position.y < 330) {
				xRecorrido += 2;
				position.y += multiSpeed * 2;
				position.x -= multiSpeed * 2 * direction;
			}
			else
				FASE = 4;
			break;
		case 4:
			if (toRight == true) currentAnim = &fly;
			else currentAnim = &flyInvers;
			position.y -= multiSpeed * 1 * direction;
			position.x -= multiSpeed * 5 * direction;
			break;
		}
		break;
	}
}
