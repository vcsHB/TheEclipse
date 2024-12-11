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
	_textCompo = _owner->GetComponent<TextPro>();

}

void UpgradeButton::Initialize()
{
	//_textCompo = _owner->GetComponent<TextPro>();

	// �� ���� �ȵ���. ���� ������ ������ �ִµ� ��

}

void UpgradeButton::SetUpgradeData(UpgradeData* data)
{
	_content = data->upgradeName + data->description;
	_textCompo->SetText(_content, 12);
	_textCompo->Initialize();

}
