#include "pch.h"
#include "Canvas.h"
#include "RectTransform.h"
#include "Button.h"
#include "InputManager.h"
Canvas::Canvas()
{
}

Canvas::~Canvas()
{
	for (RectTransform* rectTrm : _uiList)
	{
		if (rectTrm  != nullptr)
			delete rectTrm;
	}
	_uiList.clear();
}

void Canvas::Initialize()
{
	for (RectTransform* rectTrm : _uiList)
	{
		if (rectTrm != nullptr)
			rectTrm->Initialize();
	}

}

void Canvas::Update()
{
	for (RectTransform* panel : _uiList)
	{
		if(panel)
			panel->Update();
	}

	if (GET_KEYDOWN(KEY_TYPE::LBUTTON))
	{
		GetUIInPosition(GET_MOUSEPOS);
	}
}

void Canvas::Render(HDC _hdc)
{
	for (RectTransform* panel : _uiList)
	{
		if(panel)
			panel->Render(_hdc);
	}
}


RectTransform Canvas::GetUIInPosition(Vec2 position)
{

	// 위치를 입력 받아 그 위치에 해당하는 RectTransform을 반환
	for (RectTransform* ui : _uiList)
	{
		RECT rect = ui->GetRect();
		
		if (position.x < rect.right && position.x > rect.left && position.y > rect.top && position.y < rect.bottom)
		{ // RECT안의 점 조건
			Button* button = ui->GetComponent<Button>();
			if (button == nullptr)
				continue;
			button->OnClick();
		}
	}

	return RectTransform();
}
