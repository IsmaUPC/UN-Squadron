#include "ModuleParticles.h"

#include "Application.h"

#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) {
		if(particles[i] != nullptr)
		particles[i]->collider->pendingToDelete;
		
	}
}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	App->textures->Enable();
	playerShotTexture = App->textures->Load("Assets/PlayerShoot.png");
	enemyShotTexture= App->textures->Load("Assets/EnemyShoot.png");
	playerExplosionTexture = App->textures->Load("Assets/PlayerDead.png");


		// Explosion particle
	explosion.anim.PushBack({ 0, 12, 37, 46 });
	explosion.anim.PushBack({ 42, 20, 36, 38 });
	explosion.anim.PushBack({ 85, 1, 45, 57 });
	explosion.anim.PushBack({ 137, 6, 46, 52 });
	explosion.anim.PushBack({ 190, 0, 49, 58 });
	explosion.anim.PushBack({ 246, 12, 49, 46 });
	explosion.anim.PushBack({ 307, 29, 50, 29 });
	explosion.anim.loop = false;
	//explosion.speed.x += SCREEN_SPEED;

	explosion.anim.speed = 0.1f;
	
	playerLaser.anim.PushBack({ 0, 0, 40, 7 });


	for (int i = 0; i < 4; i++)
	enemyLaser.anim.PushBack({ 10*i, 0, 10, 10 });
	enemyLaser.speed.x +=  SCREEN_SPEED;
	enemyLaser.lifetime = 150;
	enemyLaser.anim.speed = 0.4f;
	

	//laser.anim.PushBack({ 249, 103, 16, 12 });
	playerLaser.speed.x = 25 + SCREEN_SPEED;
	playerLaser.lifetime = 50;
	playerLaser.anim.speed = 0.2f;

	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			delete particles[i];
			particles[i] = nullptr;
			if (c1->type == Collider::PLAYER_SHOT && c2->type == Collider::ENEMY || c2->type == Collider::PLAYER_SHOT && c1->type == Collider::ENEMY) {
				App->player->score += 20;
				

			}
			break;
		}
	}
}

update_status ModuleParticles::PreUpdate()
{
	// Remove all particles scheduled for deletion
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr && particles[i]->pendingToDelete)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;
		

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			delete particle;
			particles[i] = nullptr;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];
		//Collider* colliderI= particle->collider;
		//
		if (particle != nullptr && particle->collider != nullptr && particle->isAlive)
		{
			if (particle->collider->type == particle->collider->ENEMY_SHOT) {
				App->render->Blit(enemyShotTexture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));		
			}
			else if (particle->collider->type == particle->collider->PLAYER_SHOT) {
				App->render->Blit(playerShotTexture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
			}

		}
		if (App->player->destroyed == true)
		{
			if (particle != nullptr && particle->collider != nullptr && particle->collider->type == particle->collider->PLAYER)
			{
				App->render->Blit(playerExplosionTexture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
			}
		}
		
	}

	return update_status::UPDATE_CONTINUE;
}

Particle* ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{

	velShotEnemy = 4;

	Particle* p = new Particle(particle);

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;

			//Adding the particle's collider
			//if (colliderType != Collider::Type::NONE)
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);
			if (p->collider == nullptr) break;

			if (p->collider->type == p->collider->ENEMY_SHOT) {
				
					xPlayer = App->player->position.x - x -10;
					yPlayer = App->player->position.y - y + 5;
					escalar = (xPlayer * x) + (yPlayer * y);

					magnitudPlayer = sqrt(pow(xPlayer, 2) + pow(yPlayer, 2));
					magnitudEnemy = sqrt(pow(x, 2) + pow(y, 2));

					angulo = (acos(escalar / (magnitudPlayer * magnitudEnemy)));

				p->speed.x = (App->player->position.x > x) ? (velShotEnemy  * cos(angulo))+ SCREEN_SPEED : (velShotEnemy  * cos(-angulo)) ;
				p->speed.y = (App->player->position.y > y ) ? (velShotEnemy * sin(angulo)) :   (velShotEnemy * sin(-angulo) );
				
			}
			particles[i] = p;
			break;
		}
	}
	return p;
}