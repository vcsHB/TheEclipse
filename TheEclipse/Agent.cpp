#include "pch.h"
#include "Agent.h"

Agent::~Agent()
{
	Object::~Object();
	delete status;
}

void Agent::Movement()
{
}

void Agent::Shooting()
{
}
