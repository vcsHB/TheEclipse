#include "pch.h"
#include "TimeManager.h"
#include "Enemy.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Projectile.h"
#include "Texture.h"	
#include "ResourceManager.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "EventManager.h"
#include "State.h"
#include "StateMachine.h"

Enemy::Enemy(WorldSpaceScene* scene, map<wstring, State*> *states)
{
	AddComponent<Collider>();
	AddComponent<HealthComponent>();
	healthComponent = GetComponent<HealthComponent>();
	healthComponent->SetHp(10);
	healthComponent->SetOwner(this);
	currentScene = scene;

	stateMachine = new StateMachine(this, states);
	
	stateMachine->ChangeState(L"Idle");

	/*m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Jiwoo", L"Texture\\jiwoo.bmp");
	GetComponent<Animator>()->CreateAnimation(L"JiwooFront", m_pTex, Vec2(0.f, 150.f),
		Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.1f);
	GetComponent<Animator>()->PlayAnimation(L"JiwooFront", true);*/

}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
	stateMachine->Update();
}

void Enemy::Movement()
{
	Vec2 vPos = GetPos();
	vPos.x -= currentScene->m_moveSpeed * fDT * currentScene->m_deltaPos.x;
	vPos.y -= currentScene->m_moveSpeed * fDT * currentScene->m_deltaPos.y;



	Object::SetPos(vPos);
}

void Enemy::Shooting()
{
	Vec2 dir;

	for (int i = 0; i < 24; i++)
	{
		dir = { cosf(i), sinf(i) };
		CreateProjectile(dir);
	}
}


void Enemy::Render(HDC _hdc)
{
	//HBRUSH brush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
	//HBRUSH oldbrush = (HBRUSH)SelectObject(_hdc, brush);
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	RECT_RENDER(_hdc, vPos.x, vPos.y
		, vSize.x, vSize.y);
	ComponentRender(_hdc);
	//SelectObject(_hdc, oldbrush); 
	//DeleteObject(brush);
}

void Enemy::EnterCollision(Collider* _other)
{
	std::cout << "Enemy Enter" << std::endl;
	Object* pOtherObj = _other->GetOwner();
	wstring str = pOtherObj->GetName();
	if (pOtherObj->GetName() == L"PlayerBullet")
	{
		if (healthComponent->DecreaseHP(1))
			GET_SINGLE(EventManager)->DeleteObject(this);
	}
}

void Enemy::StayCollision(Collider* _other)
{
	//std::cout << "Stay" << std::endl;
}

void Enemy::ExitCollision(Collider* _other)
{
	std::cout << " Enemy Exit" << std::endl;
}
/*
StateMachine* Enemy::GetStateMachine()
{	
	return stateMachine; 
}*/

void Enemy::CreateProjectile(Vec2 dir)
{
	Projectile* pProj = new Projectile(currentScene);
	Vec2 vPos = GetPos();
	dir.Normalize();

	pProj->SetPos(vPos + dir * 3);
	pProj->SetSize({ 30.f,30.f });

	// 도 -> 라디안: PI / 180
	//pProj->SetAngle(PI / 4 * 7.f); // 1
	//pProj->SetDir({ cosf(duration) , sinf(duration) }); // 2
	//if (duration >= 120)
	//	duration = 30.f;
	//duration += 10.f;

	pProj->SetDir(dir);
	pProj->SetName(L"EnemyBullet");
	//Vec2 a = { 10.f, 10.f };
	//Vec2 b = { 0.f, 0.f };
	//Vec2 c = a / b;

	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pProj, LAYER::PROJECTILE);
}