#include "pch.h"
#include "HealthGauge.h"
#include "RectTransform.h"
#include "Image.h"
#include "TextPro.h"
#include "ResourceManager.h"
#include <string>
#include <sstream>

void HealthGauge::OnEnable()
{
	_owner->AddComponent<Image>();
	_fillGaugeImage = _owner->GetComponent<Image>();
	_fillGaugeImage->SetTexture(GET_SINGLE(ResourceManager)->TextureLoad(L"GaugeFill", L"Texture\\Gauge_Fill.bmp"));

}

void HealthGauge::Initialize()
{

}

void HealthGauge::HandleRefreshGauge(int current, int max)
{
	cout << "\n\n" << current << " / " << max << endl;
	_fillGaugeImage->SetHorizontalFillAmount((float)current / max);
	std::wstringstream wss;
	wss << L"(" << current << L"/" << max << L")";
	wstring content = wss.str();
	_text->SetText(content);

}

void HealthGauge::SetTextCompo(TextPro* textCompo)
{
	_text = textCompo;
}
