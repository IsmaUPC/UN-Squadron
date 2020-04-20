#include "PatternEnemy.h"


void move(Enemy_RedBird* enemy, int pattern){

	Enemy_RedBird* redbird = enemy;

	switch (pattern){
	case 1:

		redbird->waveRatio += redbird->waveRatioSpeed;

		redbird->position.y = redbird->spawnPos.y + (redbird->waveHeight * sinf(redbird->waveRatio));
		redbird->position.x -= 1;

		break;
	case 2:
		redbird->position = redbird->spawnPos;

		break;

	default:
		break;
	}
}

void move(Enemy_BrownShip* enemy, int pattern){

	Enemy_BrownShip* BrownShip = enemy;

}
