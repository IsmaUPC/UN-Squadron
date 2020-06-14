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

bool ModuleParticles::Start() {

	LOG("Loading particles");
	App->textures->Enable();
	playerShotTexture = App->textures->Load("Assets/PlayerShoot.png");
	enemyShotTexture = App->textures->Load("Assets/EnemyShoot.png");
	playerExplosionTexture = App->textures->Load("Assets/PlayerDead2.png");
	miniBoss1ShotTx = App->textures->Load("Assets/shot_miniBoss1.png");
	boss1Tx = App->textures->Load("Assets/FinalBoss1.png");
	SpecialWeaponTexture = App->textures->Load("Assets/SW_Texture.png");

	soundExplosion = App->audio->LoadFx("Assets/06_Effect_Explosion_Enemies.wav");

	//Shot Ball boss
	animBallShotBoss1.speed = 0.3f;
	hitBallShotBoss1.PushBack({ 546 ,139,20,25 });
	for (int i = 0; i < 3; i++)
		animBallShotBoss1.PushBack({ 566 + (i * 20),139,20,25 });
	for (int i = 0; i < 4; i++)
		pExplBallBoss1.anim.PushBack({ 546 + (i * 30),171,30,32 });
	pExplBallBoss1.anim.loop = false;
	pExplBallBoss1.anim.speed = 0.3f;
	ballShotBoss1.explodes = true;


	//Openwings
	openWings.PushBack({ 113,32,28,91 });
	openWings.PushBack({ 390,32,28,91 });
	openWings.PushBack({ 390,200,28,91 });
	openWings.PushBack({ 390,368,28,91 });
	openWings.PushBack({ 390,536,28,91 });

	//Moab
	for (int i = 0; i < 3; i++)
		aMoabBoss1.PushBack({ 556 + (45 * i),313,45,20 });

	for (int i = 0; i < 3; i++)
		aMoabDownBoss1.PushBack({ 556 + (45 * i),342,45,38 });
	aMoabBoss1.speed = 0.5f;
	aMoabDownBoss1.speed = 0.5f;
	pMoabBoss1.path.PushBack({ 1.0f,0.50f }, 5, new Animation(aMoabBoss1));
	pMoabBoss1.path.PushBack({ 1.0f,1.0f }, 5, new Animation(aMoabBoss1));
	pMoabBoss1.path.PushBack({ 1.0f,3.0f }, 155, new Animation(aMoabDownBoss1));
	pMoabBoss1.path.loop = false;
	pMoabBoss1.speed.x = SCREEN_SPEED;
	pMoabBoss1.explodes = true;
	pMoabDownBoss1.path.PushBack({ -0.25f,2.0f }, 150, new Animation(aMoabDownBoss1));
	pMoabDownBoss1.speed.y = 2.0f;
	pMoabDownBoss1.speed.x = -1.0f;

	//Boss2 Bombs
	pBoss2ShotBombs.anim.PushBack({ 695 ,315,25,18 });
	for (int i = 0; i < 7; i++)
		pBoss2ExplBombs.anim.PushBack({ 728 + (38 * i),307,38,37 });
	//pBoss2ShotBombs.anim.speed= 0.15f;
	pBoss2ShotBombs.lifetime = 40.0f;
	pBoss2ShotBombs.explodes = true;
	pBoss2ShotBombs.anim.loop = false;
	pBoss2ExplBombs.anim.loop = false;
	pBoss2ExplBombs.explodes = false;

	//Boss2 Misile 
	firstExplMisileB2.PushBack({ 568,36,80,70 });
	for (int i = 1; i < 3; i++) {
		loopExplMisileB2.PushBack({ 568 + (81 * i),36,80,70 });
		endExplMisileB2.PushBack({ 568 + (81 * (i + 2)),36,80,70 });
	}	
	aMisile.PushBack({ 640,144,24,16 });
	aMisile.loop = false;
	loopExplMisileB2.speed = 0.2f;
	loopExplMisileB2.loop = true;
	endExplMisileB2.speed = 0.05f;
	endExplMisileB2.loop = false;

	pBoss2ShotMisile.path.loop = false;
	pBoss2ShotMisile.path.PushBack({ 5.0f,0.0f }, 65, new Animation(aMisile));
	pBoss2ShotMisile.explodes = true;

	pBoss2ExplMisile.path.loop=false;
	pBoss2ExplMisile.path.PushBack({SCREEN_SPEED,0.0f }, 5, new Animation(firstExplMisileB2));
	pBoss2ExplMisile.path.PushBack({SCREEN_SPEED,0.0f }, 25, new Animation(loopExplMisileB2));
	pBoss2ExplMisile.path.PushBack({SCREEN_SPEED,0.0f }, 10, new Animation(endExplMisileB2));
	pBoss2ExplMisile.inmortal = true;




	//Boss1 laser
	for (int i = 0; i < 4; i++)
		bossBallLaser.anim.PushBack({ 10 * i, 0, 10, 10 });
	bossBallLaser.anim.loop = true;
	bossBallLaser.explodes = false;

	//Boss1 Burstshot
	for (int i = 0; i < 2; i++)
		pBurstshotBallBoss1.anim.PushBack({726+(i*30),356,30,24});
	pBurstshotBallBoss1.anim.loop = true;
	pBurstshotBallBoss1.anim.speed = 0.2f;

	//Explosion derivada del burstshot
	aBurstshotBallBoss1.PushBack({ 0,698,40,48 });
	aBurstshotBallBoss1.PushBack({ 40,698,40,48 });
	aBurstshotBallBoss1.PushBack({ 80,698,40,48 });
	aBurstshotBallBoss1.PushBack({ 120,698,40,48 });
	aBurstshotBallBoss1.speed = 0.1f;
	pFlashBurstshotBoss1.anim = aBurstshotBallBoss1;


	// Explosion player
	explosion.anim.PushBack({ 0, 12, 37, 46 });
	explosion.anim.PushBack({ 42, 20, 36, 38 });
	explosion.anim.PushBack({ 85, 1, 45, 57 });
	explosion.anim.PushBack({ 137, 6, 46, 52 });
	explosion.anim.PushBack({ 190, 0, 49, 58 });
	explosion.anim.PushBack({ 246, 12, 49, 46 });
	explosion.anim.PushBack({ 307, 29, 50, 29 });
	explosion.anim.speed = 0.1f;
	explosion.anim.loop = false;
	
	//explosion enemies
	for (int i = 0; i < 7; i++)
		explosionEnemies.anim.PushBack({570+i*60,386,60,60});
	explosionEnemies.anim.loop = false;
	explosionEnemies.explodes = false;
	explosionEnemies.anim.speed = 0.2f;
	
	//player shot
	playerLaser.anim.PushBack({ 0, 0, 40, 7 });
	explosionPalyerLaser.anim.PushBack({675,140,28,26});
	explosionPalyerLaser.anim.PushBack({675,140,28,26});
	explosionPalyerLaser.anim.PushBack({675,140,28,26});
	explosionPalyerLaser.anim.loop = false;
	explosionPalyerLaser.explodes = false;

	//Mini boss shot
	mBoss1ShotClose.PushBack({ 22, 29, 45, 12 });
	mBoss1ShotOpening.PushBack({ 113 , 9, 45, 52 });
	for (int i = 0; i < 2; i++) 
		mBoss1ShotOpen.PushBack({ 90 *(i+2), 8, 90, 54 });
	mBoss1ShotOpen.speed = 0.5f;
	hitMBoss1.PushBack({362,7,88,55});
	hitMBoss1.loop = false;
	mBoss1Shot.lives = 4;
	mBoss1Shot.path.PushBack({ SCREEN_SPEED , 0.0f }, 25, new Animation(mBoss1ShotClose));
	mBoss1Shot.path.PushBack({ SCREEN_SPEED , 0.0f }, 10, new Animation(mBoss1ShotOpening));
	mBoss1Shot.path.PushBack({ -0.9 , 0.0f }, 25, new Animation(mBoss1ShotOpen));
	mBoss1Shot.path.PushBack({ -3.0f  , 0.0f }, 25, new Animation(mBoss1ShotOpen));
	mBoss1Shot.path.PushBack({ -4.0f  , 0.0f }, 150, new Animation(mBoss1ShotOpen));
	mBoss1Shot.explodes = true;

	//enemy laser
	for (int i = 0; i < 4; i++)
		enemyLaser.anim.PushBack({ 10*i, 0, 10, 10 });
	enemyLaser.lifetime = 150;
	enemyLaser.anim.speed = 0.4f;


	//laser.anim.PushBack({ 249, 103, 16, 12 });
	playerLaser.speed.x = 25 + SCREEN_SPEED;
	playerLaser.lifetime = 50;
	playerLaser.anim.speed = 0.2f;
	playerLaser.explodes=true;

	//PowerUp
	for (int i = 0; i < 2; i++) {
		PowerUp.anim.PushBack({ (46 + (31 * (i * 2))), 0, 31,26 });
		PowerUpBlue.anim.PushBack({ (46 + (31 * (1+i))), 0, 31,26 });
	}
	PowerUp.anim.speed = 0.1f;
	PowerUp.explodes = false;

	PowerUpBlue.anim.speed = 0.1f;
	PowerUpBlue.explodes = false;

	//SPECIAL WEAPONS
	int indexWeapon;
	indexWeapon = App->sceneShop->BOMB;
	SpecialWeaponAnim[indexWeapon].PushBack({ 22, 0, 22, 21 });
	SpecialWeaponAnim[indexWeapon].PushBack({ 22, 0, 22, 21 });
	SpecialWeaponAnim[indexWeapon].PushBack({ 0, 0, 22, 21 });
	SpecialWeaponAnim[indexWeapon].PushBack({ 0, 0, 22, 21 });
	SpecialWeaponAnim[indexWeapon].PushBack({ 0, 0, 22, 21 });
	SpecialWeaponAnim[indexWeapon].speed = 0.1f;
	SpecialWeaponAnim[indexWeapon].loop = false;
	SpecialWeapon[indexWeapon].lifetime = 150;

	indexWeapon = App->sceneShop->CEILING;
	SpecialWeaponAnim[indexWeapon].PushBack({ 47, 0, 12, 32 });
	SpecialWeaponAnim[indexWeapon].PushBack({ 62, 0, 12, 32 });
	SpecialWeaponAnim[indexWeapon].speed = 0.2f;
	SpecialWeapon[indexWeapon].lifetime = 150;

	indexWeapon = App->sceneShop->S_SHELL;
	SpecialWeaponAnim[indexWeapon].PushBack({ 40, 38, 117, 22 });
	SpecialWeaponAnim[indexWeapon].PushBack({ 40, 67, 117, 22 });
	SpecialWeaponAnim[indexWeapon].speed = 0.1f;
	SpecialWeaponAnim[indexWeapon].loop = true;
	SpecialWeapon[indexWeapon].lifetime = 50;

	indexWeapon = App->sceneShop->GUNPOD;
	SpecialWeaponAnim[indexWeapon].PushBack({ 138, 0, 15, 16 });
	SpecialWeaponAnim[indexWeapon].speed = 0.1f;
	SpecialWeaponAnim[indexWeapon].loop = true;
	SpecialWeapon[indexWeapon].lifetime = 60;

	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(playerShotTexture);
	App->textures->Unload(enemyShotTexture);
	App->textures->Unload(playerExplosionTexture);
	App->textures->Unload(miniBoss1ShotTx);
	App->textures->Unload(boss1Tx);
	App->textures->Unload(SpecialWeaponTexture);

	App->audio->UnloadFx(soundExplosion);

	// Delete all remaining active particles on application exit 
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr) {
			for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) {
				if (particles[i] != nullptr) {
					delete particles[i];
					particles[i] = nullptr;
				}
			}
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

		p->SetStateParticle(status_Particle::STATE_PARTICLE_HIT);
		if (p != nullptr && p->collider == c1){
			//PowerUp
			if (c1->type == Collider::PLAYER && c2->type == Collider::POWERUP || c2->type == Collider::PLAYER && c1->type == Collider::POWERUP) { App->player->caughtPowerup(1); };
			if (c1->type == Collider::PLAYER && c2->type == Collider::POWERUP_B || c2->type == Collider::PLAYER && c1->type == Collider::POWERUP_B) { App->player->caughtPowerup(3); };

			if (App->player->getStatusPlayer() != status_player::STATE_HIT && p->GetStateParticle()==status_Particle::STATE_PARTICLE_HIT)
			{
				if(p->collider->type==Collider::Type::M_BOSS1_SHOT)p->path.SetCurrentAnimation(new Animation (hitMBoss1));
				else if(p->collider->type==Collider::Type::BOSS1_SHOT_BALL)p->path.SetCurrentAnimation(new Animation (hitBallShotBoss1));
				p->lives--;
			}
			if (p->lives <= 0 && !p->inmortal)p->SetToDelete();
			break;
		}
	}
}

