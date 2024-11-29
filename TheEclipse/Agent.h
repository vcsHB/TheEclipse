#pragma once
#include "Object.h"
#include "Core.h"
#include "GameScene.h"
class Texture;
class Agent :
	public Object
{  
public:
	virtual void Movement();
	virtual void Shooting();
public:
	WorldSpaceScene* currentScene;
	Texture* m_pTex = nullptr;
	HWND m_hWnd = GET_SINGLE(Core)->GetHwnd();
};

