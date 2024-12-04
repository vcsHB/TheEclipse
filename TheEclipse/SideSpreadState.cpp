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

	if (timerforMove > 3)
	{
		switch (moveIdx)
		{
		case 0:
			owner->SetPos({ player->GetPos().x , player->GetPos().y - 300 });
			break;
		case 1:
			owner->SetPos({ player->GetPos().x - 300, player->GetPos().y });
			break;
		case 2:
			owner->SetPos({ player->GetPos().x , player->GetPos().y + 300 });
			break;
		case 3:
			owner->SetPos({ player->GetPos().x + 300 , player->GetPos().y });
			break;
		}
		timerforMove = 0;
		moveIdx++;
	}

	if (durationTime > 14.f)
	{
		owner->GetStateMachine()->ChangeState(L"Idle");
	}
}

void SideSpreadState::Shooting(float _dt)
{
	timerforShot += _dt;
	if (timerforShot > 3)
	{

		Vec2 playerPos = player->GetPos();

		for (int i = 0; i < 10; i++)
		{
			float angle = 360 / 10 * i;
			float x = cosf(angle * PI / 180);
			float y = sinf(angle * PI / 180);
			Projectile* pProj = owner->CreateProjectile({ x,y });
			pProj->isAnimated = true;
			pProj->SetPos(owner->GetPos());
		}

		timerforShot = 0;
	}
}
