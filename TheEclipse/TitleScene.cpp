#include "pch.h"
#include "TitleScene.h"
#include "Object.h"
#include "Player.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Enemy.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "RectTransform.h"
#include "Canvas.h"
#include "Image.h"
#include "Button.h"
#include "TextPro.h"

void TitleScene::Init()
{
	/*Object* pObj = new Enemy();
	pObj->SetPos({ SCREEN_WIDTH / 2.f,150.f });
	pObj->SetSize({ 100.f,100.f });
	pObj->SetName(L"Enemy");
	pObj->GetComponent<HealthComponent>()->SetHp(10);
	AddObject(pObj, LAYER::ENEMY);*/

	// 캔버스 만들어보리기...
	Object* canvasObj = new Canvas;
	canvasObj->SetName(L"Canvas");
	AddObject(canvasObj, LAYER::UI);
	Canvas* canvas = dynamic_cast<Canvas*>(canvasObj);
	SetCanvas(canvas);
	RectTransform* testUI_1 = new RectTransform("Test");
	TextPro* textPro = new TextPro();

	testUI_1->SetSize({ 500, 300 }); // Image넣는 순간 의미 없음
	testUI_1->SetPos({ 150, 300 });
	testUI_1->AddComponent<Image>();
	testUI_1->GetComponent<Image>()->SetTexture(GET_SINGLE(ResourceManager)->TextureLoad(L"test_Panel", L"Texture\\test_Panel.bmp"));
	testUI_1->AddComponent<Button>();
	testUI_1->AddComponent<TextPro>();
	wstring msg = L"겜프밍";
	testUI_1->GetComponent<TextPro>()->SetText(msg, 6, RGB(255,255,255), TA_CENTER);
	
	RectTransform* healthEdgeUI = new RectTransform("HealthGaugeEdge");
	healthEdgeUI->SetPos({ 300, 50 });
	healthEdgeUI->AddComponent<Image>();
	healthEdgeUI->GetComponent<Image>()->SetTexture(GET_SINGLE(ResourceManager)->TextureLoad(L"GaugeEdge", L"Texture\\Gauge_Edge.bmp"));
	RectTransform* healthFillUI = new RectTransform("HealthGaugeFill");
	healthFillUI->SetPos({ 300, 50 });
	healthFillUI->AddComponent<Image>();
	healthFillUI->GetComponent<Image>()->SetTexture(GET_SINGLE(ResourceManager)->TextureLoad(L"GaugeFill", L"Texture\\Gauge_Fill.bmp"));

	

	canvas->AddRectPanel(testUI_1);
	canvas->AddRectPanel(healthEdgeUI);
	canvas->AddRectPanel(healthFillUI);
	canvas->Initialize();

	
	//GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::ENEMY);
	GET_SINGLE(ResourceManager)->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	GET_SINGLE(ResourceManager)->Play(L"BGM");
	
}

void TitleScene::Update()
{
	Scene::Update();
	if (GET_KEYDOWN(KEY_TYPE::F))
	{
		ming -= 5;
		_canvas->Find("HealthGaugeFill")->GetComponent<Image>()->SetHorizontalFillAmount(ming / 100.f);
	}
	

	if (GET_KEYDOWN(KEY_TYPE::ENTER))
		GET_SINGLE(SceneManager)->LoadScene(L"GameScene");
}
