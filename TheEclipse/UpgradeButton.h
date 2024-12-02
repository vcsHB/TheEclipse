#pragma once
#include "CanvasComponent.h"
class TextPro;
class UpgradeData;
class Button;
class UpgradeButton : public CanvasComponent
{

public:
	void OnEnable() override;
	void Initialize() override;
	void SetUpgradeData(UpgradeData* data);
private :
	TextPro* _textCompo;
	Button* _button;
	wstring _content;

};

