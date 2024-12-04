#include "pch.h"
#include "State.h"
#include "ClampingState.h"
#include "Enemy.h"
#include "Player.h"
#include "StateMachine.h"
#include "ResourceManager.h"
#include "Animator.h"
#include "Animation.h"
#include "EventManager.h"
#include "Collider.h"	
#include "CrackLine.h"


void ClampingState::Enter()
{
	State::Enter();

	for (int i = 0; i < 2; i++)
	{
		CrackLine* pProj = owner->CreateCrackLine();

		pProj->GetComponent<Collider>()->SetSize({ 30, 150 });
		if (i == 0)
		{
			pProj->SetPos({ player->GetPos().x - 200 , playerPos.y + 350 });
		}
		else
		{
			pProj->SetPos({ player->GetPos().x + 200 , playerPos.y + 350 });
		}

		crackLines[i] = pProj;
	}

	for (int i = 0; i < 4; i++)
	{
		CrackLine* pProj = owner->CreateCrackLine();
		pProj->SetPos(owner->GetPos());

		shootingCrackLines[i] = pProj;
	}
}

void ClampingState::Exit()
{
	for (int i = 0; i < 2; i++)
	{
		GET_SINGLE(EventManager)->DeleteObject(crackLines[i]);
	}
	State::Exit();
}

void ClampingState::Movement(float _dt)
{
	timerforMove += _dt;
	if (timerforMove > 10.f)
		owner->GetStateMachine()->ChangeState(L"Idle");


}

void ClampingState::Shooting(float _dt)
{

	timerforShot += _dt;

	if ((int)timerforShot % 2 == 0)
	{
		Vec2 dir =
		{ player->GetPos().x , owner->GetPos().y };


	}


}
