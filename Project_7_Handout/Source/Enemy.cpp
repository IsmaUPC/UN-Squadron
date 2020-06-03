#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
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
	CleanUp();
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

void Enemy::shotEnemy(Particle particle) {
	App->particles->AddParticle(particle , position.x, position.y , Collider::Type::ENEMY_SHOT);

}

void Enemy::shotPattern() {


	if (rand() % 9000 < 45 && !isShotDone) {
		shotEnemy(App->particles->enemyLaser);
		isShotDone = true;
	}
}
void Enemy::shotPattern(TYPE_PATTERN_SHOT typeShot) {

	switch (typeShot){
	case TYPE_PATTERN_SHOT::NORMAL:

	if (rand() % 9000 < 45 && !isShotDone) {
		shotEnemy(App->particles->enemyLaser);
		isShotDone = true;
	}
		break;
	case TYPE_PATTERN_SHOT::MINI_BOSS1:



		break;
	default:
		break;
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

void Enemy::resizeCollider() {

	collider->rect.w = (*currentAnim).GetCurrentFrame().w;
	collider->rect.h = (*currentAnim).GetCurrentFrame().h;
}
//void Enemy::setCurrentEnemyAnmi(Animation* _currentAnim) {
//
//	currentAnim = _currentAnim;
//	collider->rect.w = (*currentAnim).GetCurrentFrame().w;
//	collider->rect.h = (*currentAnim).GetCurrentFrame().h;
//}