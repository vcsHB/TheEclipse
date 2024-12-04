#include "pch.h"
#include "TimeManager.h"
#include "Enemy.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Projectile.h"
#include "CrackLine.h"
#include "Texture.h"	
#include "ResourceManager.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "EventManager.h"
#include "State.h"
#include "StateMachine.h"
#include "Status.h"
#include "Stat.h"

Enemy::Enemy(WorldSpaceScene* scene, map<wstring, State*>* states)
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Boss", L"Texture\\Boss.bmp");
	m_pTex2 = GET_SINGLE(ResourceManager)->TextureLoad(L"AngryBoss", L"Texture\\AngryBoss.bmp");

	status = new Status(300, 2, 3);
	AddComponent<Collider>();
	AddComponent<Animator>();
	AddComponent<HealthComponent>();
	colliderComponent = GetComponent <Collider>();
	colliderComponent->SetSize({ 100.f, 100.f });
	healthComponent = GetComponent<HealthComponent>();
	healthComponent->SetHp(status->healthStat->GetValue());
	healthComponent->SetOwner(this);
	GetComponent<Animator>()->CreateAnimation(L"Boss", m_pTex, Vec2(0.f, 0.f),
		Vec2(80.f, 80.f), Vec2(80.f, 0.f), 8, 0.1f);
	GetComponent<Animator>()->PlayAnimation(L"Boss", true);

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
	///Agent::~Agent();
}

void Enemy::Update()
{
	stateMachine->Update(fDT);
}




void Enemy::Render(HDC _hdc)
{
	//HBRUSH brush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
	//HBRUSH oldbrush = (HBRUSH)SelectObject(_hdc, brush);
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();

	//RECT_RENDER(_hdc, vPos.x, vPos.y
	//	, vSize.x, vSize.y);
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

StateMachine* Enemy::GetStateMachine()
{
	return stateMachine;
}

Projectile* Enemy::CreateProjectile(Vec2 dir)
{
	Projectile* pProj = new Projectile(currentScene);


	pProj->m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"SpinSword", L"Texture\\SpinSword.bmp");

	pProj->GetComponent<Animator>()->CreateAnimation(L"SpinSword", pProj->m_pTex, Vec2(0.f, 0.f),
		Vec2(32.f, 32.f), Vec2(32.f, 0.f), 8, 0.03f, true);
	pProj->GetComponent<Animator>()->PlayAnimation(L"SpinSword", true);


	Vec2 vPos = GetPos();
	dir.Normalize();

	pProj->SetPos(vPos + dir);
	pProj->SetSize({ 30.f,30.f });
	pProj->SetProjectile(status->atkStat->GetValue());

	// 도 -> 라디안: PI / 180
	//pProj->SetAngle(PI / 4 * 7.f); // 1
	//pProj->SetDir({ cosf(duration) , sinf(duration) }); // 2
	//if (duration >= 120)
	//	duration = 30.f;
	//duration += 10.f;

	pProj->SetDir(dir);
	pProj->SetName(L"EnemyBullet");
	pProj->GetComponent<Collider>()->SetSize({ 30.f,30.f });
	//Vec2 a = { 10.f, 10.f };
	//Vec2 b = { 0.f, 0.f };
	//Vec2 c = a / b;

	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pProj, LAYER::PROJECTILE);

	return pProj;
}

CrackLine* Enemy::CreateCrackLine()
{
	CrackLine* pProj = new CrackLine(currentScene);


	pProj->m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"CrackLine", L"Texture\\CrackLine.bmp");

	pProj->GetComponent<Animator>()->CreateAnimation(L"CrackLine", pProj->m_pTex, Vec2(0.f, 0.f),
		Vec2(32.f, 512.f), Vec2(32.f, 0.f), 8, 0.03f, true);
	pProj->GetComponent<Animator>()->PlayAnimation(L"CrackLine", true);


	Vec2 vPos = GetPos();

	pProj->SetLineDamage(status->atkStat->GetValue());

	// 도 -> 라디안: PI / 180
	//pProj->SetAngle(PI / 4 * 7.f); // 1
	//pProj->SetDir({ cosf(duration) , sinf(duration) }); // 2
	//if (duration >= 120)
	//	duration = 30.f;
	//duration += 10.f;

	pProj->SetName(L"EnemyLine");
	pProj->GetComponent<Collider>()->SetSize({ 30.f, 300.f });
	//Vec2 a = { 10.f, 10.f };
	//Vec2 b = { 0.f, 0.f };
	//Vec2 c = a / b;

	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pProj, LAYER::CRACKLINE);

	return pProj;
}

