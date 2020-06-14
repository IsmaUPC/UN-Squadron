#include "ModuleCollisions.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_Scancode.h"

ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;


	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	for (int i = 0; i < Collider::Type::MAX; i++) {
		for (int j = 0; j < Collider::Type::MAX; j++) {
			matrix[i][j] = false;
		}
	}

	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::M_BOSS1] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::M_BOSS1_SHOT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::BOSS1] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::BOSS2] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::BOSS1_SHOT_BALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::BOSS_BURSTSHOT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::BOSS_SHOT_LASER] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::BOSS_MOAB] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::BOSS2_BOMBS] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::POWERUP] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::POWERUP_B] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::BOSS2_MISILE] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::BOSS2_MISILE_EXPLOSION] = true;


	matrix[Collider::Type::POWERUP][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::POWERUP_B][Collider::Type::PLAYER] = true;

	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::SW_BOMB] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::SW_CEILING] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::SW_GUNPOD] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::SW_S_SHELL] = true;

	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::M_BOSS1_SHOT] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::M_BOSS1] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::BOSS1] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::BOSS2] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::BOSS_MOAB] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::BOSS2_MISILE] = true;

	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER] = true;

	matrix[Collider::Type::M_BOSS1_SHOT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::M_BOSS1_SHOT][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::M_BOSS1_SHOT][Collider::Type::SW_BOMB] = true;
	matrix[Collider::Type::M_BOSS1_SHOT][Collider::Type::SW_CEILING] = true;
	matrix[Collider::Type::M_BOSS1_SHOT][Collider::Type::SW_GUNPOD] = true;
	matrix[Collider::Type::M_BOSS1_SHOT][Collider::Type::SW_S_SHELL] = true;

	matrix[Collider::Type::BOSS1][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::BOSS1][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::BOSS1][Collider::Type::SW_BOMB] = true;
	matrix[Collider::Type::BOSS1][Collider::Type::SW_CEILING] = true;
	matrix[Collider::Type::BOSS1][Collider::Type::SW_GUNPOD] = true;
	matrix[Collider::Type::BOSS1][Collider::Type::SW_S_SHELL] = true;

	matrix[Collider::Type::SW_BOMB][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::SW_BOMB][Collider::Type::M_BOSS1] = true;
	matrix[Collider::Type::SW_BOMB][Collider::Type::BOSS1] = true;
	matrix[Collider::Type::SW_BOMB][Collider::Type::M_BOSS1_SHOT] = true;
	matrix[Collider::Type::SW_BOMB][Collider::Type::BOSS1_SHOT_BALL] = true;
	matrix[Collider::Type::SW_BOMB][Collider::Type::BOSS_MOAB] = true;
	matrix[Collider::Type::SW_BOMB][Collider::Type::BOSS2] = true;
	matrix[Collider::Type::SW_BOMB][Collider::Type::BOSS2_MISILE] = true;

	matrix[Collider::Type::SW_CEILING][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::SW_CEILING][Collider::Type::M_BOSS1] = true;
	matrix[Collider::Type::SW_CEILING][Collider::Type::BOSS1] = true;
	matrix[Collider::Type::SW_CEILING][Collider::Type::M_BOSS1_SHOT] = true;
	matrix[Collider::Type::SW_CEILING][Collider::Type::BOSS1_SHOT_BALL] = true;
	matrix[Collider::Type::SW_CEILING][Collider::Type::BOSS_MOAB] = true;
	matrix[Collider::Type::SW_CEILING][Collider::Type::BOSS2] = true;
	matrix[Collider::Type::SW_CEILING][Collider::Type::BOSS2_MISILE] = true;

	matrix[Collider::Type::SW_GUNPOD][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::SW_GUNPOD][Collider::Type::M_BOSS1] = true;
	matrix[Collider::Type::SW_GUNPOD][Collider::Type::BOSS1] = true;
	matrix[Collider::Type::SW_GUNPOD][Collider::Type::M_BOSS1_SHOT] = true;
	matrix[Collider::Type::SW_GUNPOD][Collider::Type::BOSS1_SHOT_BALL] = true;
	matrix[Collider::Type::SW_GUNPOD][Collider::Type::BOSS_MOAB] = true;
	matrix[Collider::Type::SW_GUNPOD][Collider::Type::BOSS2] = true;
	matrix[Collider::Type::SW_GUNPOD][Collider::Type::BOSS2_MISILE] = true;

	matrix[Collider::Type::SW_S_SHELL][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::SW_S_SHELL][Collider::Type::M_BOSS1] = true;
	matrix[Collider::Type::SW_S_SHELL][Collider::Type::BOSS1] = true;
	matrix[Collider::Type::SW_S_SHELL][Collider::Type::M_BOSS1_SHOT] = true;
	matrix[Collider::Type::SW_S_SHELL][Collider::Type::BOSS1_SHOT_BALL] = true;
	matrix[Collider::Type::SW_S_SHELL][Collider::Type::BOSS_MOAB] = true;
	matrix[Collider::Type::SW_S_SHELL][Collider::Type::BOSS2] = true;
	matrix[Collider::Type::SW_S_SHELL][Collider::Type::BOSS2_MISILE] = true;

	matrix[Collider::Type::M_BOSS1][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::M_BOSS1][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::M_BOSS1][Collider::Type::SW_BOMB] = true;
	matrix[Collider::Type::M_BOSS1][Collider::Type::SW_CEILING] = true;
	matrix[Collider::Type::M_BOSS1][Collider::Type::SW_GUNPOD] = true;
	matrix[Collider::Type::M_BOSS1][Collider::Type::SW_S_SHELL] = true;


	matrix[Collider::Type::BOSS1_SHOT_BALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::BOSS1_SHOT_BALL][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::BOSS1_SHOT_BALL][Collider::Type::SW_BOMB] = true;
	matrix[Collider::Type::BOSS1_SHOT_BALL][Collider::Type::SW_CEILING] = true;
	matrix[Collider::Type::BOSS1_SHOT_BALL][Collider::Type::SW_GUNPOD] = true;
	matrix[Collider::Type::BOSS1_SHOT_BALL][Collider::Type::SW_S_SHELL] = true;

	matrix[Collider::Type::BOSS_SHOT_LASER][Collider::Type::PLAYER] = true;

	matrix[Collider::Type::BOSS_BURSTSHOT][Collider::Type::PLAYER] = true;

	matrix[Collider::Type::BOSS_MOAB][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::BOSS_MOAB][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::BOSS_MOAB][Collider::Type::SW_BOMB] = true;
	matrix[Collider::Type::BOSS_MOAB][Collider::Type::SW_CEILING] = true;
	matrix[Collider::Type::BOSS_MOAB][Collider::Type::SW_GUNPOD] = true;
	matrix[Collider::Type::BOSS_MOAB][Collider::Type::SW_S_SHELL] = true;

	matrix[Collider::Type::BOSS2][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::BOSS2][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::BOSS2][Collider::Type::SW_BOMB] = true;
	matrix[Collider::Type::BOSS2][Collider::Type::SW_CEILING] = true;
	matrix[Collider::Type::BOSS2][Collider::Type::SW_GUNPOD] = true;
	matrix[Collider::Type::BOSS2][Collider::Type::SW_S_SHELL] = true;

	matrix[Collider::Type::BOSS2_BOMBS][Collider::Type::PLAYER] = true;

	matrix[Collider::Type::BOSS2_MISILE][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::BOSS2_MISILE][Collider::Type::PLAYER_SHOT] = true;

	matrix[Collider::Type::BOSS2_MISILE_EXPLOSION][Collider::Type::PLAYER] = true;

	matrix[Collider::Type::BOSS2_MISILE][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::BOSS2_MISILE][Collider::Type::SW_GUNPOD] = true;
	matrix[Collider::Type::BOSS2_MISILE][Collider::Type::SW_S_SHELL] = true;
	matrix[Collider::Type::BOSS2_MISILE][Collider::Type::SW_BOMB] = true;
	matrix[Collider::Type::BOSS2_MISILE][Collider::Type::SW_CEILING] = true;
}


// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

update_status ModuleCollisions::PreUpdate()
{
	// Remove all colliders scheduled for detection
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if(colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for(uint k = i+1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if(colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (matrix[c1->type][c2->type] && c1->Intersects(c2->rect))
			{
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c1->listeners[i] != nullptr)
						c1->listeners[i]->OnCollision(c1, c2);

				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c2->listeners[i] != nullptr)
						c2->listeners[i]->OnCollision(c2, c1);
			}
		}
	}
	
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleCollisions::Update()
	
{	//Press F1 to switch debug mode
	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN) {
		debug = !debug;
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleCollisions::PostUpdate()
{
	if (debug) {
		DebugDraw();
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 80;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
			continue;
		
		switch(colliders[i]->type)
		{
			case Collider::Type::NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
			case Collider::Type::WALL: case Collider::Type::POWERUP: case Collider::Type::POWERUP_B: // blue
				App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
			case Collider::Type::PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			case Collider::Type::ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			case Collider::Type::PLAYER_SHOT: case Collider::Type::SW_BOMB: case Collider::Type::SW_CEILING: case Collider::Type::SW_GUNPOD: case Collider::Type::SW_S_SHELL:
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
			case Collider::Type::ENEMY_SHOT: // magenta
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
			case Collider::Type::M_BOSS1_SHOT: // cian
			App->render->DrawQuad(colliders[i]->rect, 10, 255, 255, alpha);
			break;
			case Collider::Type::M_BOSS1: // red
				App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			case Collider::Type::BOSS1: // red
				App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;

			case Collider::Type::BOSS2: // red
				App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
				break;
			case Collider::Type::BOSS1_SHOT_BALL: // cian
				App->render->DrawQuad(colliders[i]->rect, 10, 255, 255, alpha);
			break;

		}
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}

void ModuleCollisions::RemoveCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
}