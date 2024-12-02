#include "pch.h"
#include "UpgradeButton.h"
#include "RectTransform.h"
#include "UpgradeData.h"
#include "TextPro.h"
#include "ResourceManager.h"
#include "Image.h"
#include "Button.h"



void UpgradeButton::OnEnable()
{
	_owner->AddComponent<Image>();
	_owner->GetComponent<Image>()->SetTexture(GET_SINGLE(ResourceManager)->TextureLoad(L"Upgrade_Panel", L"Texture\\Upgrade_Panel.bmp"));
	_owner->AddComponent<Button>();
	_owner->AddComponent<TextPro>();
}

void UpgradeButton::Initialize()
{
	_textCompo = _owner->GetComponent<TextPro>();

}

void UpgradeButton::SetUpgradeData(UpgradeData* data)
{
	_content = data->upgradeName + L"\n" + data->description;
	_textCompo->SetText(_content, 16);

}
