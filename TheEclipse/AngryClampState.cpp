#include "pch.h"
#include "State.h"
#include "AngryClampState.h"
#include "Enemy.h"
#include "Player.h"
#include "Projectile.h"
#include "Collider.h"	
#include "CrackLine.h"
#include "StateMachine.h"
#include "ResourceManager.h"
#include "Animator.h"
#include "Animation.h"
#include "EventManager.h"

void AngryClampState::Enter()
{
	State::Enter();
	crackLineIdx = 0;

	vPos = { player->GetPos().x, player->GetPos().y - 300.f };


	int _bulletCount = 20;
	Vec2 dir;
	for (int i = 0; i < _bulletCount; i++)
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

	for (int i = 0; i < 4; i++)
	{

		CrackLine* pProj = owner->CreateCrackLine();

		if (i >= 2)
		{
			pProj->GetComponent<Collider>()->SetSize({ 550, 30 });
			pProj->m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"CrackLineWidth", L"Texture\\CrackLineWidth.bmp");

			pProj->GetComponent<Animator>()->CreateAnimation(L"CrackLineWidth", pProj->m_pTex, Vec2(0.f, 0.f),
				Vec2(512.f, 32.f), Vec2(0.f, 32.f), 5, 0.03f, true);
			pProj->GetComponent<Animator>()->PlayAnimation(L"CrackLineWidth", true);
			if (i == 2)
			{
				pProj->SetPos({ player->GetPos().x  , player->GetPos().y - 200.f });
			}
			else
			{
				pProj->SetPos({ player->GetPos().x  , player->GetPos().y + 200.f });
			}
		}
		else
		{
			pProj->GetComponent<Collider>()->SetSize({ 30, 550 });
			if (i == 0)
			{
				pProj->SetPos({ player->GetPos().x - 200 , player->GetPos().y });
			}
			else
			{
				pProj->SetPos({ player->GetPos().x + 200 , player->GetPos().y });
			}
		}

		crackLines[crackLineIdx] = pProj;
		crackLineIdx++;
	}

}

void AngryClampState::Exit()
{
	for (int i = 0; i < crackLineIdx; i++)
	{
		GET_SINGLE(EventManager)->DeleteObject(crackLines[i]);
	}
	waittime = 0;
	createTime = 0;
	projIdx = 0;
	isCreated = false;
	State::Exit();
}

void AngryClampState::Movement(float _dt)
{

}

void AngryClampState::Shooting(float _dt)
{
	Vec2 dir = player->GetPos();
	timerforShot += _dt;
	waittime += _dt;
	createTime += _dt;

	if (createTime > 6 && isCreated == false)
	{
		isCreated = true;

		int _bulletCount = 20;
		Vec2 dir;
		for (int i = 0; i < _bulletCount; i++)
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

	if (waittime > 1.f)
	{
		if (timerforShot >= 0.2f)
		{
			if (projectilles[projIdx] != nullptr)
			{
				projectilles[projIdx]->SetDir(dir - projectilles[projIdx]->GetPos());
				projIdx++;
				timerforShot = 0;
			}
			if (20 == projIdx)
			{
				owner->GetStateMachine()->ChangeState(L"Chase");
			}
		}
	}
}
