#include "pch.h"
#include "Image.h"
#include "GDISelector.h"
#include "RectTransform.h"

void Image::Render(HDC hdc)
{

	PEN_TYPE ePen = PEN_TYPE::GREEN;
	GDISelector pen(hdc, ePen);
	GDISelector brush(hdc, BRUSH_TYPE::HOLLOW);
	RECT_RENDER(hdc, _owner->GetPos().x, _owner->GetPos().y,
		_owner->GetSize().x, _owner->GetSize().y);
}
