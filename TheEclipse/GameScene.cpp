#include "pch.h"
#include "GameScene.h"
#include "State.h"	
#include "Enemy.h"
#include "Player.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "IdleState.h"
#include "TargetingState.h"
#include "SpreadState.h"
#include "ClampingState.h"
#include "SideSpreadState.h"
#include "Projectile.h"
#include "PoolManager.h"


void GameScene::Init()
{
	map<wstring, State*> stage1;
	stage1.insert(std::pair<wstring, State*>(L"Idle", new IdleState(L"IdleState")));
	stage1.insert(std::pair<wstring, State*>(L"Spread", new SpreadState(L"SpreadState")));
	stage1.insert(std::pair<wstring, State*>(L"Target", new TargetingState(L"TargetingState")));
	stage1.insert(std::pair<wstring, State*>(L"Clamp", new ClampingState(L"ClampingState")));
	stage1.insert(std::pair<wstring, State*>(L"Side", new SideSpreadState(L"SideSpreadState")));


	map <wstring, State*> stage2;
	stage2.insert(std::pair<wstring, State*>(L"Idle", new IdleState(L"IdleState")));
	stage2.insert(std::pair<wstring, State*>(L"Move", new TargetingState(L"MoveState")));

	stateData = new map<int, map<wstring, State*>>();
	stateData->insert(std::pair<int, map<wstring, State*>>(1, stage1));
	stateData->insert(std::pair<int, map<wstring, State*>>(2, stage2));

	//Object* backGround = new 

	for (int i = 0; i < 120; i++)
	{
		Projectile* projectile = new Projectile(this);
		projectile->enabled = false;
		PoolManager::AddPool(PoolingType::Projectile, projectile);
	}

	SetNextLevel(1);

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::PLAYER);
}

void GameScene::Update()
{
	Scene::Update();

}

void GameScene::SetNextLevel(int level)
{
	//to do 플레이어 초기화 , 적 불러오기 
	ResetPlayer(level);
	SpawnBoss(level);
}

void GameScene::ResetPlayer(int level) {
	Player* pPlayer = new Player(this);

	player = pPlayer;

	pPlayer->SetPos({ SCREEN_WIDTH / 2.f, 500.f });
	pPlayer->SetSize({ 100.f, 100.f });
	pPlayer->SetName(L"Player");
	AddObject(pPlayer, LAYER::PLAYER);
}
void GameScene::SpawnBoss(int level) {
	Enemy* pBoss = new Enemy(this, stateData);
	pBoss->SetSize({ 100.f, 100.f });
	pBoss->SetPos({ SCREEN_WIDTH / 2.f, 150.f });
	pBoss->SetName(L"Enemy");
	//to do 레벨 별 보스 texture 설정 
	AddObject(pBoss, LAYER::ENEMY);
}




