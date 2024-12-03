#include "pch.h"
#include "State.h"
#include "ClampingState.h"
#include "Enemy.h"
#include "Player.h"
#include "StateMachine.h"
#include "Projectile.h"
#include "ResourceManager.h"
#include "Animator.h"
#include "Animation.h"
#include "EventManager.h"
#include "Collider.h"	


void ClampingState::Enter()
{
	State::Enter();

	for (int i = 0; i < 2; i++)
	{
		Projectile* pProj = owner->CreateProjectile({ 0,0 });
		pProj->m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"CrackLine", L"Texture\\CrackLine.bmp");

		pProj->GetComponent<Animator>()->CreateAnimation(L"CrackLine", pProj->m_pTex, Vec2(0.f, 0.f),
			Vec2(32.f, 512.f), Vec2(32.f, 0.f), 8, 0.03f, true);
		pProj->GetComponent<Animator>()->PlayAnimation(L"CrackLine", true);
		pProj->isAnimated = true;
		pProj->GetComponent<Collider>()->SetSize({ 30, 150 });
		if (i == 0)
		{
			pProj->SetPos({ player->GetPos().x - 200 , playerPos.y + 350 });
		}
		else
		{
			pProj->SetPos({ player->GetPos().x + 200 , playerPos.y + 350 });
		}

		projectiles[i] = pProj;
	}
}

void ClampingState::Exit()
{
	for (int i = 0; i < 2; i++)
	{
		GET_SINGLE(EventManager)->DeleteObject(projectiles[i]);
	}
	waittime = 0;
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
	if (timerforShot > 2)
	{
		timerforShot = 0;

	}
}
