#include "pch.h"
#include "Image.h"
#include "GDISelector.h"
#include "RectTransform.h"
#include "Texture.h"
#include "Core.h"

void Image::Initialize()
{
}

void Image::Render(HDC hdc)
{
	Vec2 ownerPos = _owner->GetPos();
	//Vec2 ownerSize = _texture->GGet();
	float width = _texture->GetWidth();
	float height = _texture->GetHeight();

	::TransparentBlt(hdc
		, (int)(ownerPos.x - width / 2)
		, (int)(ownerPos.y - height / 2)
		, width * _horizontalFillAmount, height * _vertialFillAmount,
		_texture->GetTexDC()
		, 0, 0, width * _horizontalFillAmount, height * _vertialFillAmount, RGB(255, 0, 255));



	/*PEN_TYPE ePen = PEN_TYPE::GREEN;
	GDISelector pen(hdc, ePen);
	GDISelector brush(hdc, BRUSH_TYPE::HOLLOW);
	RECT_RENDER(hdc, _owner->GetPos().x, _owner->GetPos().y,
		_owner->GetSize().x, _owner->GetSize().y);*/
}

void Image::SetTexture(Texture* texture)
{
	_texture = texture;
	_owner->SetSize(GetTextureSize());
	
}

Vec2 Image::GetTextureSize()
{
	return Vec2({ _texture->GetWidth(), _texture->GetHeight() });
}
