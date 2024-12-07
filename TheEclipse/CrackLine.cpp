#include "pch.h"
#include "CrackLine.h"
#include "Animation.h"
#include "Animator.h"
#include "GameScene.h"
#include "HealthComponent.h"
#include "EventManager.h"
#include "TimeManager.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "Core.h"

CrackLine::CrackLine(WorldSpaceScene* scene)
{
	AddComponent<Animator>();
	currentScene = scene;
	AddComponent<Collider>();
}

CrackLine::~CrackLine()
{
}

void CrackLine::Update()
{
	Vec2 vPos = GetPos();

	vPos.x -= (currentScene->m_moveSpeed * fDT * currentScene->m_deltaPos.x);
	vPos.y -= (currentScene->m_moveSpeed * fDT * currentScene->m_deltaPos.y);

	Object::SetPos(vPos);
}

void CrackLine::Render(HDC _hdc)
{
	ComponentRender(_hdc);
	//ELLIPSE_RENDER(_hdc, vPos.x, vPos.y
	//	, vSize.x, vSize.y);

}

void CrackLine::SetLineDamage(int damage)
{
	_damage = damage;
}

void CrackLine::SetPos(Vec2 v)
{
	originPos = v;
	Object::SetPos(v);
}

void CrackLine::EnterCollision(Collider* _other)
{
	Object* pOtherObj = _other->GetOwner();

	Vec2 playerPos = pOtherObj->GetPos();

	Vec2 m_Pos = GetPos();
	if (pOtherObj->GetName() == L"Player" && m_name == L"EnemyLine")
	{
		//std::cout << "Proj Enter" << std::endl;
		HealthComponent* health = _other->GetOwner()->GetComponent<HealthComponent>();
		health->DecreaseHP(_damage);
	}
}

void CrackLine::StayCollision(Collider* _other)
{

}

void CrackLine::ExitCollision(Collider* _other)
{
}
