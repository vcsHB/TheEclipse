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
void TitleScene::Init()
{
	Object* pObj = new Enemy;
	pObj->SetPos({ SCREEN_WIDTH / 2.f,150.f });
	pObj->SetSize({ 100.f,100.f });
	pObj->SetName(L"Enemy");
	AddObject(pObj, LAYER::ENEMY);

	// ĵ���� ��������...
	Object* canvasObj = new Canvas;
	canvasObj->SetName(L"Canvas");
	AddObject(canvasObj, LAYER::UI);
	Canvas* canvas = dynamic_cast<Canvas*>(canvasObj);
	RectTransform* testUI_1 = new RectTransform();

	testUI_1->SetSize({ 500, 300 });
	testUI_1->SetPos({ 500, 300 });
	testUI_1->AddComponent<Image>();
	testUI_1->AddComponent<Button>();
	canvas->AddRectPanel(testUI_1);

	canvas->Initialize();

	Object* pPlayer = new Player;
	pPlayer->SetPos({ SCREEN_WIDTH / 2.f,500.f });
	pPlayer->SetSize({ 100.f,100.f });
	AddObject(pPlayer, LAYER::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::ENEMY);
	//GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::ENEMY);
	GET_SINGLE(ResourceManager)->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	GET_SINGLE(ResourceManager)->Play(L"BGM");
}

void TitleScene::Update()
{
	Scene::Update();
	if (GET_KEYDOWN(KEY_TYPE::ENTER))
		GET_SINGLE(SceneManager)->LoadScene(L"GameScene");
}
