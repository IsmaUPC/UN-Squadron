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
	//currentAnim = &fly;
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
	twistToRight.speed = 0.08f;
	currentAnim = &twistToRight;

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
	twistToLeft.speed = 0.02f;

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
	twistToRightToDown.speed = 0.08f;

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
	twistToLeftToDown.speed = 0.02f;

	path.PushBack({ -0.5f , 0.0f }, 125, &flyInvers);

	//path.PushBack({ 1.0f , 0.0f }, 250, &walkBack);
	collider = App->collisions->AddCollider({ 0, 0, 66, 39 }, Collider::Type::ENEMY, (Module*)App->enemies);
	
	position.y = 350;
	
	//
}

void Enemy_RedShip::Update()
{

	move();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();

}

void Enemy_RedShip::move(){
	spawnPos.x +=SCREEN_SPEED;

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
		if (FASE == 1){
			if (position.y >= SCREEN_HEIGHT / 2) {
				
				xRecorrido =  (spawnPos.x- position.x);
				//if (xRecorrido >= 100)
				//if (xRecorrido > 0)
					position.y -= sqrt(xRecorrido/50);

				position.x -= 2;
			}else{
				FASE = 2;
			}
		}else{
			xRecorrido--;

			//if (xRecorrido >= 100) 
			//if (xRecorrido > 0)
				position.y -= sqrt(xRecorrido/50);
			
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
		switch (FASE){
		case 1:
			if (xRecorrido < 150) {
				xRecorrido = (spawnPos.x - position.x);

				position.x -= 2;

			}else
				FASE = 2;
			break;
		case 2:
			if (position.y > 250) {
				xRecorrido = (spawnPos.x - position.x);

				position.y -= sqrt(xRecorrido / 50);
				position.x -= 1;
			}else
				FASE = 3;
			
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
				position.x += 1;
			}
			else
				FASE = 5;
			break;
		case 5:

			xRecorrido = (spawnPos.x - position.x) ;

			position.y -= sqrt(xRecorrido / 80);
			position.x += 3+SCREEN_SPEED ;
			break;
		}

			break;
	case 3:

		if (FASE == 1){
			if (!startmove) {
				startmove = true;
				n = 270;
			}

			if (n <= 360){

			xRecorrido = (spawnPos.x - position.x);
			n += 5;
			alpha = n * M_PI / 180.0f;

			position.x += (position.y * cos(alpha))/40;
			position.y -= 2;
			}else {
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
			position.x += (position.y * cos(alpha))/40;
			position.y -= 2;

		}


		break;

	}
}
