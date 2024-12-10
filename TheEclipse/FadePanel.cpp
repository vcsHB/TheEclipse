#include "pch.h"
#include "FadePanel.h"
#include "TimeManager.h"
#include "Image.h"
#include "RectTransform.h"
#include "ResourceManager.h"
void FadePanel::OnEnable()
{

	_owner->AddComponent<Image>();
	_imageComponent = _owner->GetComponent<Image>();
	_imageComponent->SetVerticalFillAmount(0.f);
	_imageComponent->SetTexture(GET_SINGLE(ResourceManager)->TextureLoad(L"Black_BG", L"Texture\\Black_BG_Panel.bmp"));
}
void FadePanel::Update()
{
	if (!_isFading) return;

	if (_onOff)
		_currentTime += fDT;
	else
		_currentTime -= fDT;
	cout << "FillAmount : " << (float)_currentTime / _duration << endl;
	_imageComponent->SetVerticalFillAmount(_currentTime / _duration);
}
void FadePanel::Fade(bool value)
{
	if (_isFading) return;
	if (_onOff == value) return;
	_onOff = value;
	_isFading = true;
	_currentTime = value ? 0.f : 1.f;

}
