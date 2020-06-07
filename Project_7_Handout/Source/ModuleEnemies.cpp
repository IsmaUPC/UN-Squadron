#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include <SDL_mixer\include\SDL_mixer.h>
#include "Enemy.h"
#include "Enemy_RedShip.h"
#include "Enemy_GreenShip.h"
#include "Enemy_BrownShip.h"
#include "Enemy_YellowShip.h"
#include "Enemy_BlueShip.h"
#include "Enemy_MiniBoss1.h"
#include "Enemy_FinalBoss1.h"
#include "Enemy_Green2.h"
#include "Enemy_White.h"
#include "Enemy_FinalBoss2.h"



ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{

}

bool ModuleEnemies::Start()
{
	textureEnemies = App->textures->Load("Assets/UNSquadronSpritesEnemies.png");
	finalBoss1= App->textures->Load("Assets/FinalBoss1.png");
	finalBoss2 = App->textures->Load("Assets/FinalBoss2.png");
	enemyDestroyedFx = App->audio->LoadFx("Assets/06_Effect_Explosion_Enemies.wav");

	return true;
}

update_status ModuleEnemies::PreUpdate(){
	// Remove all enemies scheduled for deletion
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->pendingToDelete)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleEnemies::Update()
{
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
			enemies[i]->Update();
	}

	HandleEnemiesDespawn();

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	App->textures->Unload(textureEnemies);
	App->textures->Unload(finalBoss1);
	App->textures->Unload(finalBoss2);
	App->audio->UnloadFx(enemyDestroyedFx);

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPE type, int x, int y, int pattern)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(spawnQueue[i].type == ENEMY_TYPE::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			spawnQueue[i].pattern = pattern;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != ENEMY_TYPE::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = ENEMY_TYPE::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void ModuleEnemies::HandleEnemiesDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			// Delete the enemy when it has reached the end of the screen
			if ((enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN-261)
				||(enemies[i]->position.x * SCREEN_SIZE > (App->render->camera.x+SCREEN_WIDTH+ SPAWN_MARGIN)))
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);

				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}
}

void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
				case ENEMY_TYPE::GREENSHIP:
					enemies[i] = new Enemy_GreenShip(info.x, info.y, info.pattern);
					break;
				case ENEMY_TYPE::BROWNSHIP:
					enemies[i] = new Enemy_BrownShip(info.x, info.y, info.pattern);
					break;
				case ENEMY_TYPE::REDSHIP:
					enemies[i] = new Enemy_RedShip(info.x, info.y, info.pattern);
					break;
				case ENEMY_TYPE::YELLOWSHIP:
					enemies[i] = new Enemy_YellowShip(info.x, info.y, info.pattern);
					break;
				case ENEMY_TYPE::BLUESHIP:
					enemies[i] = new Enemy_BlueShip(info.x, info.y, info.pattern);
					break;
				case ENEMY_TYPE::MINIBOOS1:
					enemies[i] = new Enemy_MiniBoss1(info.x, info.y, info.pattern);
					break;
				case ENEMY_TYPE::BOSS1:
					enemies[i] = new Enemy_FinalBoss1(info.x, info.y, info.pattern);
					break;
				case ENEMY_TYPE::GREEN:
					enemies[i] = new Enemy_Green2(info.x, info.y, info.pattern);
					break;
				case ENEMY_TYPE::WHITE:
					enemies[i] = new Enemy_White(info.x, info.y, info.pattern);
					break;
				case ENEMY_TYPE::BOSS2:
					enemies[i] = new Enemy_FinalBoss2(info.x, info.y, info.pattern);
					break;
			}
			if (info.type == ENEMY_TYPE::BOSS1) enemies[i]->texture = finalBoss1;
			if (info.type == ENEMY_TYPE::BOSS2) enemies[i]->texture = finalBoss2;
			else enemies[i]->texture = textureEnemies;
			enemies[i]->destroyedFx = enemyDestroyedFx;
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->OnCollision(c2); //Notify the enemy of a collision
			App->audio->PlayFx(enemyDestroyedFx);
			
			//switch type enemi for diferent score and money
			//Need creat a variable type in enemymodules
			
			delete enemies[i];
			enemies[i] = nullptr;
			break;


		}
	}
}

void ModuleEnemies::spawningEnemies(int numEnemies, ENEMY_TYPE type, int x, int y, int enemiesDistance,int pattern) {
	//It is responsible for making "number of enemies" appear, according to their type, 
	//in the xand y coordinates with an "enemy distance" between enemy and enemy
	for (int i = 0; i < numEnemies; i++)
		AddEnemy(type, x + (i * enemiesDistance), y,pattern);
}