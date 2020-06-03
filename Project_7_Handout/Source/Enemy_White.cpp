#include "Enemy_White.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include <math.h>
#include "ModulePlayer.h"
#define PI 3.141592

Enemy_White::Enemy_White(int x, int y, int _pattern) :Enemy(x, y, _pattern)
{
	//Animation
	FirsAnim.PushBack({ 891,394,52,19 });
	currentAnim = &FirsAnim;

	Up.PushBack({ 951,394,52,23 });

	Down.PushBack({ 1011, 394, 52, 21 });


	collider = App->collisions->AddCollider({ 0, 0, 52, 39 }, Collider::Type::ENEMY, (Module*)App->enemies);
	position.x -= SCREEN_WIDTH + 60;
}


void Enemy_White::Update() {

	move();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_White::move() {

	switch (pattern) {
	case 0:
		if (xRecorrido < 50)
		{
			xRecorrido++;
			position.x += 2;
			position.y += 0.5;
		}
		else pattern = 1;
		break;
	case 1:
		if (xRecorrido < 80)
		{
			xRecorrido++;
			position.x += speed;
			position.y -= 1;
		}
		else pattern = 2;
		break;
	case 2:
		currentAnim = &Down;
		if (position.y > App->player->position.y+20 || position.y < App->player->position.y - 20)
		{
			position.x += SCREEN_SPEED;
			if (position.y < App->player->position.y) position.y += 2;
			if (position.y > App->player->position.y) position.y -= 2;
		}
		else pattern = 3;
		break;
	case 3:
		if (radio * cos(radianes) < 0)currentAnim = &Down;
		else currentAnim = &Up;
		if (grados != angulo)
		{
			radianes = grados * PI / 180;
			position.x += speed;
			position.y += radio * cos(radianes);
			grados += 2.5;
		}
		else radio = 4, speed = 3, grados=135, pattern = 3;
		break;
	}


}