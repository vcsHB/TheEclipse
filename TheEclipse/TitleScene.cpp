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
#include "TimeManager.h"
#include "TextPro.h"
#include "FadePanel.h"

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
	canvasObj->SetName(L"TitleCanvas");
	AddObject(canvasObj, LAYER::UI);
	Canvas* canvas = dynamic_cast<Canvas*>(canvasObj);
	SetCanvas(canvas);
	RectTransform* testUI_1 = new RectTransform("Logo");
	RectTransform* titleBg = new RectTransform("titleBg");

	TextPro* textPro = new TextPro();

	testUI_1->SetSize({ 500, 300 }); // Image넣는 순간 의미 없음
	testUI_1->SetPos({ 250, 120 });
	testUI_1->AddComponent<Image>();
	testUI_1->GetComponent<Image>()->SetTexture(GET_SINGLE(ResourceManager)->TextureLoad(L"GameLogo", L"Texture\\GameLogo.bmp"));
	
	titleBg->SetSize({ 500, 300 }); // Image넣는 순간 의미 없음
	titleBg->SetPos({ 250, 350 });
	titleBg->AddComponent<Image>();
	titleBg->GetComponent<Image>()->SetTexture(GET_SINGLE(ResourceManager)->TextureLoad(L"BG", L"Texture\\TitleBG1.bmp"));


	RectTransform* startButton = new RectTransform("quitButton");
	startButton->SetPos({ 250, 300 });
	startButton->AddComponent<Image>();
	startButton->GetComponent<Image>()->SetTexture(GET_SINGLE(ResourceManager)->TextureLoad(L"Button", L"Texture\\Button_Panel.bmp"));
	startButton->AddComponent<Button>();
	startButton->GetComponent<Button>()->OnClickEvent.Add(std::bind(&TitleScene::HandleGameStart, this, std::placeholders::_1));
	startButton->AddComponent<TextPro>();
	wstring content = L" 시작";
	startButton->GetComponent<TextPro>()->SetText(content, 15);

	RectTransform* quitButton = new RectTransform("quitButton");
	quitButton->SetPos({ 250, 400 });
	quitButton->AddComponent<Image>();
	quitButton->GetComponent<Image>()->SetTexture(GET_SINGLE(ResourceManager)->TextureLoad(L"Button", L"Texture\\Button_Panel.bmp"));
	quitButton->AddComponent<Button>();
	quitButton->AddComponent<TextPro>();
	content = L" 종료";
	
	quitButton->GetComponent<TextPro>()->SetText(content, 15);

	RectTransform* fadePanel = new RectTransform("FadePanel");
	fadePanel->AddComponent<FadePanel>();
	fadePanel->GetComponent<FadePanel>();


	canvas->AddRectPanel(titleBg);
	canvas->AddRectPanel(testUI_1);
	canvas->AddRectPanel(startButton);
	canvas->AddRectPanel(quitButton);
	canvas->AddRectPanel(fadePanel);

	canvas->Initialize();

	//GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::ENEMY);
	GET_SINGLE(ResourceManager)->LoadSound(L"BGM", L"Sound\\to-the-death.wav", true);
	GET_SINGLE(ResourceManager)->Play(L"BGM");
	
}

void TitleScene::Update()
{
	Scene::Update();
	
	if (_isExiting)
	{
		_currentExitTime += fDT;
		if (_currentExitTime >= _exitDuration)
		{
			_currentExitTime = 0;
			_isExiting = false;
			GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::BGM);
			GET_SINGLE(SceneManager)->LoadScene(L"GameScene2");


		}
	}
	/*if (GET_KEYDOWN(KEY_TYPE::ENTER))
		GET_SINGLE(SceneManager)->LoadScene(L"GameScene2");*/
}


void TitleScene::HandleGameStart(bool value)
{
	if (_isExiting) return;
	_canvas->Find("FadePanel")->GetComponent<FadePanel>()->Fade(true);
	_isExiting = true;
}
