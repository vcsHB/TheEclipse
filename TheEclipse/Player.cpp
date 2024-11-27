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


int dirX = 0;
int dirY = 0;
Player::Player(GameScene* scene)
{
	//m_pTex = new Texture;
	//wstring path = GET_SINGLE(ResourceManager)->GetResPath();
	//path += L"Texture\\planem.bmp";
	//m_pTex->Load(path);
	//m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Player", L"Texture\\planem.bmp");
	m_hWnd = GET_SINGLE(Core)->GetHwnd();
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Jiwoo", L"Texture\\jiwoo.bmp");

	AddComponent<Collider>();
	AddComponent<Animator>();
	AddComponent<HealthComponent>();
	healthComponent = GetComponent<HealthComponent>();
	healthComponent->SetHp(10);
	healthComponent->SetOwner(this);
	GetComponent<Animator>()->CreateAnimation(L"JiwooFront", m_pTex, Vec2(0.f, 150.f),
		Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.1f);
	GetComponent<Animator>()->PlayAnimation(L"JiwooFront", true);
	currentScene = scene;


}
Player::~Player()
{
	//if (nullptr != m_pTex)
	//	delete m_pTex;


}
void Player::Update()
{
	Movement();
	Shooting();
}

Vec2 originPos() {
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
	std::cout << "Enemy Enter" << std::endl;
	Object* pOtherObj = _other->GetOwner();
	wstring str = pOtherObj->GetName();
	if (pOtherObj->GetName() == L"EnemyBullet")
	{
		if (healthComponent->DecreaseHP(1))
		{
			currentScene->m_moveSpeed;
			GET_SINGLE(EventManager)->DeleteObject(this);
		}
	}
}

void Player::StayCollision(Collider* _other)
{
}

void Player::ExitCollision(Collider* _other)
{
}

void Player::Movement()
{
	auto p = originPos();

	if (GET_KEY(KEY_TYPE::A))
	{
		currentScene->m_WorldPosition.x -= currentScene->m_moveSpeed * fDT;
		if (currentScene->m_WorldPosition.x > -525.f)
			dirX = -1;
		else
		{
			dirX = 0;
		}
	}
	if (GET_KEY(KEY_TYPE::D))
	{
		currentScene->m_WorldPosition.x += currentScene->m_moveSpeed * fDT;
		if (currentScene->m_WorldPosition.x < 510.f)
			dirX = 1;
		else
		{
			dirX = 0;
		}
	}

	if (GET_KEY(KEY_TYPE::A) == false && GET_KEY(KEY_TYPE::D) == false ||
		GET_KEY(KEY_TYPE::A) == true && GET_KEY(KEY_TYPE::D) == true) {
		dirX = 0;
	}

	//A x D x 
	//dirX = 0;
	if (GET_KEY(KEY_TYPE::W))
	{
		currentScene->m_WorldPosition.y -= currentScene->m_moveSpeed * fDT;
		if (currentScene->m_WorldPosition.y > -80.f)
			dirY = -1;
		else
			dirY = 0;
	}
	if (GET_KEY(KEY_TYPE::S))
	{
		currentScene->m_WorldPosition.y += currentScene->m_moveSpeed * fDT;
		if (currentScene->m_WorldPosition.y < 50.f)
			dirY = 1;
		else
			dirY = 0;
	}
	if (GET_KEY(KEY_TYPE::W) == false && GET_KEY(KEY_TYPE::S) == false ||
		GET_KEY(KEY_TYPE::W) == true && GET_KEY(KEY_TYPE::S) == true) {
		dirY = 0;
	}

	currentScene->m_deltaPos = { dirX,dirY };

	cout << currentScene->m_WorldPosition.y << endl;

	currentScene->m_WorldPosition.x = std::clamp(currentScene->m_WorldPosition.x, -525.f, 510.f);
	currentScene->m_WorldPosition.y = std::clamp(currentScene->m_WorldPosition.y, -80.f, 50.f);
	SetWindowPos(m_hWnd, HWND_TOP,
		p.x + currentScene->m_WorldPosition.x, p.y + currentScene->m_WorldPosition.y,
		0, 0, SWP_NOSIZE | SWP_SHOWWINDOW | SWP_ASYNCWINDOWPOS);
}

void Player::Shooting()
{
	if (GET_KEYDOWN(KEY_TYPE::LBUTTON))
	{
		Vec2 dir = { (Vec2)GET_MOUSEPOS - GetPos() };
		CreateProjectile(dir, currentScene);
	}
}

void Player::CreateProjectile(Vec2 dir, GameScene* scene)
{

	Projectile* pProj = new Projectile(scene);
	Vec2 vPos = GetPos();
	vPos.y -= GetSize().y / 2.f;
	pProj->SetPos(vPos);
	pProj->SetSize({ 30.f,30.f });


	// 도 -> 라디안: PI / 180
	//pProj->SetAngle(PI / 4 * 7.f); // 1
	//static float angle = 0.f;
	//pProj->SetAngle(angle * PI / 180); // 2
	//angle += 10.f;
	pProj->SetDir(dir);
	pProj->SetName(L"PlayerBullet");
	//Vec2 a = { 10.f, 10.f };
	//Vec2 b = { 0.f, 0.f };
	//Vec2 c = a / b;

	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pProj, LAYER::PROJECTILE);
}
