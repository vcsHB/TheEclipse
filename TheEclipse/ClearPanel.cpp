#include "pch.h"
#include "RectTransform.h"
#include "ClearPanel.h"

#include "TextPro.h"
#include "Image.h"
#include "ResourceManager.h"

void ClearPanel::OnEnable()
{
	_owner->AddComponent<Image>();
	_panelImage = _owner->GetComponent<Image>();
	_owner->AddComponent<TextPro>();
	_textCompo = _owner->GetComponent<TextPro>();
	Close();

}

void ClearPanel::Initialize()
{
	_panelImage->SetTexture(GET_SINGLE(ResourceManager)->TextureLoad(L"Black_BG", L"Texture\\Black_BG_Panel.bmp"));
	wstring content = L"집행관을 쓰러뜨렸습니다.";
	_textCompo->SetText(content, 14.f);
}

void ClearPanel::Open()
{
	_owner->enabled = true;
}

void ClearPanel::Close()
{
	_owner->enabled = false;
}
