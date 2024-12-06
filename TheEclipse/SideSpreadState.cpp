#include "pch.h"
#include "State.h"	
#include "SideSpreadState.h"
#include "Player.h"	
#include "Enemy.h"	
#include "StateMachine.h"
#include "Projectile.h"

void SideSpreadState::Enter()
{
	State::Enter();
}

void SideSpreadState::Exit()
{
	owner->SetPos({ player->GetPos().x , player->GetPos().y - 250 });
	moveIdx = 0;
	State::Exit();

}

void SideSpreadState::Movement(float _dt)
{
	timerforMove += _dt;
	durationTime += _dt;

	if (timerforMove > 2)
	{
		switch (moveIdx)
		{
		case 0:
			vPos = { player->GetPos().x - 100, player->GetPos().y };
			break;
		case 1:
			vPos = { player->GetPos().x , player->GetPos().y + 100 };

			break;
		case 2:
			vPos = { player->GetPos().x + 100 , player->GetPos().y };

			break;
		case 3:
			vPos = { player->GetPos().x , player->GetPos().y - 100 };

			break;
		}
		timerforMove = 0;
		moveIdx++;
	}

	if (durationTime > 10.f)
	{
		owner->GetStateMachine()->ChangeState(L"Idle");
	}
}

void SideSpreadState::Shooting(float _dt)
{
	timerforShot += _dt;
	if (timerforShot > 2)
	{

		Vec2 playerPos = player->GetPos();

		for (int i = 0; i < 20; i++)
		{
			float angle = 360 / 20 * i;
			float x = cosf(angle * PI / 180);
			float y = sinf(angle * PI / 180);
			Projectile* pProj = owner->CreateProjectile({ x,y });
			pProj->isAnimated = true;
			pProj->SetPos(owner->GetPos());
		}

		timerforShot = 0;
	}
}
