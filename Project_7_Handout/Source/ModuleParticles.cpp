#include "ModuleParticles.h"

#include "Application.h"

#include "ModulePlayer.h"
#include "SceneShop.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles(){

}

bool ModuleParticles::Start(){

	LOG("Loading particles");
	App->textures->Enable();
	playerShotTexture = App->textures->Load("Assets/PlayerShoot.png");
	enemyShotTexture= App->textures->Load("Assets/EnemyShoot.png");
	playerExplosionTexture = App->textures->Load("Assets/PlayerDead.png");
	miniBoss1ShotTx = App->textures->Load("Assets/shot_miniBoss1.png");
	

		// Explosion particle
	explosion.anim.PushBack({ 0, 12, 37, 46 });
	explosion.anim.PushBack({ 42, 20, 36, 38 });
	explosion.anim.PushBack({ 85, 1, 45, 57 });
	explosion.anim.PushBack({ 137, 6, 46, 52 });
	explosion.anim.PushBack({ 190, 0, 49, 58 });
	explosion.anim.PushBack({ 246, 12, 49, 46 });
	explosion.anim.PushBack({ 307, 29, 50, 29 });
	explosion.anim.speed = 0.1f;
	explosion.anim.loop = false;
	
	for (int i = 0; i < 7; i++)
	{
		explosionEnemies.anim.PushBack({571+i*60,386,60,60});
		explosionEnemies.anim.loop = false;
		explosionEnemies.anim.speed = 0.2f;
	}
	
	
	playerLaser.anim.PushBack({ 0, 0, 40, 7 });
	
	
	//Mini boss shot
		mBoss1ShotClose.PushBack({ 22, 29, 45, 12 });
		mBoss1ShotOpening.PushBack({ 113 , 9, 45, 52 });
	for (int i = 0; i < 2; i++) {
		mBoss1ShotOpen.PushBack({ 90 *(i+2), 8, 90, 54 });
	}
	mBoss1ShotOpen.speed = 0.5f;

	hit.PushBack({362,7,88,55});
	hit.loop = false;

	for (int i = 0; i < 4; i++)
	enemyLaser.anim.PushBack({ 10*i, 0, 10, 10 });
	enemyLaser.lifetime = 150;
	enemyLaser.anim.speed = 0.4f;


	//laser.anim.PushBack({ 249, 103, 16, 12 });
	playerLaser.speed.x = 25 + SCREEN_SPEED;
	playerLaser.lifetime = 50;
	playerLaser.anim.speed = 0.2f;

	//SPECIAL WEAPONS
	int indexWeapon;
	indexWeapon = App->sceneShop->BOMB;
	SpecialWeapon[indexWeapon].anim.PushBack({ 0, 0, 10, 7 });
	SpecialWeaponAnim[indexWeapon].PushBack({ 0, 0, 10, 7 });
	SpecialWeapon[indexWeapon].lifetime = 150;


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
		Particle* p = particles[i];
		// Always destroy particles that collide
		if (p == nullptr) continue;

		p->SetStateParticle();
		if (p != nullptr && p->collider == c1){
			if (App->player->getStatusPlayer() != status_player::STATE_HIT && p->GetStateParticle()==status_Particle::STATE_PARTICLE_HIT)
			{
				if(p->collider->type==Collider::Type::M_BOSS1_SHOT)p->path.SetCurrentAnimation(new Animation (hit));
				p->lives--;
			}
			if (p->lives <= 0)
			{
				p->SetToDelete();
				if (p->collider->type != Collider::Type::PLAYER_SHOT)
				{
					SDL_Rect pCollider = p->collider->rect;
					AddParticle(explosionEnemies, pCollider.x, pCollider.y);
				}
				//App->audio->PlayFx(Enemy::destroyedFx);
			}
			
			if (c1->type == Collider::PLAYER_SHOT && c2->type == Collider::ENEMY || c2->type == Collider::PLAYER_SHOT && c1->type == Collider::ENEMY) {
				App->player->score += 100;
				App->player->money += 300;

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
		
		if (particle->GetStateParticle() == status_Particle::STATE_PARTICLE_IDLE && particle->collider->type==Collider::Type::M_BOSS1_SHOT){
			particles[i]->path.SetCurrentAnimation(new Animation(mBoss1ShotOpen));
		}

		if (particle->GetStateParticle() == status_Particle::STATE_PARTICLE_IDLE && particle->collider->type == Collider::Type::SW_BOMB){
			particles[i]->path.SetCurrentAnimation(new Animation(SpecialWeaponAnim[App->sceneShop->BOMB]));
		}

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)	particle->SetToDelete();
				

		ChekParticlesDespawn(particle);
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
			if (particle->collider->type == particle->collider->M_BOSS1_SHOT) {
				resizeParticle(particle);
				particle->collider->SetPos(particle->spawnPos + particle->path.GetRelativePosition());
				particle->position = particle->spawnPos + particle->path.GetRelativePosition();
				particle->path.Update();
				App->render->Blit(miniBoss1ShotTx, particle->position.x, particle->position.y, &(particle->path.GetCurrentAnimation()->GetCurrentFrame()));		
			}
			//SWs
			if (particle->collider->type == particle->collider->SW_BOMB) {
				resizeParticle(particle);
				particle->collider->SetPos(particle->spawnPos + particle->path.GetRelativePosition());
				particle->position = particle->spawnPos + particle->path.GetRelativePosition();
				particle->path.Update();
				App->render->Blit(playerShotTexture, particle->position.x, particle->position.y, &(particle->path.GetCurrentAnimation()->GetCurrentFrame()));
			}
			if (particle->collider->type == particle->collider->ENEMY_SHOT) {
				App->render->Blit(enemyShotTexture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));		
			}
			else if (particle->collider->type == particle->collider->PLAYER_SHOT) {
				App->render->Blit(playerShotTexture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
			}
			else if (particle->collider->type == particle->collider->NONE) {
				if (App->player->destroyed == true) {
					App->render->Blit(playerExplosionTexture, (particle->position.x - (particle->anim.GetCurrentFrame().w - PLAYER_WIDTH)),
						particle->position.y - (particle->anim.GetCurrentFrame().h / 2), &(particle->anim.GetCurrentFrame()));
				}
				else if(App->player->getStatusPlayer()!=status_player::STATE_DEAD)
				App->render->Blit(App->enemies->GetTextureEnemies(), (particle->position.x + -(particle->anim.GetCurrentFrame().w/2 )),
					particle->position.y - (particle->anim.GetCurrentFrame().h / 2), &(particle->anim.GetCurrentFrame()));
			}
		
			//if (App->player->destroyed == true){
			//	if (particle != nullptr && particle->collider != nullptr && particle->collider->type == particle->collider->PLAYER)	{
			//		App->render->Blit(playerExplosionTexture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
			//	}
			//}
		}

		
	}

	return update_status::UPDATE_CONTINUE;
}




