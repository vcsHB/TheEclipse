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
	void SetText(wstring& content, float size, COLORREF color, UINT alignType);

	void Render(HDC hdc) override;
	

};

