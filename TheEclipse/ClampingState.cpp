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

	vPos = { player->GetPos().x, player->GetPos().y - 300.f };

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

		crackLines[i] = pProj;
	}

}

void ClampingState::Exit()
{
	for (int i = 0; i < 4; i++)
	{
		GET_SINGLE(EventManager)->DeleteObject(crackLines[i]);
	}
	State::Exit();
}

void ClampingState::Movement(float _dt)
{
	timerforMove += _dt;
	if (timerforMove > 10.f)
		owner->GetStateMachine()->ChangeState(L"Side");


}

void ClampingState::Shooting(float _dt)
{


}
