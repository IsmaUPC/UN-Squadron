#include "Enemy_MiniBoss1.h"

#include "Application.h"
#include "ModuleCollisions.h"


Enemy_MiniBoss1::Enemy_MiniBoss1(float x, float y, int _pattern) :Enemy(x, y, _pattern)
{
	//Animation
	FirsAnim.PushBack({ 559,299,220,80 });
	currentAnim = &FirsAnim;

	collider = App->collisions->AddCollider({ 0, 0, 220, 80 }, Collider::Type::ENEMY, (Module*)App->enemies);   
	position.x -= 330;
	
}


void Enemy_MiniBoss1::Update() {

	move();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_MiniBoss1::move() 
{
	float speedPatternX[6] = { 1.6f, 1.25f, 1, 1.25f, 0.5f, 1.5f };
	float speedPatternY[6] = { 2.f, -2.f, 2.f, -2.f, 2.f, -2.f };
	if (collider->pendingToDelete != true)
		resizeCollider();
	int i = FASE;
	switch (pattern) {
	case 0:
		yRecorrido += 2;
		
		if (yRecorrido >= i * 300 && yRecorrido < (i+1) * 300)
		{
			position.y += speedPatternY[i];
			position.x += speedPatternX[i];
			if (yRecorrido >= ((i+1) * 300)-2) FASE++;
		}
		break;

	}

}