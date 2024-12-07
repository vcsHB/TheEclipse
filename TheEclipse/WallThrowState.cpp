#include "pch.h"
#include "State.h"
#include "WallThrowState.h"
#include "CrackLine.h"
#include "Enemy.h"
#include "Player.h"
#include "StateMachine.h"
#include "ResourceManager.h"	
#include "Collider.h"	
#include "Animator.h"	
#include "Animation.h"	
#include "EventManager.h"	

void WallThrowState::Enter()
{

	int idx = 16;

	Vec2 playerPos = player->GetPos();



	for (int i = 0; i < idx; i++)
	{
		CrackLine* pCrackLine = owner->CreateCrackLine();

		pCrackLine->SetPos(
			{ playerPos.x + positionArr[i].x
			, playerPos.y + positionArr[i].y
			});

		if (i < 4 || i >= 8 && i < 12)
		{
			pCrackLine->GetComponent<Collider>()->SetSize({ 550, 30 });
			pCrackLine->m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"CrackLineWidth", L"Texture\\CrackLineWidth.bmp");

			pCrackLine->GetComponent<Animator>()->CreateAnimation(L"CrackLineWidth", pCrackLine->m_pTex, Vec2(0.f, 0.f),
				Vec2(512.f, 32.f), Vec2(0.f, 32.f), 5, 0.03f, true);
			pCrackLine->GetComponent<Animator>()->PlayAnimation(L"CrackLineWidth", true);
		}

		crackLines[i] = pCrackLine;
	}

	State::Enter();

}

void WallThrowState::Exit()
{
	waitTime = 0;
	crackLineIdx = 0;

	for (int i = 0; i < 16; i++)
	{
		GET_SINGLE(EventManager)->DeleteObject(crackLines[i]);
	}
	State::Exit();
}

void WallThrowState::Movement(float _dt)
{

}

void WallThrowState::Shooting(float _dt)
{
	waitTime += _dt;
	Vec2 pos = crackLines[crackLineIdx]->GetPos();
	Vec2 curPos = positionArr[crackLineIdx];

	if (waitTime > 1.f)
	{
		timerforShot += _dt;


		if (timerforShot < 2)
		{

			int posX = abs(curPos.x);
			int posY = abs(curPos.y);

			if (posX == 150 && curPos.y == -300)
				crackLines[crackLineIdx]->SetPos({ pos.x, pos.y += _dt * 300 });
			else if (posX == 150 && curPos.y == 300)
				crackLines[crackLineIdx]->SetPos({ pos.x, pos.y += _dt * -300 });
			else if (posY == 150 && curPos.x == -300)
				crackLines[crackLineIdx]->SetPos({ pos.x += _dt * +300 , pos.y });
			else if (posY == 150 && curPos.x == 300)
				crackLines[crackLineIdx]->SetPos({ pos.x += _dt * -300 , pos.y });
		}

		if (timerforShot >= 3)
		{
			timerforShot = 0;
			crackLineIdx++;
		}
	}

	if (crackLineIdx >= 8)
	{
		owner->GetStateMachine()->ChangeState(L"Target");
	}
}
