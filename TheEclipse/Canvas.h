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

	// �ش� ��ġ�� �ִ� UI�� �����´�. 
	// ( �켱������ �����ؾ��ϳ� �ͱ� �ѵ� �ϴ��� �� �ִ��� �Ȱ�ġ�Բ� ����� �غ��ô�. )
	RectTransform GetUIInPosition(Vec2 position);


};

