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
#include "Projectile.h"


void ClampingState::Enter()
{
	State::Enter();
	shootTime = 0;
	crackLineIdx = 0;
	sizeIdx = 0;
	vPos = { player->GetPos().x, player->GetPos().y - 300.f };

	for (int i = 0; i < 4; i++)
	{

		CrackLine* pProj = owner->CreateCrackLine();
		crackLines[crackLineIdx] = pProj;
		crackLineIdx++;
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
	}
}

void ClampingState::Exit()
{
	for (int i = 0; i < crackLineIdx; i++)
	{
		GET_SINGLE(EventManager)->DeleteObject(crackLines[i]);
	}
	State::Exit();

}

void ClampingState::Movement(float _dt)
{
	timerforMove += _dt;
	if (timerforMove > 8.f)
		owner->GetStateMachine()->ChangeState(L"Side");


}

void ClampingState::Shooting(float _dt)
{
	timerforShot += _dt;
	shootTime += _dt;

	if (timerforShot > 2)
	{


		for (int i = 0; i < 4; i++)
		{
			CrackLine* pProj = owner->CreateCrackLine();

			crackLines[crackLineIdx] = pProj;
			crackLineIdx++;
			if (i < 2)
			{
				pProj->m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"CrackLineWidth", L"Texture\\CrackLineWidth.bmp");

				pProj->GetComponent<Animator>()->CreateAnimation(L"CrackLineWidth", pProj->m_pTex, Vec2(0.f, 0.f),
					Vec2(512.f, 32.f), Vec2(0.f, 32.f), 5, 0.03f, true);
				pProj->GetComponent<Animator>()->PlayAnimation(L"CrackLineWidth", true);
			}
			switch (i)
			{
			case 0:
				pProj->GetComponent<Collider>()->SetSize({ 550, 30 });
				pProj->SetPos({ player->GetPos().x  , player->GetPos().y - sizeArr[sizeIdx] });
				break;
			case 1:
				pProj->GetComponent<Collider>()->SetSize({ 550, 30 });
				pProj->SetPos({ player->GetPos().x  , player->GetPos().y + sizeArr[sizeIdx] });
				break;
			case 2:

				pProj->GetComponent<Collider>()->SetSize({ 30, 550 });
				pProj->SetPos({ player->GetPos().x - sizeArr[sizeIdx] , player->GetPos().y });
				break;
			case 3:
				pProj->GetComponent<Collider>()->SetSize({ 30, 550 });
				pProj->SetPos({ player->GetPos().x + sizeArr[sizeIdx] , player->GetPos().y });
				break;
			}
		}
		timerforShot = 0;
		sizeIdx++;
	}


	Vec2 playerPos = player->GetPos();
	if (shootTime > 0.5f)
	{
		Projectile* pProj = owner->CreateProjectile(playerPos - vPos);
		pProj->isAnimated = true;
		shootTime = 0;
	}
}
