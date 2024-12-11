#include "pch.h"
#include "OverPanel.h"
#include "RectTransform.h"

#include "TextPro.h"
#include "Image.h"
#include "ResourceManager.h"


void OverPanel::OnEnable()
{
	_owner->AddComponent<Image>();
	_panelImage = _owner->GetComponent<Image>();
	_owner->AddComponent<TextPro>();
	_textCompo = _owner->GetComponent<TextPro>();
	Close();
}

void OverPanel::Initialize()
{
	_panelImage->SetTexture(GET_SINGLE(ResourceManager)->TextureLoad(L"Black_BG", L"Texture\\Black_BG_Panel.bmp"));
	wstring content = L"패배 했습니다.";
	_textCompo->SetText(content, 20.f, RGB(255,1, 1));
	_textCompo->Initialize();
}

void OverPanel::Open()
{
	_owner->enabled = true;
}

void OverPanel::Close()
{
	_owner->enabled = false;
}
