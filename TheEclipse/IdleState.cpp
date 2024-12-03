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


void IdleState::Movement(float _dt) {

	timerforMove += _dt;


	if (owner->GetPos().x >= SCREEN_WIDTH || owner->GetPos().x < 0)
	{
		owner->GetStateMachine()->ChangeState(L"Target");
	}


	if (timerforMove > 4.f)
	{
		owner->GetStateMachine()->ChangeState(L"Spread");
	}
}

void IdleState::Shooting(float _dt) {


}
