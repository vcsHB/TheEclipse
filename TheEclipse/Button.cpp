#include "pch.h"
#include "RectTransform.h"
#include "Button.h"
#include "Image.h"

void Button::Initialize()
{
	_image = _owner->GetComponent<Image>();
	_size = _image->GetTextureSize();
}

void Button::OnClick()
{
	_owner->SetPos({ _owner->GetPos().x + 10, _owner->GetPos().y });
}
