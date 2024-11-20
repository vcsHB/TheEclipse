#pragma once
#include "CanvasComponent.h"
class Texture;
class Image : public CanvasComponent
{

public:
	void Render(HDC hdc) override;
public:

	Texture* _texture;



};