void ModuleParticles::ChekParticlesDespawn(Particle* _particle) {
	iPoint posCamera = { App->render->camera.x, App->render->camera.y };
	fPoint posParticle = { _particle->position.x ,_particle->position.y };

	if (_particle != nullptr) {
	// Always destroy particles that collide
		if ((posParticle.y * SCREEN_SIZE < posCamera.y - SPAWN_MARGIN) || (posParticle.y * SCREEN_SIZE > (posCamera.y + SCREEN_HEIGHT + SPAWN_MARGIN)) 
			|| (posParticle.x * SCREEN_SIZE < posCamera.x - SPAWN_MARGIN)|| (posParticle.x * SCREEN_SIZE > (posCamera.x + SCREEN_WIDTH + SPAWN_MARGIN))) {

			LOG("DeSpawning enemy at %d", _particle->position.x * SCREEN_SIZE);
			
			_particle->SetToDelete();
			//delete _particle;
			//_particle = nullptr;
		}
	
	}
}


void ModuleParticles::resizeParticle(Particle* particle)
{
	particle->collider->rect.w = (*particle->path.GetCurrentAnimation()).GetCurrentFrame().w;
	particle->collider->rect.h = (*particle->path.GetCurrentAnimation()).GetCurrentFrame().h;
}

Particle* ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay){

	velShotEnemy = 7;

	Particle* p = new Particle(particle);

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr){
			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;

			//Adding the particle's collider 
			p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

				//Set direction to shotEnemy
				if (p->collider->type == p->collider->ENEMY_SHOT) p= setShotDirection(p, x, y);
				if (p->collider->type == p->collider->M_BOSS1_SHOT) {
					//p->timerHitParticle = new Timer(100);
					p->spawnPos.create(x,y);
					p->lives = 4;

					p->path.PushBack({  SCREEN_SPEED , 0.0f }, 25, new Animation(mBoss1ShotClose));
					p->path.PushBack({ SCREEN_SPEED , 0.0f },20, new Animation(mBoss1ShotOpening));
					p->path.PushBack({ -0.9 , 0.0f },25, new Animation(mBoss1ShotOpen));
					p->path.PushBack({ -3.0f  , 0.0f },25, new Animation(mBoss1ShotOpen));
					p->path.PushBack({ -4.0f  , 0.0f },150, new Animation(mBoss1ShotOpen));
				}
			
			particles[i] = p;
			break;
		}
	}
	return p;
}

