#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"



Enemy::Enemy(int x, int y) : position(x, y)
{
	spawnPos = position;
	timerShot = new Timer(200);
}
Enemy::Enemy(int x, int y, int _pattern) : position(x, y) , pattern(_pattern)
{
	spawnPos = position;
	timerShot = new Timer(200);

}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
	CleanUp();
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Update()
{
	resizeCollider();
	timerShot->update();
	if(collider->type== Collider::Type::ENEMY && timerShot->check())shotType(TypeShot::ENEMY_SHOT);
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	if(collider->type== Collider::ENEMY_SHOT)shotType();

}

void Enemy::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
}

void Enemy::OnCollision(Collider* _collider)
{

	if (App->player->getStatusPlayer() != status_player::STATE_HIT)lives--, stateEnemy = status_Enemies::STATE_ENEMY_HIT;;
}

void Enemy::shotEnemy(Particle particle, Collider::Type type) {
	App->particles->AddParticle(particle , position.x, position.y +10, type);

}

void Enemy::shotType(TypeShot typeShot) {

	switch (typeShot){
	case TypeShot::ENEMY_SHOT:

	if (rand() % 90 < 45 && !isShotDone) {
		shotEnemy(App->particles->enemyLaser, Collider::Type::ENEMY_SHOT);
		isShotDone = true;
	}
		break;
	case TypeShot::MINI_BOSS1:

			shotEnemy(App->particles->mBoss1Shot, Collider::Type::M_BOSS1_SHOT);

		break;
	default:
		break;
	}


}
void Enemy::CleanUp() {

}

void Enemy::SetToDelete(){
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

void Enemy::resizeCollider() {
	collider->rect.w = (*currentAnim).GetCurrentFrame().w;
	collider->rect.h = (*currentAnim).GetCurrentFrame().h;
}
