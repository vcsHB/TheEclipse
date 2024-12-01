#pragma once
#include "State.h"
#include "Enemy.h"
class TargetingState :
    public State
{
public:
	virtual void Enter();
	virtual void Update();
	virtual void Exit();
};

