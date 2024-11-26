#include "pch.h"
#include "Enemy.h"
#include "Collider.h"
#include "EventManager.h"
#include "HealthComponent.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "TimeManager.h"

Enemy::Enemy(GameScene* scene)
{
	this->AddComponent<Collider>();
	this->AddComponent<HealthComponent>();
	healthComponent = GetComponent<HealthComponent>();
	currentScene = scene;
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
	Vec2 vPos = GetPos();
	vPos.x -= currentScene->m_moveSpeed * fDT * currentScene->m_deltaPos.x;
	vPos.y -= currentScene->m_moveSpeed * fDT * currentScene->m_deltaPos.y;
	
	Object::SetPos(vPos);
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
