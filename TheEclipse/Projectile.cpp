#include "pch.h"
#include "Projectile.h"
#include "TimeManager.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "EventManager.h"
#include "GameScene.h"
#include "HealthComponent.h"
#include "UpgradeManager.h"
#include "Animation.h"
#include "Animator.h"
#include "PoolManager.h"
#include "ParticleSystem.h"

Projectile::Projectile()
	: m_angle(0.f)
	, m_vDir(1.f, 1.f)
	, isAnimated(false)
{
	
}

Projectile::Projectile(WorldSpaceScene* scene)
//	: m_dir(-1.f)
	: m_angle(0.f)
	, m_vDir(1.f, 1.f)
	, isAnimated(false)
{
	AddComponent<Animator>();

	//m_pTex = new Texture;
	//wstring path = GET_SINGLE(ResourceManager)->GetResPath();
	//path += L"Texture\\Bullet.bmp";
	//m_pTex->Load(path);
	currentScene = scene;
	this->AddComponent<Collider>();
	GetComponent<Collider>()->SetSize({ 20.f,20.f });
}

Projectile::~Projectile()
{
}

void Projectile::Update()
{
	_currentLifeTime += GET_SINGLE(TimeManager)->GetDT();
	Vec2 vPos = GetPos();

	// 삼각함수의 단위가 2가지가 있다.
	// 라디안, 디그리
	//vPos.x += cosf(m_angle) * 500.f * fDT;
	//vPos.y += sinf(m_angle) * 500.f * fDT;

	vPos.x += (m_vDir.x * 200.f * fDT * moveSpeed) - (currentScene->m_moveSpeed * fDT * currentScene->m_deltaPos.x);// -currentScene->m_WorldPosition.x);
	vPos.y += (m_vDir.y * 200.f * fDT * moveSpeed) - (currentScene->m_moveSpeed * fDT * currentScene->m_deltaPos.y);// -currentScene->m_WorldPosition.y);

	Object::SetPos(vPos);

	//vPos = originPos;
	//vPos -= currentScene->m_WorldPosition *fDT;
	//Object::SetPos(vPos);
	Vec2 vSize = GetSize();
	if (_currentLifeTime >= lifeTime)
	{
		PoolManager::Push(this);
		//GET_SINGLE(EventManager)->DeleteObject(this);
	}
}

void Projectile::Render(HDC _hdc)
{
	ComponentRender(_hdc);
	//ELLIPSE_RENDER(_hdc, vPos.x, vPos.y
	//	, vSize.x, vSize.y);
	if (isAnimated == false)
	{
		Vec2 vPos = GetPos();
		int width = m_pTex->GetWidth();

		int height = m_pTex->GetHeight();
		::TransparentBlt(_hdc
			, (int)(vPos.x - width / 2)
			, (int)(vPos.y - height / 2)
			, width, height,
			m_pTex->GetTexDC()
			, 0, 0, width, height, RGB(255, 0, 255));
	}
}

void Projectile::SetProjectile(int damage)
{
	_damage = damage;
}

void Projectile::SetPos(Vec2 v)
{
	originPos = v;
	Object::SetPos(v);
}

void Projectile::EnterCollision(Collider* _other)
{
	Object* pOtherObj = _other->GetOwner();

	if (pOtherObj->GetName() == L"Player" && m_name == L"EnemyBullet")
	{
		//std::cout << "Proj Enter" << std::endl;
		PoolManager::Push(this);
		GET_SINGLE(ResourceManager)->LoadSound(L"PlayerHit", L"Sound\\PlayerHit.wav", false);
		GET_SINGLE(ResourceManager)->Play(L"PlayerHit");
		HealthComponent* health = _other->GetOwner()->GetComponent<HealthComponent>();
		health->DecreaseHP(_damage);
		GenerateBreakVFX();


	}
	if (pOtherObj->GetName() == L"Enemy" && m_name == L"PlayerBullet")
	{
		//std::cout << "GetDamage : " << _damage << std::endl;
		PoolManager::Push(this);
		HealthComponent* health = _other->GetOwner()->GetComponent<HealthComponent>();
		health->DecreaseHP(_damage);
		GET_SINGLE(UpgradeManager)->GainExp(4);
		GenerateBreakVFX();

	}
}

void Projectile::StayCollision(Collider* _other)
{
}

void Projectile::ExitCollision(Collider* _other)
{
}

PoolingType Projectile::GetPoolingType()
{
	return PoolingType::Projectile;
}

Object* Projectile::GetPoolObject()
{
	return this;
}

void Projectile::ResetItem()
{
	_currentLifeTime = 0.f;
}

void Projectile::GenerateBreakVFX()
{
	ParticleSystem* vfx = dynamic_cast<ParticleSystem*> (PoolManager::Pop(PoolingType::HitVFX));
	vfx->SetPos(GetPos());
	cout << GetPos().x << " y:" << GetPos().y << endl;
	vfx->Play();
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(vfx, LAYER::PROJECTILE);

}
