#pragma once
#include "CanvasComponent.h"
class Button : public CanvasComponent
{
public :
	void Initialize() override;
public:
	
	// ����Ǵ� ��ü
	void OnClick();
};

