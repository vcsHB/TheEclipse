#include "pch.h"
#include "State.h"
#include "Enemy.h"
#include "TimeManager.h"

State::State(wstring name)
{
	this->name = name;
}

void State::Init(Enemy* owner)
{
	this->owner = owner;
}

void State::Enter()
{
	std::wcout << name << "   " << L"Enter" << endl;
}

void State::Update()
{
	// 창이동 보정 처리
	Vec2 vPos = owner->GetPos();
	vPos.x -= owner->currentScene->m_moveSpeed * fDT * owner->currentScene->m_deltaPos.x;
	vPos.y -= owner->currentScene->m_moveSpeed * fDT * owner->currentScene->m_deltaPos.y;

	owner->Object::SetPos(vPos);

	Timer();
	Movement();
	Shooting();
}

void State::Exit()
{
	timer = 0;
	std::wcout << name << "   " << L"Exit" << endl;
}

void State::Timer()
{
	timer += fDT;
}
