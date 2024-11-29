#pragma once
#include "CanvasComponent.h"
class Texture;
class Image : public CanvasComponent
{

public:
	void Initialize() override;
	void Render(HDC hdc) override;
private:

	Texture* _texture;
	float _vertialFillAmount = 1.f; // 0.0 ~ 1.0
	float _horizontalFillAmount = 1.f; // 0.0 ~ 1.0

public:
	void SetTexture(Texture * texture);
	Texture* GetTexture() { return _texture; }
	Vec2 GetTextureSize();

	void SetVerticalFillAmount(float fillAmount)
	{
		_vertialFillAmount = fillAmount;
	}

	void SetHorizontalFillAmount(float fillAmount)
	{
		_horizontalFillAmount = fillAmount;
	}
};

