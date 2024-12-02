#include "pch.h"
#include "State.h"
#include "IdleState.h"
#include "Enemy.h"
#include "StateMachine.h"

Vec2 dirArr[4] = {  };
int atkIdx = 0;

float shotTimer = 10.f;
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
	if (timerforMove > 6.f)
		owner->GetStateMachine()->ChangeState(L"Move");
}

void IdleState::Shooting(float _dt) {

	timerforShot += _dt;

	if (timerforShot > 1.f)
	{
		timerforShot = 0;
		Vec2 dir;
		for (int i = 0; i < 24; i++)
		{
			dir = { cosf(i) + i, sinf(i) + i };
			owner->CreateProjectile(dir);
		}
	}
}
