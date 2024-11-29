#include "pch.h"
#include "GameScene_2.h"
#include "Enemy.h"
#include "Player.h"
#include "CollisionManager.h"
#include "ResourceManager.h"

void GameScene_2::Init()
{
	HWND m_hWnd1;
	HWND m_hWnd2;
	Object* pPlayer = new Player(this);
	pPlayer->SetPos({ SCREEN_WIDTH / 2.f, 500.f });
	pPlayer->SetSize({ 100.f, 100.f });
	pPlayer->SetName(L"Player");
	AddObject(pPlayer, LAYER::PLAYER);

	Object* pBoss = new Enemy(this);
	pBoss->SetSize({ 100.f, 100.f });
	pBoss->SetPos({ SCREEN_WIDTH / 2.f, 150.f });
	pBoss->SetName(L"Enemy");
	AddObject(pBoss, LAYER::ENEMY);


	//Object* backGround = new 

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::PLAYER);
}

void GameScene_2::Update()
{
}
