#include "Enemy_Template.h"

#include "Application.h"
#include "ModuleCollisions.h"


Enemy_Template::Enemy_Template(int x, int y, int _pattern) :Enemy(x, y, _pattern)
{
	//Animation
	FirsAnim.PushBack({ 0,0,0,0 });
	currentAnim = &FirsAnim;



	collider = App->collisions->AddCollider({ 0, 0, 66, 39 }, Collider::Type::ENEMY, (Module*)App->enemies);
}


void Enemy_Template::Update(){

	move();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_Template::move(){

	switch (pattern){
	case 0:
		currentAnim = path.GetCurrentAnimation();
		waveRatio += waveRatioSpeed;
		path.Update();
		position = spawnPos + path.GetRelativePosition();

		position.x -= 1;
		break;

	case 1:

		break;
	}


}