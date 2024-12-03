#include "pch.h"
#include "State.h"
#include "Enemy.h"
#include "Player.h"
#include "TimeManager.h"

State::State(wstring name)
{
	this->name = name;
}

void State::Init(Enemy* owner)
{
	this->owner = owner;
	player = owner->currentScene->player;
}

void State::Enter()
{
	std::wcout << name << "   " << L"Enter" << endl;
	timerforMove = 0;
	timerforShot = 0;

}

void State::Update(float _dt)
{
	// 창이동 보정 처리
	vPos = owner->GetPos();
	vPos.x -= owner->currentScene->m_moveSpeed * fDT * owner->currentScene->m_deltaPos.x;
	vPos.y -= owner->currentScene->m_moveSpeed * fDT * owner->currentScene->m_deltaPos.y;

	playerPos = player->GetPos();

	Movement(_dt);
	Shooting(_dt);

	owner->Object::SetPos(vPos);
}

void State::Exit()
{
	timerforMove = 0;
	std::wcout << name << "   " << L"Exit" << endl;
}

