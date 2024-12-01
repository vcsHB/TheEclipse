#include "pch.h"
#include "State.h"
#include "IdleState.h"
#include "Enemy.h"
#include "StateMachine.h"

void IdleState::Enter()
{
	State::Enter();
}

void IdleState::Exit() {
	//
	State::Exit();
}


void IdleState::Movement() {
	if (timer > 5.f)
		owner->stateMachine->ChangeState(L"Move");
		//owner->GetStateMachine()->ChangeState(L"Move");
}

void IdleState::Shooting() {
	//this->owner;
}
