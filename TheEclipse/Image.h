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
public:
	void SetTexture(Texture * texture);
	Texture* GetTexture() { return _texture; }
	Vec2 GetTextureSize();

};

