#include "pch.h"
#include "TimeManager.h"
#include "Player.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Projectile.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "EventManager.h"
#include "Status.h"
#include "PlayerStatus.h"
#include "Stat.h"
#include "PoolManager.h"
#include "HealthGauge.h"
#include "Canvas.h"
#include "RectTransform.h"

int dirX = 0;
int dirY = 0;
Player::Player(WorldSpaceScene* scene)
{
	//m_pTex = new Texture;
	//wstring path = GET_SINGLE(ResourceManager)->GetResPath();
	//path += L"Texture\\planem.bmp";
	//m_pTex->Load(path);
	//m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Player", L"Texture\\planem.bmp");
	m_hWnd = GET_SINGLE(Core)->GetHwnd();
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"PlayerIdle", L"Texture\\Player_Idle-Sheet.bmp");

	playerStatus = new PlayerStatus(15, 1, 3, 1, 1, 1, 0);
	status = playerStatus;
	
	AddComponent<Collider>();
	AddComponent<Animator>();
	AddComponent<HealthComponent>();
	healthComponent = GetComponent<HealthComponent>();
	healthComponent->SetMaxHealth(status->healthStat->GetValue());
	healthComponent->SetHp(status->healthStat->GetValue());
	healthComponent->SetOwner(this);
	
	GetComponent<Animator>()->CreateAnimation(L"PlayerIdle", m_pTex, Vec2(40.f, 0.f),
		Vec2(40.f, 40.f), Vec2(40.f, 0.f), 5, 0.1f);
	/*GetComponent<Animator>()->CreateAnimation(L"Player_Idle-Sheet", m_pTex, Vec2(0.f, 150.f),
		Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.1f);*/
	GetComponent<Animator>()->PlayAnimation(L"PlayerIdle", true);
	currentScene = scene;

}


Player::~Player()
{
	//Agent::~Agent();
	//if (nullptr != m_pTex)
	//	delete m_pTex;

}
void Player::Start()
{
	_healthGauge = currentScene->GetCanvas()->Find("HealthGaugeFill")->GetComponent<HealthGauge>();
	healthComponent->OnHealthChangedEvent.Add(std::bind(&HealthGauge::HandleRefreshGauge, _healthGauge, std::placeholders::_1, std::placeholders::_2));

}
void Player::Update()
{
	Movement();
	Shooting();
}

Vec2 Player::OriginPos()
{
	int ResolutionX = GetSystemMetrics(SM_CXSCREEN);  //1920
	int ResolutionY = GetSystemMetrics(SM_CYSCREEN);  //1080

	int Winposx = ResolutionX / 2 - SCREEN_WIDTH / 2;
	int Winposy = ResolutionY / 2 - SCREEN_HEIGHT / 2;
	return { Winposx, Winposy };
}


void Player::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	//RECT_RENDER(_hdc, vPos.x, vPos.y
	//	, vSize.x, vSize.y);
	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();
	//::BitBlt(_hdc
	//	, (int)(vPos.x - vSize.x / 2)
	//	, (int)(vPos.y - vSize.y / 2)
	//	, width, height,
	//	m_pTex->GetTexDC()
	//	,0,0,SRCCOPY
	//);
	/*::TransparentBlt(_hdc
		, (int)(vPos.x - width / 2)
		, (int)(vPos.y - height / 2)
		, width, height,
		m_pTex->GetTexDC()
		, 0, 0,width, height, RGB(255,0,255));*/
	ComponentRender(_hdc);
	//::StretchBlt();
	//::AlphaBlend();
	//::PlgBlt();

}

void Player::EnterCollision(Collider* _other)
{

}

void Player::StayCollision(Collider* _other)
{
}

void Player::ExitCollision(Collider* _other)
{
}

