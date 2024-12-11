#pragma once
#include "Object.h"
#include "Core.h"
#include "GameScene.h"
class Status;
class Collider;
class Texture;

class Agent :
	public Object
{
public:
	virtual ~Agent() override;
public:
	virtual void Shooting();
	virtual void Movement();
	virtual void KnockBack();
	virtual void Blink(bool active);
public:
	WorldSpaceScene* currentScene;
	Status* status;
	Texture* m_pTex = nullptr;
	HWND m_hWnd = GET_SINGLE(Core)->GetHwnd();
	Collider* colliderComponent;
	bool isBlinking = false;
	float blinkDuration = 0;
};

