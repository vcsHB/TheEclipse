#include "pch.h"
#include "GameScene_2.h"
#include "WorldSpaceScene.h"
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
#include "SideSpreadState.h"
#include "AngrySpreadState.h"
#include "AngryClampState.h"
#include "PoolManager.h"
#include "HealthGauge.h"
#include "ParticleSystem.h"
#include "ChaseState.h"
#include "WallThrowState.h"

#include "ClearPanel.h"
#include "OverPanel.h"
#include "GameManager.h"
#include "FadePanel.h"

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
	healthFillUI->AddComponent<HealthGauge>();

	RectTransform* healthText = new RectTransform("HealthText");
	healthText->SetPos({ 250, 670 });
	healthText->AddComponent<TextPro>();
	wstring content = L"HP (20/20)";
	healthFillUI->GetComponent<HealthGauge>()->SetTextCompo(healthText->GetComponent<TextPro>());
	healthText->GetComponent<TextPro>()->SetText(content, 10);

	
	// Enemy Health
	RectTransform* bossHealthEdgeUI = new RectTransform("Enemy_HealthGaugeEdge");
	bossHealthEdgeUI->SetPos({ 250, 30 });
	bossHealthEdgeUI->AddComponent<Image>();
	bossHealthEdgeUI->GetComponent<Image>()->SetTexture(GET_SINGLE(ResourceManager)->TextureLoad(L"GaugeEdge", L"Texture\\Gauge_Edge.bmp"));
	RectTransform* bossHealthFillUI = new RectTransform("Enemy_HealthGaugeFill");
	bossHealthFillUI->SetPos({ 250, 30 });
	bossHealthFillUI->AddComponent<HealthGauge>();

	RectTransform* bossHealthText = new RectTransform("Enemy_HealthText");
	bossHealthText->SetPos({ 250, 45 });
	bossHealthText->AddComponent<TextPro>();
	bossHealthFillUI->GetComponent<HealthGauge>()->SetTextCompo(bossHealthText->GetComponent<TextPro>());
	content = L"HP (50/50)";
	bossHealthText->GetComponent<TextPro>()->SetText(content, 10);

	RectTransform* bossNameText = new RectTransform("BossNameText");
	bossNameText->SetPos({ 250, 60 });
	bossNameText->AddComponent<TextPro>();
	content = L"ÁýÇàÀÚ ¹Ö±Û¸µ";
	bossNameText->GetComponent<TextPro>()->SetText(content, 13);

	//==

	RectTransform* upgradeButton_1 = new RectTransform("UpgradePanel_1");
	upgradeButton_1->SetPos({ 250, 220 });
	upgradeButton_1->AddComponent<UpgradeButton>();

	RectTransform* upgradeButton_2 = new RectTransform("UpgradePanel_2");
	upgradeButton_2->AddComponent<UpgradeButton>();
	upgradeButton_2->SetPos({ 250, 370 });
	upgradeButton_1->AddActiveGroup(upgradeButton_2);
	upgradeButton_1->SetActive(false);

	RectTransform* expGauge = new RectTransform("ExpGauge");
	expGauge->SetPos({ 250, 630 });
	expGauge->AddComponent<ExpGauge>();

	RectTransform* clearPanel = new RectTransform("ClearPanel");
	clearPanel->AddComponent <ClearPanel>();

	RectTransform* overPanel = new RectTransform("OverPanel");
	clearPanel->AddComponent <OverPanel>();
	GET_SINGLE(GameManager)->Initialize(clearPanel, overPanel);


	RectTransform* fadePanel = new RectTransform("FadePanel");
	fadePanel->AddComponent<FadePanel>();
	fadePanel->GetComponent<FadePanel>();
	fadePanel->GetComponent < FadePanel>()->SetDefault(true);



	canvas->AddRectPanel(healthEdgeUI);
	canvas->AddRectPanel(healthFillUI);
	canvas->AddRectPanel(healthText);

	canvas->AddRectPanel(bossHealthEdgeUI);
	canvas->AddRectPanel(bossHealthFillUI);
	canvas->AddRectPanel(bossHealthText);
	canvas->AddRectPanel(bossNameText);

	canvas->AddRectPanel(upgradeButton_1);
	canvas->AddRectPanel(upgradeButton_2);
	canvas->AddRectPanel(expGauge);


	canvas->AddRectPanel(fadePanel);


	canvas->Initialize();
	// === Enemy Setting
	map<wstring, State*> stage1;
	stage1.insert(std::pair<wstring, State*>(L"Idle", new IdleState(L"IdleState")));
	stage1.insert(std::pair<wstring, State*>(L"Spread", new SpreadState(L"SpreadState")));
	stage1.insert(std::pair<wstring, State*>(L"Target", new TargetingState(L"TargetingState")));
	stage1.insert(std::pair<wstring, State*>(L"Clamp", new ClampingState(L"ClampingState")));
	stage1.insert(std::pair<wstring, State*>(L"Side", new SideSpreadState(L"SideSpreadState")));


	map <wstring, State*> stage2;
	stage2.insert(std::pair<wstring, State*>(L"Idle", new IdleState(L"IdleState")));
	stage2.insert(std::pair<wstring, State*>(L"AngrySpread", new AngrySpreadState(L"AngrySpreadState")));
	stage2.insert(std::pair<wstring, State*>(L"AngryClamp", new AngryClampState(L"AngryClampState")));
	stage2.insert(std::pair<wstring, State*>(L"Target", new TargetingState(L"TargetingState")));
	stage2.insert(std::pair<wstring, State*>(L"Side", new SideSpreadState(L"SideSpreadState")));
	stage2.insert(std::pair<wstring, State*>(L"Chase", new ChaseState(L"ChaseState")));
	stage2.insert(std::pair<wstring, State*>(L"Clamp", new ClampingState(L"ClampingState")));
	stage2.insert(std::pair<wstring, State*>(L"WallThrow", new WallThrowState(L"WallThrowState")));



	stateData = new map<int, map<wstring, State*>>();
	stateData->insert(std::pair<int, map<wstring, State*>>(1, stage1));
	stateData->insert(std::pair<int, map<wstring, State*>>(2, stage2));
	Enemy* pBoss = new Enemy(this, stateData);
	pBoss->SetSize({ 100.f, 100.f });
	pBoss->SetPos({ SCREEN_WIDTH / 2.f, 150.f });
	pBoss->SetName(L"Enemy");
	AddObject(pBoss, LAYER::ENEMY);

	// ===== Pool Setting =====
	PoolManager::Initialize();
	//IPoolable* poolable = new T;
	for (int i = 0; i < 90; i++)
	{
		Projectile* projectile = new Projectile(this);
		projectile->enabled = false;
		PoolManager::AddPool(PoolingType::Projectile, projectile);
	}

	for (int i = 0; i < 20; i++)
	{
		ParticleSystem* vfx = new ParticleSystem(L"HitVFX", { 0,0 }, 0.2f, 4, 0.7f, 14.3f);
		vfx->enabled = false;
		PoolManager::AddPool(PoolingType::HitVFX, vfx);
	}

	//Object* backGround = new 
	GET_SINGLE(UpgradeManager)->Initialize(

		upgradeButton_1->GetComponent<UpgradeButton>(),
		upgradeButton_2->GetComponent<UpgradeButton>(),
		expGauge->GetComponent<ExpGauge>(),
		pPlayer
	);

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::CRACKLINE, LAYER::PLAYER);


	GET_SINGLE(ResourceManager)->LoadSound(L"BGM", L"Sound\\to-the-death.wav", true);
	GET_SINGLE(ResourceManager)->Play(L"BGM");
	fadePanel->GetComponent<FadePanel>()->Fade(false);
}

void GameScene_2::Update()
{
	Scene::Update();
	GET_SINGLE(GameManager)->Update(); // ²ûÂïÇÑ.
}

void GameScene_2::Release()
{
	GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::BGM);
	Scene::Release();
}
