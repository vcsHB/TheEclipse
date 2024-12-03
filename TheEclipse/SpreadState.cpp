#include "pch.h"
#include "State.h"
#include "SpreadState.h"
#include "Enemy.h"
#include "StateMachine.h"

Vec2 dirArr[4] = {  };
int atkIdx = 0;
int _bulletCount = 24;
void SpreadState::Enter()
{
	State::Enter();
}

void SpreadState::Exit() {
	//
	State::Exit();
}


void SpreadState::Movement(float _dt) {

	timerforMove += _dt;


	if (timerforMove > 8.f)
		owner->GetStateMachine()->ChangeState(L"Idle");


	if (timerforMove < 2.f)
	{
		vPos.x -= (200 * _dt);
	}
	else if (timerforMove >= 2.f && timerforMove < 6.f)
	{
		vPos.x += (200 * _dt);
	}
	else
	{
		vPos.x -= (200 * _dt);
	}

}

void SpreadState::Shooting(float _dt) {

	timerforShot += _dt;

	if (timerforShot > 1.f)
	{
		timerforShot = 0;
		Vec2 dir;
		for (int i = 0; i < 24; i++)
		{
			float angle = 360.f / _bulletCount * i;
			float x = cosf(angle * PI / 180);
			float y = sinf(angle * PI / 180);
			{
				owner->CreateProjectile({ x,y });
			}
		}
	}
}