void Player::Movement()
{
	auto p = OriginPos();

	currentScene->m_moveSpeed = 100.f * status->moveSpeedStat->GetValue();
	_currentDashTime += GET_SINGLE(TimeManager)->GetDT();
	float moveAmount = currentScene->m_moveSpeed * fDT;
	Vec2 moveDirection = { 0,0 };
	if (GET_KEY(KEY_TYPE::A))
	{
		moveDirection.x = -1;

	}
	if (GET_KEY(KEY_TYPE::D))
	{
		if (moveDirection.x == -1) moveDirection.x = 0;
		moveDirection.x = 1;
	}
	if (GET_KEY(KEY_TYPE::W))
	{
		moveDirection.y = -1;

	}
	if (GET_KEY(KEY_TYPE::S))
	{
		if (moveDirection.y == -1) moveDirection.y = 0;
		moveDirection.y = 1;
	}

	Vec2 dashDirection = {0,0};
	moveDirection.Normalize();
	if (GET_KEYDOWN(KEY_TYPE::SPACE))
	{
		if (_currentDashTime > 1.f)
		{
			_currentDashTime = 0.f;
			dashDirection = moveDirection * 100.f;

		}
	}

	currentScene->m_deltaPos = moveDirection  + dashDirection;

	int windowSizeX = GetSystemMetrics(SM_CXSCREEN);
	int windowSizeY = GetSystemMetrics(SM_CXSCREEN);
	float Winposx = windowSizeX / 2 - SCREEN_WIDTH / 2;
	float Winposy = windowSizeY / 2 - SCREEN_HEIGHT / 2;

	float widthClamp = windowSizeX / 2 - SCREEN_WIDTH;
	float heightClamp = windowSizeY / 2 - SCREEN_HEIGHT;


	currentScene->m_WorldPosition = currentScene->m_WorldPosition + moveDirection * moveAmount + dashDirection;
	currentScene->m_WorldPosition.x = std::clamp(currentScene->m_WorldPosition.x, -widthClamp, widthClamp);
	currentScene->m_WorldPosition.y = std::clamp(currentScene->m_WorldPosition.y, -heightClamp, heightClamp);
	SetWindowPos(m_hWnd, HWND_TOP,
		p.x + currentScene->m_WorldPosition.x + dashDirection.x, p.y + currentScene->m_WorldPosition.y + dashDirection.y,
		0, 0, SWP_NOSIZE | SWP_SHOWWINDOW | SWP_ASYNCWINDOWPOS);
}

void Player::Shooting()
{
	int fireSpeed = playerStatus->fireSpeedStat->GetValue();
	_currentShootCoolTime += GET_SINGLE(TimeManager)->GetDT() * (1 + fireSpeed * 0.2f);
	if (_currentShootCoolTime >= 1.f)
	{
		_currentShootCoolTime = 0;
		//Vec2 dir = { (Vec2)GET_MOUSEPOS - GetPos() };
		Vec2 direction = { 0, -1 };
		CreateProjectile(direction);
	}
}	

void Player::CreateProjectile(Vec2 dir)
{
	int projectileAmount = playerStatus->bulletMultipleStat->GetValue();
	Vec2 fireOriginPos = GetPos();
	fireOriginPos.y -= GetSize().y / 2.f;
	for (int i = 0; i < projectileAmount; i++)
	{
		float x = (-(20.f * 0.5f) * (projectileAmount - 1) + i * 20.f) + fireOriginPos.x;
		Vec2 generatePos = { x, fireOriginPos.y };
		GenerateProjectile(generatePos, dir);
	}
}

Projectile* Player::GenerateProjectile(Vec2 position, Vec2 direction)
{

	Projectile* pProj = dynamic_cast<Projectile*>(PoolManager::Pop(PoolingType::Projectile));

	pProj->SetPos(position);
	pProj->SetSize({ 20.f,20.f });
	pProj->m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Bullet", L"Texture\\Bullet.bmp");

	// 도 -> 라디안: PI / 180
	//pProj->SetAngle(PI / 4 * 7.f); // 1
	//static float angle = 0.f;
	//pProj->SetAngle(angle * PI / 180); // 2
	//angle += 10.f;
	pProj->SetDir(direction);
	pProj->SetName(L"PlayerBullet");
	pProj->SetProjectile(status->atkStat->GetValue());
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pProj, LAYER::PROJECTILE);

	return pProj;
}
