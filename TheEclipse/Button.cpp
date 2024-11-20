#include "pch.h"
#include "RectTransform.h"
#include "Button.h"

void Button::Initialize()
{

}

void Button::OnClick()
{
	_owner->SetPos({ _owner->GetPos().x + 10, _owner->GetPos().y });
}
