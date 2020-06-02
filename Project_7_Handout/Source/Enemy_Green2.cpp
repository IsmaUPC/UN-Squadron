#include "Enemy_Green2.h"

#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"
#include <math.h>
#define PI 3.141592

Enemy_Green2::Enemy_Green2(int x, int y, int _pattern) :Enemy(x, y, _pattern)
{
	//Animation
	FirsAnim.PushBack({ 891,421,54,14 });
	currentAnim = &FirsAnim;

	Up.PushBack({ 1011,421,54,19});
	Up.speed = 0.08;
	Up.loop = false;

	Down.PushBack({951, 421, 54, 21});
	Down.speed = 0.08;
	Down.loop = false;

	collider = App->collisions->AddCollider({ 0, 0, 54, 14 }, Collider::Type::ENEMY, (Module*)App->enemies);
}


void Enemy_Green2::Update() {

	move();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_Green2::move() {
	following = (position.y < App->player->position.y-20 && position.y > App->player->position.y + 20) ? -1 : 1;
	switch (pattern) {
	case 0:
		if (yRecorrido < 110)
		{
			yRecorrido++;
			position.x += -1;
			position.y += 1;
		}
		else yRecorrido = 0, pattern = 2;
	case 1:
		if (xRecorrido < 110)
		{
			xRecorrido++;
			position.x += -1;
		}
		else
		{
			if (direction == 1)pattern = 2;
			else pattern = 7;
		}
		break;
	case 2:
		if(yRecorrido < 10)currentAnim = &Down;
		else currentAnim = &FirsAnim;
		if (yRecorrido < 25)
		{
			yRecorrido++;
			position.y += 2;
			position.x += SCREEN_SPEED;
		}
		else pattern = 3;
		break;
	case 3:
		if (yRecorrido < 55)currentAnim = &Up;
		else currentAnim = &FirsAnim;
		if (yRecorrido < 75)
		{
			yRecorrido++;
			position.y -= 2;
			position.x += 1;
		}
		else pattern = 4;
		break;
	case 4:
		if (yRecorrido < 105)currentAnim = &Down;
		else currentAnim = &FirsAnim;
		if (yRecorrido < 125)
		{
			yRecorrido++;
			position.y += 2;
			position.x += 1;
		}
		else pattern = 5;
		break;
	case 5:
		if (yRecorrido < 155)currentAnim = &Up;
		else currentAnim = &FirsAnim;
		if (yRecorrido < 175)
		{
			yRecorrido++;
			position.y -= 2;
			position.x += 1;
		}
		else pattern = 6;
		break;
	case 6:
		if (yRecorrido < 185)currentAnim = &Down;
		else currentAnim = &FirsAnim;
		if (yRecorrido < 200)
		{
			yRecorrido++;
			position.y += 2;
			position.x += 1;
		}
		else pattern = 7;
		break;
	case 7:
		currentAnim = &Up;
		if (grados != 90)
		{
			radianes = grados * PI / 180;
			position.x -= radio * sin(radianes);
			position.y -= (radio * cos(radianes)*direction)*following;
			grados += 2.5;
			if (grados == 360)grados = 0;
		}
		else grados = 270, pattern = 8;
		break;
	case 8:///////////////////////////////////
		currentAnim = &FirsAnim;
		if (xRecorrido < 155)
		{
			xRecorrido++;
			position.x -= 3;
		}
		else
		{
			pattern = 9;
			if (roundTwo==false)radio = 1.7;
			else radio = 3.5;
		}
		break;
	case 9:
		currentAnim = &Up;
		if (grados != 90)
		{
			radianes = grados * PI / 180;
			position.x += radio * sin(radianes);
			position.y -= (radio * cos(radianes))*following;
			grados += 2.5;
			if (grados == 360)grados = 0;
		}
		else
		{
			if (roundTwo==false)pattern = 10;
			else xRecorrido=0,pattern = 11;
		}
		break;
	case 10:
		radio = 2.5;
		if(radio * cos(radianes)<0)currentAnim = &Down;
		else currentAnim = &Up;
		if (grados != 630)
		{
			radianes = grados * PI / 180;
			position.x += 2.6;
			position.y -= radio * cos(radianes);
			grados += 2.5;
		}
		else xRecorrido=110, yRecorrido=0, direction=-1, grados=270,radio=4.8,roundTwo=true,pattern = 2;
		break;
	case 11:
		currentAnim = &Up;
		if (xRecorrido < 60)
		{
			xRecorrido++;
			position.x += 3.5;
			position.y -= 3*following;
		}
		else pattern = 10;
	}
}