update_status ModuleParticles::PreUpdate()
{
	// Remove all particles scheduled for deletion
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)	{
		
		if (particles[i] != nullptr && particles[i]->pendingToDelete){
			if (particles[i]->explodes){
				//particle explosion 
				SDL_Rect pCollider = particles[i]->collider->rect;
				if (particles[i]->collider->type== Collider::Type::BOSS1_SHOT_BALL) {
					AddParticle(pExplBallBoss1, pCollider.x, pCollider.y,Collider::Type::BOSS_EXPLOSION_BALL);
				}
				else if (particles[i]->collider->type == Collider::Type::PLAYER_SHOT)
				{
					AddParticle(explosionPalyerLaser, pCollider.x+ (pCollider.w/2), pCollider.y+ (pCollider.h/2), Collider::Type::NONE);
				}
				else if (particles[i]->collider->type == Collider::Type::BOSS2_MISILE)
				{
					AddParticle(pBoss2ExplMisile, pCollider.x- 40, pCollider.y- 35, Collider::Type::BOSS2_MISILE_EXPLOSION);
				}
				else if (particles[i]->collider->type == Collider::Type::BOSS2_BOMBS)
				{
					AddParticle(pBoss2ExplBombs, pCollider.x+ (pCollider.w/2), pCollider.y+ (pCollider.h/2), Collider::Type::NONE);
				}
				else {
				App->audio->PlayFx(*(new int(soundExplosion)));
					AddParticle(explosionEnemies, pCollider.x, pCollider.y);
				}
			}
			if (particles[i]->collider->type == Collider::Type::BOSS_EXPLOSION_BALL) laserBallExplosion( i);
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleParticles::laserBallExplosion( const uint& i)
{
	float spdL = 4;
	float rad = 45 * PI / 180;
	bossBallLaser.explodes = false;
	bossBallLaser.speed = { spdL + SCREEN_SPEED, 0.0f };
	AddParticle(bossBallLaser, particles[i]->position.x, particles[i]->position.y, Collider::Type::BOSS_SHOT_LASER);

	bossBallLaser.speed = { (float)cos(rad) * spdL + SCREEN_SPEED , -((float)sin(rad) * spdL) };
	AddParticle(bossBallLaser, particles[i]->position.x, particles[i]->position.y, Collider::Type::BOSS_SHOT_LASER);

	bossBallLaser.speed = { 0.0f + SCREEN_SPEED,spdL };
	AddParticle(bossBallLaser, particles[i]->position.x, particles[i]->position.y, Collider::Type::BOSS_SHOT_LASER);

	bossBallLaser.speed = { 0.0f + SCREEN_SPEED,-spdL };
	AddParticle(bossBallLaser, particles[i]->position.x, particles[i]->position.y, Collider::Type::BOSS_SHOT_LASER);

	bossBallLaser.speed = { (float)cos(rad) * spdL + SCREEN_SPEED , (float)sin(rad) * spdL };
	AddParticle(bossBallLaser, particles[i]->position.x, particles[i]->position.y, Collider::Type::BOSS_SHOT_LASER);

	bossBallLaser.speed = { -((float)cos(rad) * spdL - SCREEN_SPEED) , (float)sin(rad) * spdL };
	AddParticle(bossBallLaser, particles[i]->position.x, particles[i]->position.y, Collider::Type::BOSS_SHOT_LASER);

	bossBallLaser.speed = { -((float)cos(rad) * spdL - SCREEN_SPEED), -((float)sin(rad) * spdL) };
	AddParticle(bossBallLaser, particles[i]->position.x, particles[i]->position.y, Collider::Type::BOSS_SHOT_LASER);

	bossBallLaser.speed = { -(spdL - SCREEN_SPEED), 0.0f };
	AddParticle(bossBallLaser, particles[i]->position.x, particles[i]->position.y, Collider::Type::BOSS_SHOT_LASER);
}

update_status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;
		
		if (particle->GetStateParticle() == status_Particle::STATE_PARTICLE_CHANGE_ANIMATION){
			if( particle->collider->type == Collider::Type::M_BOSS1_SHOT)particles[i]->path.SetCurrentAnimation(new Animation(mBoss1ShotOpen));
			if( particle->collider->type == Collider::Type::BOSS1_SHOT_BALL)particles[i]->path.SetCurrentAnimation(new Animation(animBallShotBoss1));
			particles[i]->SetStateParticle(status_Particle::STATE_PARTICLE_IDLE);
		}
		if (particle->collider->type == Collider::Type::POWERUP || particle->collider->type == Collider::Type::POWERUP_B) {
			angle[i] += angleIncrement;
			particle->position.y += (Radio * sinf(angle[i]));
			particle->position.x += SCREEN_SPEED + speed_X_PowerUP;
		};
		if (particle->GetStateParticle() == status_Particle::STATE_PARTICLE_IDLE && particle->collider->type == Collider::Type::SW_BOMB) {
			particles[i]->path.SetCurrentAnimation(new Animation(SpecialWeaponAnim[App->sceneShop->BOMB]));
		}
		if (particle->GetStateParticle() == status_Particle::STATE_PARTICLE_IDLE && particle->collider->type == Collider::Type::SW_CEILING) {
			particles[i]->path.SetCurrentAnimation(new Animation(SpecialWeaponAnim[App->sceneShop->CEILING]));
		}
		if (particle->GetStateParticle() == status_Particle::STATE_PARTICLE_IDLE && particle->collider->type == Collider::Type::SW_S_SHELL) {
			particles[i]->path.SetCurrentAnimation(new Animation(SpecialWeaponAnim[App->sceneShop->S_SHELL]));
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
			colliderI = particle->collider;
			if (colliderI->type == Collider::Type::BOSS1_SHOT_BALL || colliderI->type == Collider::Type::BOSS_MOAB || colliderI->type == Collider::Type::BOSS2_MISILE || colliderI->type == Collider::Type::BOSS2_MISILE_EXPLOSION) {
				pathRefresh(particle);
				App->render->Blit(boss1Tx, particle->position.x, particle->position.y, &(particle->path.GetCurrentAnimation()->GetCurrentFrame()));
				 if (particle->path.isFinish)particle->SetToDelete();
			}
			//Shot mini boss
			else if (colliderI->type == Collider::Type::M_BOSS1_SHOT ) {
				pathRefresh(particle);
				App->render->Blit(miniBoss1ShotTx, particle->position.x, particle->position.y, &(particle->path.GetCurrentAnimation()->GetCurrentFrame()));		
			}
			//SWs
			else if (colliderI->type == Collider::Type::SW_BOMB || colliderI->type == Collider::Type::SW_CEILING || colliderI->type == Collider::Type::SW_S_SHELL || colliderI->type == Collider::Type::SW_GUNPOD) {
				pathRefresh(particle);
				App->render->Blit(SpecialWeaponTexture, particle->position.x, particle->position.y, &(particle->path.GetCurrentAnimation()->GetCurrentFrame()));
			}
			//shot enemy 
			else if (colliderI->type == Collider::Type::ENEMY_SHOT) {
				App->render->Blit(enemyShotTexture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));		
			}
			//player shot
			else if (colliderI->type == Collider::Type::POWERUP_B ||colliderI->type == Collider::Type::POWERUP || colliderI->type == Collider::Type::PLAYER_SHOT || colliderI->type == Collider::Type::BOSS_SHOT_LASER) {
				App->render->Blit(playerShotTexture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
			}
			else if (colliderI->type == Collider::Type::BOSS_EXPLOSION_BALL || colliderI->type == Collider::Type::BOSS_BURSTSHOT|| colliderI->type == Collider::Type::BOSS2_BOMBS) {
				App->render->Blit(boss1Tx, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame())); 
			}
			else if (colliderI->type == Collider::Type::NONE && colliderI->type!=Collider::Type::BOSS_EXPLOSION_BALL) {
				if (App->player->destroyed == true) {	
						App->render->Blit(playerExplosionTexture, (particle->position.x - (particle->anim.GetCurrentFrame().w - PLAYER_WIDTH)),
						particle->position.y - (particle->anim.GetCurrentFrame().h / 2), &(particle->anim.GetCurrentFrame()));
				}
				//explosion enemiesif (particle->path.getTotalSteps()==NULL) {}
				
				else if (App->player->getStatusPlayer() != status_player::STATE_DEAD) {
						App->render->Blit(boss1Tx, (particle->position.x + -(particle->anim.GetCurrentFrame().w / 2)),
						particle->position.y - (particle->anim.GetCurrentFrame().h / 2), &(particle->anim.GetCurrentFrame()));
				}
			}
		}
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleParticles::pathRefresh(Particle* particle)
{
	resizeParticle(particle);
	particle->collider->SetPos(particle->spawnPos + particle->path.GetRelativePosition());
	particle->position = particle->spawnPos + particle->path.GetRelativePosition();
	particle->path.Update();
}




void ModuleParticles::ChekParticlesDespawn(Particle* _particle) {
	iPoint posCamera = { App->render->camera.x, App->render->camera.y };
	fPoint posParticle = { _particle->position.x ,_particle->position.y };

	if (_particle != nullptr) {
	// Always destroy particles that collide
		if ((posParticle.y * SCREEN_SIZE < posCamera.y - SPAWN_MARGIN) || (posParticle.y * SCREEN_SIZE > (posCamera.y + SCREEN_HEIGHT + SPAWN_MARGIN)) 
			|| (posParticle.x * SCREEN_SIZE < posCamera.x - SPAWN_MARGIN)|| (posParticle.x * SCREEN_SIZE > (posCamera.x + SCREEN_WIDTH + SPAWN_MARGIN))) {

			LOG("DeSpawning enemy at %d", _particle->position.x * SCREEN_SIZE);
			_particle->explodes = false;
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


	speedShots = 7;

	Particle* p = new Particle(particle);

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i){
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr){
			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;

			//Adding the particle's collider 
			p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);
			
			if (p->collider !=nullptr) {
				if (p->collider->type == Collider::Type::BOSS_BURSTSHOT) { p->speed.x = -3; };

				if (p->collider->type == Collider::Type::POWERUP || p->collider->type == Collider::Type::POWERUP_B) { p->speed.x = -1; };

				//if(p->collider->type== Collider::Type::NONE)App->audio->PlayFx(*(new int(soundExplosion)));
					//Set direction to shotEnemy
					if (p->collider->type == p->collider->ENEMY_SHOT) p = setShotDirection(p, x, y);
					if (p->collider->type == p->collider->M_BOSS1_SHOT) p->spawnPos.create(x, y);
					if (p->collider->type == p->collider->BOSS1_SHOT_BALL)	createBallBoss(p, x, y);
					if (p->collider->type == p->collider->BOSS_MOAB) p->spawnPos.create(x,y);
					if (p->collider->type == p->collider->BOSS2_MISILE) p->spawnPos.create(x,y);
					if (p->collider->type == p->collider->BOSS2_MISILE_EXPLOSION) p->spawnPos.create(x,y);

			}
			particles[i] = p;
			break;
		}
	}
	return p;
}

