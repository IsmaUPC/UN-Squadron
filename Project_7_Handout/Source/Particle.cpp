#include "Particle.h"

#include "Collider.h"

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
	timerHitParticle = new Timer(200);
}

Particle::Particle(const Particle& p) : anim(p.anim), position(p.position), speed(p.speed),
frameCount(p.frameCount), lifetime(p.lifetime),timerHitParticle(p.timerHitParticle){
	
}

Particle::~Particle(){
	if (collider != nullptr)
		collider->pendingToDelete = true;
		//this->path.CleanUp();
}

bool Particle::Update()
{
	if (timerHitParticle != nullptr)
	{
		timerHitParticle->update();
		if (timerHitParticle->check())stateParticle = status_Particle::STATE_PARTICLE_IDLE;
	}
	bool ret = true;
	frameCount++;

	// The particle is set to 'alive' when the delay has been reached
	if (!isAlive && frameCount >= 0)
		isAlive = true;

	if (isAlive)
	{

		if(collider->type == Collider::Type::M_BOSS1_SHOT) path.Update();
		if (path.GetCurrentAnimation() != nullptr)path.GetCurrentAnimation()->Update();
		anim.Update();

		// If the particle has a specific lifetime, check when it has to be destroyed
		if (lifetime > 0)
		{
			if (frameCount >= lifetime)
				ret = false;
		}
		// Otherwise the particle is destroyed when the animation is finished
		else if (anim.HasFinished())
			ret = false;

		// Update the position in the screen
		position.x += speed.x;
		position.y += speed.y;

		if (collider != nullptr)
			collider->SetPos(position.x, position.y);
	}

	return ret;
}
void Particle::SetStateParticle()
{
	stateParticle = status_Particle::STATE_PARTICLE_HIT;
}


void Particle::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}