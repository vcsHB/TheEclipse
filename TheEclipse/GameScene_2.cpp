#include "pch.h"
#include "GameScene_2.h"
#include "Enemy.h"
#include "Player.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "RectTransform.h"
#include "Canvas.h"
#include "Image.h"
#include "TextPro.h"
#include "Button.h"
#include "UpgradeButton.h"
#include "UpgradeManager.h"
#include "ExpGauge.h"
#include "State.h"
#include "IdleState.h"
#include "SpreadState.h"
#include "TargetingState.h"
#include "ClampingState.h"

void GameScene_2::Init()
{
	HWND m_hWnd1;
	HWND m_hWnd2;
	Player* pPlayer = new Player(this);
	pPlayer->SetPos({ SCREEN_WIDTH / 2.f, 500.f });
	pPlayer->SetSize({ 100.f, 100.f });
	pPlayer->SetName(L"Player");
	player = pPlayer;
	AddObject(pPlayer, LAYER::PLAYER);

	Canvas* canvas = new Canvas();
	AddObject(canvas, LAYER::UI);
	SetCanvas(canvas);

	RectTransform* healthEdgeUI = new RectTransform("HealthGaugeEdge");
	healthEdgeUI->SetPos({ 250, 650 });
	healthEdgeUI->AddComponent<Image>();
	healthEdgeUI->GetComponent<Image>()->SetTexture(GET_SINGLE(ResourceManager)->TextureLoad(L"GaugeEdge", L"Texture\\Gauge_Edge.bmp"));
	RectTransform* healthFillUI = new RectTransform("HealthGaugeFill");
	healthFillUI->SetPos({ 250, 650 });
	healthFillUI->AddComponent<Image>();
	healthFillUI->GetComponent<Image>()->SetTexture(GET_SINGLE(ResourceManager)->TextureLoad(L"GaugeFill", L"Texture\\Gauge_Fill.bmp"));
	RectTransform* healthText = new RectTransform("HealthText");
	healthText->SetPos({ 250, 670 });
	healthText->AddComponent<TextPro>();
	wstring content = L"HP (50/50)";
	healthText->GetComponent<TextPro>()->SetText(content, 20);



	RectTransform* upgradeButton_1 = new RectTransform("UpgradePanel_1");
	upgradeButton_1->SetPos({250, 220});
	upgradeButton_1->AddComponent<UpgradeButton>();

	RectTransform* upgradeButton_2 = new RectTransform("UpgradePanel_2");
	upgradeButton_2->AddComponent<UpgradeButton>();
	upgradeButton_2->SetPos({ 250, 370 });
	upgradeButton_1->AddActiveGroup(upgradeButton_2);
	upgradeButton_1->SetActive(false);

	RectTransform* expGauge = new RectTransform("ExpGauge");
	expGauge->SetPos({ 250, 630 });
	expGauge->AddComponent<ExpGauge>();

	canvas->AddRectPanel(healthEdgeUI);
	canvas->AddRectPanel(healthFillUI);
	canvas->AddRectPanel(healthText);
	canvas->AddRectPanel(upgradeButton_1);
	canvas->AddRectPanel(upgradeButton_2);
	canvas->AddRectPanel(expGauge);

	// === Enemy Setting
	map<wstring, State*> stage1;
	stage1.insert(std::pair<wstring, State*>(L"Idle", new IdleState(L"IdleState")));
	stage1.insert(std::pair<wstring, State*>(L"Spread", new SpreadState(L"SpreadState")));
	stage1.insert(std::pair<wstring, State*>(L"Target", new TargetingState(L"TargetingState")));
	stage1.insert(std::pair<wstring, State*>(L"Clamp", new ClampingState(L"ClampingState")));

	map <wstring, State*> stage2;
	stage2.insert(std::pair<wstring, State*>(L"Idle", new IdleState(L"IdleState")));
	stage2.insert(std::pair<wstring, State*>(L"Move", new TargetingState(L"MoveState")));

	stateData = new map<int, map<wstring, State*>>();
	stateData->insert(std::pair<int, map<wstring, State*>>(1, stage1));
	stateData->insert(std::pair<int, map<wstring, State*>>(2, stage2));
	Enemy* pBoss = new Enemy(this, &stateData->at(1));
	pBoss->SetSize({ 100.f, 100.f });
	pBoss->SetPos({ SCREEN_WIDTH / 2.f, 150.f });
	pBoss->SetName(L"Enemy");
	AddObject(pBoss, LAYER::ENEMY);



	//Object* backGround = new 
	GET_SINGLE(UpgradeManager)->Initialize(

		upgradeButton_1->GetComponent<UpgradeButton>(),
		upgradeButton_2->GetComponent<UpgradeButton>(),
		expGauge->GetComponent<ExpGauge>(),
		pPlayer
	);

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::PLAYER);
}

void GameScene_2::Update()
{
	Scene::Update();
}
