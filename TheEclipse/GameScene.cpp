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
	Object* pPlayer = new Player;
	pPlayer->SetPos({ SCREEN_WIDTH / 2.f, 500.f });
	pPlayer->SetSize({ 100.f, 100.f });
	AddObject(pPlayer, LAYER::PLAYER);

	Object* pBoss = new Enemy;
	pBoss->SetSize({ 100.f, 100.f });
	pBoss->SetPos({ SCREEN_WIDTH / 2.f, 100.f });

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::ENEMY);
	

}

void GameScene::Update()
{
	//if()
}




