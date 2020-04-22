#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"

#define MAX_LISTENERS 5

class Module;
class Enemy;

struct Collider
{
	enum Type
	{
		NONE = -1,
		WALL,
		PLAYER,
		ENEMY,
		PLAYER_SHOT,
		ENEMY_SHOT,

		MAX
	};

	//Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);
	Collider(SDL_Rect rectangle, Type type, Enemy* listener = nullptr);

	void SetPos(int x, int y);

	bool Intersects(const SDL_Rect& r) const;

	void AddListener(Module* listener);

	void AddListener(Enemy* listener);

	//Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	Module* listeners[MAX_LISTENERS] = { nullptr };
	Enemy* listenersE[MAX_LISTENERS] = { nullptr };
};


#endif // !__COLLIDER_H__

