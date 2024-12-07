#include "pch.h"
#include "State.h"
#include "ChaseState.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Player.h"
#include "StateMachine.h"


void ChaseState::Enter()
{
	State::Enter();
	int _bulletCount = 20;
	Vec2 dir;
	for (int i = 0; i < _bulletCount; i++)
	{
		float angle = 360.f / _bulletCount * i;
		float x = cosf(angle * PI / 180);
		float y = sinf(angle * PI / 180);

		dir = { x, y };
		Projectile* pProj = owner->CreateProjectile({ 0,0 });
		pProj->SetPos({ dir.x * 200 + owner->GetPos().x  , dir.y * 200 + owner->GetPos().y });
		pProj->isAnimated = true;
		projectilles[i] = (pProj);
	}
}

void ChaseState::Exit()
{
	projIdx = 0;
	State::Exit();
}

void ChaseState::Movement(float _dt)
{
	timerforMove += _dt;

	if (timerforMove <= 6)
	{
		for (int i = 0; i < 20; i++)
		{
			float angle = 360.f / 20 * i;
			float x = cosf(angle * PI / 180);
			float y = sinf(angle * PI / 180);

			Vec2 dir = { x,y };
			projectilles[i]->SetPos({ dir.x * 200 + owner->GetPos().x  , dir.y * 200 + owner->GetPos().y });
		}

		Vec2 playerPos = player->GetPos();

		Vec2 dir = playerPos - owner->GetPos();

		dir.Normalize();

		vPos += dir * _dt * 100.f;
	}
}

void ChaseState::Shooting(float _dt)
{
	timerforShot += _dt;

	Vec2 dir = player->GetPos();

	if (timerforShot > 6)
	{

		targetingTime += _dt;

		if (targetingTime > .2f)
		{
			if (projectilles[projIdx] != nullptr)
			{
				projectilles[projIdx]->SetDir(dir - projectilles[projIdx]->GetPos());
				projectilles[projIdx]->moveSpeed = 2;
				projIdx++;
				targetingTime = 0;
			}

			if (20 == projIdx)
			{
				owner->GetStateMachine()->ChangeState(L"WallThrow");
			}
		}
	}
}
