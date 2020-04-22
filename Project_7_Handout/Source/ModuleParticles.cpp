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
	/*
	// Explosion particle
	explosion.anim.PushBack({274, 296, 33, 30});
	explosion.anim.PushBack({313, 296, 33, 30});
	explosion.anim.PushBack({346, 296, 33, 30});
	explosion.anim.PushBack({382, 296, 33, 30});
	explosion.anim.PushBack({419, 296, 33, 30});
	explosion.anim.PushBack({457, 296, 33, 30});
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;
	*/
	playerLaser.anim.PushBack({ 0, 0, 40, 7 });


	for (int i = 0; i < 4; i++)
	enemyLaser.anim.PushBack({ 10*i, 0, 10, 10 });
	enemyLaser.speed.x = - SCREEN_SPEED;
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
			break;
		}
	}
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

		if (particle != nullptr && particle->collider != nullptr && particle->isAlive)
		{
			if (particle->collider->type == particle->collider->ENEMY_SHOT) {
				App->render->Blit(enemyShotTexture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));		
			}
			else if (particle->collider->type == particle->collider->PLAYER_SHOT) {
				App->render->Blit(playerShotTexture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
			}
		}
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	velShotEnemy = 2;
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);
			if (p->collider == nullptr) break;
		

			if (p->collider->type == p->collider->ENEMY_SHOT) {
				

				xPlayer = App->player->position.x - x;
				yPlayer = App->player->position.y - y;
				escalar = (xPlayer * x) + (yPlayer * y);

				magnitudPlayer = sqrt(pow(xPlayer, 2) + pow(yPlayer, 2));
				magnitudEnemy = sqrt(pow(x, 2) + pow(y, 2));

				angulo = acos(escalar / (magnitudPlayer * magnitudEnemy));

				p->speed.x = (xPlayer > 0) ? (velShotEnemy * cos(angulo) + SCREEN_SPEED) : (velShotEnemy * cos(angulo) - SCREEN_SPEED);
				p->speed.y = (yPlayer > 0 ) ? (velShotEnemy * sin(angulo)) + (0.5f+SCREEN_SPEED*sin(angulo)) : -(velShotEnemy * sin(angulo)) - ((velShotEnemy * sin(angulo ))*SCREEN_SPEED);
					//p->speed.x = (velShotEnemy * cos(angulo) - SCREEN_SPEED);
					//p->speed.y = (velShotEnemy * sin(angulo));
			}
			particles[i] = p;
			break;
		}
	}
}