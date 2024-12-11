#include "pch.h"
#include "Enemy.h"
#include "TimeManager.h"
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
#include "PoolManager.h"
#include "HealthGauge.h"
#include "Canvas.h"
#include "RectTransform.h"
#include "GameManager.h"

Enemy::Enemy(WorldSpaceScene* scene, map<int, map<wstring, State*>>* states)
{
	statesArr = states;

	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Boss", L"Texture\\Boss.bmp");

	status = new Status(300, 2, 3);
	AddComponent<Collider>();
	AddComponent<Animator>();
	AddComponent<HealthComponent>();
	colliderComponent = GetComponent <Collider>();
	colliderComponent->SetSize({ 100.f, 100.f });
	healthComponent = GetComponent<HealthComponent>();
	healthComponent->OnDieEvent.Add(std::bind(&Enemy::HandleDieEvent, this, std::placeholders::_1));
	healthComponent->SetMaxHealth(status->healthStat->GetValue());
	healthComponent->FillMaxHealth();
	healthComponent->SetOwner(this);
	GetComponent<Animator>()->CreateAnimation(L"Boss", m_pTex, Vec2(0.f, 0.f),
		Vec2(80.f, 80.f), Vec2(80.f, 0.f), 8, 0.1f);
	GetComponent<Animator>()->PlayAnimation(L"Boss", true);
	HealthGauge* gauge = scene->GetCanvas()->Find("Enemy_HealthGaugeFill")->GetComponent<HealthGauge>();
	healthComponent->OnHealthChangedEvent.Add(std::bind(&HealthGauge::HandleRefreshGauge, gauge, std::placeholders::_1, std::placeholders::_2));

	currentScene = scene;

	stateMachine = new StateMachine(this, &statesArr->at(1));

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
	if (isBlinking)
	{
		blinkDuration += fDT;

		if (blinkDuration > 0.3f)
		{
			isBlinking = false;
			Blink(isBlinking);
		}
	}

	if (GET_KEY(KEY_TYPE::J))
	{
		isAngry = true;
		ChangeToAngryMode();
		Blink(false);
	}

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

void Enemy::ChangeToAngryMode()
{
	stateMachine->SetStateList(this, &statesArr->at(2));
	isAngry = true;
	Blink(false);
}
void Enemy::EnterCollision(Collider* _other)
{
	Object* pOtherObj = _other->GetOwner();
	wstring str = pOtherObj->GetName();
	if (pOtherObj->GetName() == L"PlayerBullet")
	{
		if (healthComponent->DecreaseHP(1))
			GET_SINGLE(EventManager)->DeleteObject(this);
		GET_SINGLE(ResourceManager)->LoadSound(L"BossHit", L"Sound\\BossHit.wav", false);
		GET_SINGLE(ResourceManager)->Play(L"BossHit");
		Blink(true);

		if (healthComponent->GetHp() <= 50 && isAngry == false)
		{
			ChangeToAngryMode();
		}
	}
}

void Enemy::StayCollision(Collider* _other)
{
	//std::cout << "Stay" << std::endl;
}

void Enemy::ExitCollision(Collider* _other)
{
}

StateMachine* Enemy::GetStateMachine()
{
	return stateMachine;
}



Projectile* Enemy::CreateProjectile(Vec2 dir)
{
	Projectile* pProj = new Projectile(currentScene);   //dynamic_cast<Projectile*>(PoolManager::Pop(PoolingType::Projectile));


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
		Vec2(32.f, 512.f), Vec2(32.f, 0.f), 5, 0.03f, true);
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
	pProj->GetComponent<Collider>()->SetSize({ 30.f, 550.f });
	//Vec2 a = { 10.f, 10.f };
	//Vec2 b = { 0.f, 0.f };
	//Vec2 c = a / b;

	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pProj, LAYER::CRACKLINE);

	return pProj;
}

void Enemy::Blink(bool active)
{

	Agent::Blink(active);

	if (isAngry)
	{
		if (active)
		{
			DoAnimation(L"AngryBossHit", L"Texture\\AngryBossHit.bmp");
		}
		else
		{
			DoAnimation(L"AngryBoss", L"Texture\\AngryBoss.bmp");
		}
	}
	else
	{
		if (active)
		{
			DoAnimation(L"BossHit", L"Texture\\BossHit.bmp");
		}
		else
		{
			DoAnimation(L"Boss", L"Texture\\Boss.bmp");
		}
	}
}

void Enemy::DoAnimation(wstring name, wstring path)
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(name, path);
	GetComponent<Animator>()->CreateAnimation(name, m_pTex, Vec2(0.f, 0.f),
		Vec2(80.f, 80.f), Vec2(80.f, 0.f), 8, 0.1f);
	GetComponent<Animator>()->PlayAnimation(name, true);
}

void Enemy::HandleDieEvent(bool value)
{
	GET_SINGLE(GameManager)->GameClear();
}



