#pragma once
#include "CanvasComponent.h"
class Button : public CanvasComponent
{
public :
	void Initialize() override;
public:
	
	// 실행되는 주체
	void OnClick();
};

