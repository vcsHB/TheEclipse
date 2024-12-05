
#include "pch.h"
#include "State.h"
#include "TargetingState.h"
#include "Enemy.h"
#include "Player.h"
#include "StateMachine.h"
#include "Projectile.h"


void TargetingState::Enter()
{
	State::Enter();
	projIdx = 0;

	int _bulletCount = 20;
	Vec2 dir;
	for (int i = 0; i < 24; i++)
	{
		float angle = 360.f / _bulletCount * i;
		float x = cosf(angle * PI / 180);
		float y = sinf(angle * PI / 180);


		dir = { x, y };
		Projectile* pProj = owner->CreateProjectile({ 0,0 });
		pProj->SetPos({ dir.x * 200 + player->GetPos().x  , dir.y * 200 + player->GetPos().y });
		pProj->isAnimated = true;
		projectilles[i] = (pProj);
	}
}


void TargetingState::Exit()
{
	waittime = 0;
	State::Exit();
}

void TargetingState::Movement(float _dt)
{
	timerforMove += _dt;

	Vec2 enemyPos = owner->GetPos();

	Vec2 dir = player->GetPos();
	dir = dir - enemyPos;
	vPos.x += dir.x * _dt * 10.f;
}

void TargetingState::Shooting(float _dt)
{
	Vec2 dir = player->GetPos();
	timerforShot += _dt;
	waittime += _dt;
	if (waittime > 1.f)
	{
		if (timerforShot >= 0.2f)
		{

			projectilles[projIdx]->SetDir(dir - projectilles[projIdx]->GetPos());
			timerforShot = 0;
			projIdx++;

			if (24 == projIdx)
			{
				owner->GetStateMachine()->ChangeState(L"Idle");
			}
		}
	}

	//Projectile* pProj =
	//pProj->SetPos()


}
