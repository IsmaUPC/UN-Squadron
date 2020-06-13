#include "Enemy_BrownShip.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_BrownShip::Enemy_BrownShip(int x, int y,int _pattern) : Enemy(x, y,_pattern)
{
	flyInvers.PushBack({487,165,61,18});
	flyInvers.speed = 0.01f;
	currentAnim = &flyInvers;

	fly.PushBack({ 559,165,62,18 });
	fly.speed = 0.01f;

	flyDown.PushBack({ 487,188,61, 18 });
	flyDown.speed = 0.01f;

	flyAhead.PushBack({ 348,157,62, 47 });
	flyAhead.speed = 0.01f;

	flyAback.PushBack({ 979,155,62, 49 });
	//flyAback.PushBack({ 1045,171,62, 33 });
	flyAback.speed = 0.01f;

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

	loopToRight.PushBack({ 0,541,62,49 });
	loopToRight.PushBack({ 62,541,62, 49 });
	loopToRight.PushBack({ 124,541,62, 49 });
	loopToRight.PushBack({ 186,541,62, 49 });
	loopToRight.PushBack({ 248,541,62, 49 });
	loopToRight.PushBack({ 310,541,62, 49 });
	loopToRight.PushBack({ 372,541,62, 49 });
	loopToRight.PushBack({ 434,541,62, 49 });
	loopToRight.loop = true;
	loopToRight.speed = 0.25f;

	loopToLeft.PushBack({ 1045,541,62, 49 });
	loopToLeft.PushBack({ 983,541,62, 49 });
	loopToLeft.PushBack({ 921,541,62, 49 });
	loopToLeft.PushBack({ 859,541,62, 49 });
	loopToLeft.PushBack({ 797,541,62, 49 });
	loopToLeft.PushBack({ 735,541,62, 49 });
	loopToLeft.PushBack({ 673,541,62, 49 });
	loopToLeft.PushBack({ 611,541,62, 49 });
	loopToLeft.loop = true;
	loopToLeft.speed = 0.25f;

	// TODO 3: Have the Brown Cookies describe a path in the screen
	//path.PushBack({-0.8f , -0.5f}, 100, &flyInvers);
	//path.PushBack({ -0.8f , 0.5f }, 100, &flyInvers);
	collider = App->collisions->AddCollider({0, 0, 61, 18}, Collider::Type::ENEMY, (Module*)App->enemies);
	if (pattern == 0)pattern = 1, angulo = 0.5;
	if (pattern == 3&&(position.y==160 || position.y == 100))isTwist=true;
	if (pattern == 4 && (position.y == 160 || position.y == 100))pattern = 3, isTwist2 = true, direction = -1;
	if (pattern == 4)pattern = 3, direction = -1;
	desacelaracion = 3;
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

	if (collider->pendingToDelete != true)
		resizeCollider();

	switch (pattern) {
	case 1:
		switch (FASE) {
		case 1:
			if (position.y == 200)currentAnim = &flyDown, TOP = 150;
			else if (position.y == 160)currentAnim = &flyAhead, TOP = 150;
			else currentAnim = &flyInvers, TOP = 100;
			if (xRecorrido < TOP) {
				xRecorrido += 3;
				position.x -= 3;

			}
			else
				FASE = 2;
			break;
		case 2:
			currentAnim = &twistToRight;
			if (yRecorrido < 140) {
				yRecorrido += 2.3;
				position.y += angulo;
				position.x -= desacelaracion;
				desacelaracion -= 0.02;
			}
			else
				FASE = 3;

			break;
		case 3:
			if (yRecorrido < 160) {
				yRecorrido += 2;
				position.y += angulo;
				position.x += desacelaracion;
				desacelaracion += 0.06;
			}
			else
				FASE = 4;
			break;

		case 4:
			currentAnim = &loopToRight;
			
			position.y += angulo;
			position.x += 5;
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
		switch (FASE) {
		case 1:
			if (isTwist == true)currentAnim = &flyAback;
			else if (position.y == 100 || position.y == 160)currentAnim = &flyAhead;
			else if (position.y == 140 || position.y == 200)currentAnim = &flyDown;
			else if(isTwist==false)currentAnim = &flyInvers;
			if (xRecorrido < 150) {
				xRecorrido += 3;
				position.x -= 3;

			}
			else
				FASE = 2;
			break;
		case 2:
			currentAnim = &twistToRight;
			if (yRecorrido < 140) {
				yRecorrido += 2.3;
				position.y -= direction*1.2;
				position.x -= desacelaracion;
				desacelaracion -= 0.02;
			}
			else
				FASE = 3;

			break;
		case 3:
			if (yRecorrido < 180) {
				yRecorrido += 2;
				position.y -= direction*1;
				position.x += desacelaracion;
				desacelaracion += 0.06;
			}
			else
				FASE = 4;
			break;

		case 4:
			currentAnim = &loopToRight;

			position.y -= direction*0.6;
			position.x += 6;
			break;
		}
		break;
	}
}
