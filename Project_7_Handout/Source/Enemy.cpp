#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"



Enemy::Enemy(int x, int y) : position(x, y)
{
	spawnPos = position;
}
Enemy::Enemy(int x, int y, int _pattern) : position(x, y) , pattern(_pattern)
{
	spawnPos = position;
}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	shotPattern();

}

void Enemy::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
}

void Enemy::OnCollision(Collider* collider)
{
	//App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	App->audio->PlayFx(destroyedFx);
}

void Enemy::shotEnemy() {
	App->particles->AddParticle(App->particles->enemyLaser, position.x, position.y , Collider::Type::ENEMY_SHOT);

}

void Enemy::shotPattern() {

	if (rand() % 5000 < 45 && !isShotDone) {
		shotEnemy();
		isShotDone = true;
	}
}
void Enemy::CleanUp() {

}

void Enemy::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}