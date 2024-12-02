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

void GameScene_2::Init()
{
	HWND m_hWnd1;
	HWND m_hWnd2;
	Object* pPlayer = new Player(this);
	pPlayer->SetPos({ SCREEN_WIDTH / 2.f, 500.f });
	pPlayer->SetSize({ 100.f, 100.f });
	pPlayer->SetName(L"Player");
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

	canvas->AddRectPanel(healthEdgeUI);
	canvas->AddRectPanel(healthFillUI);
	canvas->AddRectPanel(healthText);
	canvas->AddRectPanel(upgradeButton_1);
	canvas->AddRectPanel(upgradeButton_2);


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
	Scene::Update();
}
