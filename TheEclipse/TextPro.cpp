#include "pch.h"
#include "TextPro.h"
#include "RectTransform.h"
#include "GDISelector.h"

void TextPro::Initialize()
{ 
	AddFontResource(TEXT("\\Resource\\Font\\Silver"));
	_font = CreateFont(
		(int)(((float)_fontSize / 2 )* 3), _fontSize, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET,
		0, 0, 0, VARIABLE_PITCH | FF_ROMAN,
		TEXT("Silver")
	);

}

void TextPro::SetText(wstring& content, float size = 12, COLORREF color = RGB(255,255,255), UINT alignType = TA_CENTER)
{
	_content = content;
	_fontSize = size;
	_color = color;
	_alignType = alignType;

}

void TextPro::Render(HDC hdc)
{
	
	SelectObject(hdc, _font);
	
	SetTextColor(hdc, _color);
	SetTextAlign(hdc, _alignType);

	
	GDISelector(hdc, _font);
	TextOut(hdc, _owner->GetPos().x, _owner->GetPos().y, _content.c_str(), _content.length());
}
