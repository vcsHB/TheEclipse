#include "pch.h"
#include "ExpGauge.h"
#include "RectTransform.h"
#include "ResourceManager.h"
#include "Image.h"

void ExpGauge::OnEnable()
{
	_owner->AddComponent<Image>();
	_fillImage = _owner->GetComponent<Image>();
	_fillImage->SetTexture(GET_SINGLE(ResourceManager)->TextureLoad(L"Upgrade_Panel", L"Texture\\Upgrade_Panel.bmp"));
}

void ExpGauge::Initialize()
{
}

void ExpGauge::SetFillAmount(int current, int max)
{

	_fillImage->SetHorizontalFillAmount(current / (float)max);
}
