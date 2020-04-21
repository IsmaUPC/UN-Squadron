#include "Enemy_BrownShip.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_BrownShip::Enemy_BrownShip(int x, int y,int _pattern) : Enemy(x, y,_pattern)
{
	flyInvers.PushBack({487,165,61,18});
	currentAnim = &flyInvers;
	flyInvers.speed = 0.01f;

	fly.PushBack({ 559,165,62,18 });
	//currentAnim = &fly;
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
	twistToRight.speed = 0.02f;
	   
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
	twistToLeft.speed = 0.02f;

	loopToRight.PushBack({ 559,165,62,18 });
	loopToRight.PushBack({ 697,157,62, 47 });
	loopToRight.PushBack({ 559,188,62, 18 });
	loopToRight.PushBack({ 66,155,62, 49 });
	loopToRight.loop = true;
	loopToRight.speed = 0.02f;

	loopToLeft.PushBack({ 487,165,61,18 });
	loopToLeft.PushBack({ 348,157,62, 47 });
	loopToLeft.PushBack({ 487,188,61, 18 });
	loopToLeft.PushBack({ 979,155,62, 49 });
	loopToLeft.loop = true;
	loopToLeft.speed = 0.02f;

	// TODO 3: Have the Brown Cookies describe a path in the screen
	path.PushBack({-0.8f , -0.5f}, 100, &flyInvers);
	path.PushBack({ -0.8f , 0.5f }, 100, &flyInvers);
	collider = App->collisions->AddCollider({0, 0, 61, 18}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_BrownShip::Update()
{

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_BrownShip::move()
{

	switch (pattern) {
	case 0:
		path.Update();
		position = spawnPos + path.GetRelativePosition();

		break;

	case 1:

		break;
	}

}