Particle* ModuleParticles::AddSWParticle(const Particle& particle, int _indexWeapon, int x, int y, Collider::Type colliderType, uint delay) {

	Particle* p = new Particle(particle);

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) {
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr) {
			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;

			//Adding the particle's collider 
			p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

			switch (_indexWeapon) {
			case App->sceneShop->CLUSTER:

				break;
			case App->sceneShop->PHOENIX:

				break;
			case App->sceneShop->FALCON:

				break;
			case App->sceneShop->BULLPUP:

				break;
			case App->sceneShop->S_SHELL:

				break;
			case App->sceneShop->T_LASER:

				break;
			case App->sceneShop->BOMB:
				p->spawnPos.create(x, y);
				p->lives = 1;

				p->path.PushBack({ SCREEN_SPEED + 0.5f , 1.f }, 25, new Animation(SpecialWeaponAnim[_indexWeapon]));
				p->path.PushBack({ SCREEN_SPEED + 0.5f , 1.5f }, 25, new Animation(SpecialWeaponAnim[_indexWeapon]));
				p->path.PushBack({ SCREEN_SPEED + 0.5f , 2.f }, 25, new Animation(SpecialWeaponAnim[_indexWeapon]));
				p->path.PushBack({ SCREEN_SPEED + 0.5f , 2.5f }, 150, new Animation(SpecialWeaponAnim[_indexWeapon]));

				break;
			case App->sceneShop->NAPALM:

				break;
			case App->sceneShop->GUNPOD:

				break;
			case App->sceneShop->CEILING:

				break;
			case App->sceneShop->MEGACRUSH:

				break;
			}
			particles[i] = p;
			break;
		}
	}
	return p;
}

Particle* ModuleParticles::setShotDirection(Particle* p, int x, int y) {

	xPlayer = App->player->position.x - x - 10;
	yPlayer = App->player->position.y - y + 5;
	escalar = (xPlayer * x) + (yPlayer * y);

	magnitudPlayer = sqrt(pow(xPlayer, 2) + pow(yPlayer, 2));
	magnitudEnemy = sqrt(pow(x, 2) + pow(y, 2));

	angulo = (acos(escalar / (magnitudPlayer * magnitudEnemy)));

	p->speed.x = (App->player->position.x > x) ? (velShotEnemy * cos(angulo)) + SCREEN_SPEED : (velShotEnemy * cos(-angulo));
	p->speed.y = (App->player->position.y > y) ? (velShotEnemy * sin(angulo)) : (velShotEnemy * sin(-angulo));

	return p;
}