#include "pch.h"
#include "State.h"
#include "TargetingState.h"
#include "Enemy.h"
#include "StateMachine.h"
void TargetingState::Enter()
{
	State::Enter();
}


void TargetingState::Exit()
{
	State::Exit();
}

void TargetingState::Movement(float _dt)
{

}

void TargetingState::Shooting(float _dt)
{
}
