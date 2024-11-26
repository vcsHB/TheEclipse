#include "pch.h"
#include "GameScene.h"
#include "Enemy.h"
#include "Player.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
void GameScene::Init()
{
	HWND m_hWnd1;
	HWND m_hWnd2;
	Object* pPlayer = new Player(this);
	pPlayer->SetPos({ SCREEN_WIDTH / 2.f, 500.f });
	pPlayer->SetSize({ 100.f, 100.f });
	pPlayer->SetName(L"Player");
	AddObject(pPlayer, LAYER::PLAYER);

	Object* pBoss = new Enemy(this);
	pBoss->SetName(L"Enemy");
	pBoss->SetSize({ 100.f, 100.f });
	pBoss->SetPos({ SCREEN_WIDTH / 2.f, 150.f });
	AddObject(pBoss, LAYER::ENEMY);


	//Object* backGround = new 

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::ENEMY);
}

void GameScene::Update()
{
	Scene::Update();

}