void ModuleParticles::createBallBoss(Particle* p, int x, int y)
{
	distanceBall = (firstSecond) ? 40 : 0;
	firstSecond = !firstSecond;

	p->spawnPos.create(x, y);
	p->lives = 4;
	p->path.loop = false;
	p->path.PushBack({ -0.5f,-1.0f }, 50, new Animation(animBallShotBoss1));
	p->path.PushBack({ -0.5f,-0.5f }, 10, new Animation(animBallShotBoss1));
	p->path.PushBack({ -0.5f,-0.0f }, 5, new Animation(animBallShotBoss1));
	p->path.PushBack({ -0.5f,+0.5f }, 10, new Animation(animBallShotBoss1));
	p->path.PushBack({ -0.5f,+1.0f }, distanceBall, new Animation(animBallShotBoss1));
	p->path.PushBack({ SCREEN_SPEED,0.0f }, 0, new Animation(animBallShotBoss1));
}
void ModuleParticles::createMisile(Particle* p, int x, int y)
{
	

	p->spawnPos.create(x, y);
	p->lives = 1;
	p->path.loop = false;
	p->path.PushBack({ -0.5f,-1.0f }, 50, new Animation(animBallShotBoss1));
	p->path.PushBack({ -0.5f,-0.5f }, 10, new Animation(animBallShotBoss1));
	p->path.PushBack({ -0.5f,-0.0f }, 5, new Animation(animBallShotBoss1));
	p->path.PushBack({ -0.5f,+0.5f }, 10, new Animation(animBallShotBoss1));
	p->path.PushBack({ -0.5f,+1.0f }, distanceBall, new Animation(animBallShotBoss1));
	p->path.PushBack({ SCREEN_SPEED,0.0f }, 0, new Animation(animBallShotBoss1));
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
				p->spawnPos.create(x, y);
				p->lives = 10;
				p->path.PushBack({ SCREEN_SPEED + 5, 0 }, 150, new Animation(SpecialWeaponAnim[_indexWeapon]));

				break;
			case App->sceneShop->T_LASER:

				break;
			case App->sceneShop->BOMB:
				p->spawnPos.create(x, y);
				p->lives = 1;
				p->explodes = true;
				p->path.PushBack({ SCREEN_SPEED + 0.5f , 1.f }, 25, new Animation(SpecialWeaponAnim[_indexWeapon]));
				p->path.PushBack({ SCREEN_SPEED + 0.5f , 1.5f }, 25, new Animation(SpecialWeaponAnim[_indexWeapon]));
				p->path.PushBack({ SCREEN_SPEED + 0.5f , 2.f }, 25, new Animation(SpecialWeaponAnim[_indexWeapon]));
				p->path.PushBack({ SCREEN_SPEED + 0.5f , 2.5f }, 150, new Animation(SpecialWeaponAnim[_indexWeapon]));

				break;
			case App->sceneShop->NAPALM:

				break;
			case App->sceneShop->GUNPOD:
				p->spawnPos.create(x, y);
				p->lives = 1;

				p->path.PushBack({ SCREEN_SPEED + 11.5f ,-11.5f }, 60, new Animation(SpecialWeaponAnim[_indexWeapon]));
				break;
			case App->sceneShop->CEILING:
				p->spawnPos.create(x, y);
				p->lives = 1;

				p->path.PushBack({ 0.5f , -4.f }, 25, new Animation(SpecialWeaponAnim[_indexWeapon]));

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

	p->explodes = false;
	xPlayer = App->player->position.x - x - 10;
	yPlayer = App->player->position.y - y + 5;
	escalar = (xPlayer * x) + (yPlayer * y);

	magnitudPlayer = sqrt(pow(xPlayer, 2) + pow(yPlayer, 2));
	magnitudEnemy = sqrt(pow(x, 2) + pow(y, 2));

	angulo = (acos(escalar / (magnitudPlayer * magnitudEnemy)));

	p->speed.x = (App->player->position.x > x) ? (speedShots * cos(angulo)) + SCREEN_SPEED : (speedShots * cos(-angulo));
	p->speed.y = (App->player->position.y > y) ? (speedShots * sin(angulo)) : (speedShots * sin(-angulo));

	return p;
}