#pragma once
#include "Object.h"
#include "Core.h"
class Texture;
class Player : public Object
{
public:
	Player();
	~Player();
public:
	void Update() override;
	void Render(HDC _hdc) override;
public:
	int m_hp;
private:
	void CreateProjectile();
	Texture* m_pTex;
	HWND m_hWnd = GET_SINGLE(Core)->GetHwnd();
};

