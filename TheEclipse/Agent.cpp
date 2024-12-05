#include "pch.h"
#include "Agent.h"
#include "Collider.h"

Agent::~Agent()
{
	Object::~Object();
	delete status;
}

void Agent::Shooting()
{
}

void Agent::Movement()
{
}

void Agent::KnockBack()
{
	Vec2 blockMove = GetPos();
	colliderComponent->GetOffSetPos();

	blockMove -= colliderComponent->GetOffSetPos();
}

void Agent::Blink(bool active)
{
	blinkDuration = 0;
	isBlinking = true;
}
