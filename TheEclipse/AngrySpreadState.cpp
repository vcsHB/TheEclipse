#include "pch.h"
#include "State.h"	
#include "AngrySpreadState.h"
#include "Projectile.h"
#include "Player.h"	
#include "Enemy.h"	
#include "StateMachine.h"	


void AngrySpreadState::Enter()
{
	State::Enter();
	vPos = { player->GetPos().x , player->GetPos().y - 300 };
}

void AngrySpreadState::Exit()
{
	State::Exit();
}

void AngrySpreadState::Movement(float _dt)
{

	if (isTransed == false)
		transTime += _dt;

	timerforMove += _dt;


	if (transTime >= 4)
	{
		isTransed = true;
		vPos.x = player->GetPos().x + 300;
		transTime = 0;
	}


	if (timerforMove < 2)
	{
		vPos.x -= (300 * _dt);
	}
	else if (timerforMove >= 2.f && timerforMove < 4.f)
	{
		vPos.y += (300 * _dt);
	}
	else  if (timerforMove >= 4.f && timerforMove < 6.f)
	{
		vPos.y -= (300 * _dt);
	}
	else if (timerforMove >= 6.f && timerforMove < 8.f)
	{
		vPos.x -= (150 * _dt);
	}


	if (timerforMove > 10.f)
	{
		owner->GetStateMachine()->ChangeState(L"AngryClamp");
	}

}

void AngrySpreadState::Shooting(float _dt)
{
	timerforShot += _dt;

	if (timerforShot > 1.f)
	{
		timerforShot = 0;
		Vec2 dir;
		for (int i = 0; i < 24; i++)
		{
			float angle = 360.f / 24 * i;
			float x = cosf(angle * PI / 180);
			float y = sinf(angle * PI / 180);
			{
				Projectile* pProj = owner->CreateProjectile({ x,y });
				pProj->moveSpeed = 2;
				pProj->isAnimated = true;
			}
		}
	}
}
