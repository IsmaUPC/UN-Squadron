#ifndef _PATTERNENEMY_H__
#define _PATTERNENEMY_H__

#include "Enemy_BrownShip.h"
#include "Enemy_RedBird.h"
#include "Mech.h"

void move(Enemy_RedBird* enemy, int pattern);
void move(Enemy_BrownShip* enemy, int pattern);

#endif // _PATTERNENEMY_H__
