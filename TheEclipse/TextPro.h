#pragma once
#include <string>
#include "CanvasComponent.h"

class TextPro : public CanvasComponent
{
private :
	wstring _content;
	float _fontSize = 1.f;
	HFONT _font;
	COLORREF _color;
	UINT _alignType;
	

public :
	void Initialize() override;
	void SetText(wstring& content, float size = 12, COLORREF color = RGB(255, 255, 255), UINT alignType = TA_CENTER);
	void ChangeTextContent(wstring& content);
	void Render(HDC hdc) override;
	

};

