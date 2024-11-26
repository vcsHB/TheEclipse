#pragma once
#include <vector>
#include "Object.h"
class RectTransform;

class Canvas : public Object
{
public:
	Canvas();
	~Canvas();
private:
	vector<RectTransform*> _uiList;
	
public:

	void Initialize();
	void Update() override;
	void Render(HDC _hdc) override;
	void AddRectPanel(RectTransform* newPanel)
	{
		_uiList.push_back(newPanel);
	}

	// 해당 위치에 있는 UI를 가져온다. 
	// ( 우선순위를 관리해야하나 싶긴 한데 일단은 걍 최대한 안겹치게끔 노력을 해봅시다. )
	RectTransform GetUIInPosition(Vec2 position);


};

