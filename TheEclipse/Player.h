#pragma once
#include "Object.h"
#include "Core.h"
#include "GameScene.h"
class Texture;
class Player : public Object
{
public:
	Player(GameScene* scene);
	~Player();
public:
	void Update() override;
	void Render(HDC _hdc) override;
	void Movement();
	void Shooting();
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
private:
	void CreateProjectile(Vec2 dir , GameScene* scene);
	GameScene* currentScene;
	Texture* m_pTex;
	HWND m_hWnd = GET_SINGLE(Core)->GetHwnd();	
};

