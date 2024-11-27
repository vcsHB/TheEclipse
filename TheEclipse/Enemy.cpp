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



Enemy::Enemy(GameScene* scene)
{
	AddComponent<Collider>();
	AddComponent<HealthComponent>();
	healthComponent = GetComponent<HealthComponent>();
	healthComponent->SetHp(10);
	healthComponent->SetOwner(this);
	currentScene = scene;

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
	Movement();
	Shooting();
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
	if (GET_KEYDOWN(KEY_TYPE::SPACE))
	{

		Vec2 dir = { 0 , 1 };
		CreateProjectile(dir, currentScene);
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

void Enemy::CreateProjectile(Vec2 dir, GameScene* scene)
{
	Projectile* pProj = new Projectile(scene);
	Vec2 vPos = GetPos();
	vPos.y += GetSize().y / 2.f;
	pProj->SetPos(vPos);
	pProj->SetSize({ 30.f,30.f });


	// 도 -> 라디안: PI / 180
	//pProj->SetAngle(PI / 4 * 7.f); // 1
	//static float angle = 0.f;
	//pProj->SetAngle(angle * PI / 180); // 2
	//angle += 10.f;
	pProj->SetDir(dir);
	pProj->SetName(L"EnemyBullet");
	//Vec2 a = { 10.f, 10.f };
	//Vec2 b = { 0.f, 0.f };
	//Vec2 c = a / b;

	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pProj, LAYER::PROJECTILE);
}