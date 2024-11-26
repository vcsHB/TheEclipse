#pragma once
#include "CanvasComponent.h"
class Image;
class Button : public CanvasComponent
{
public :
	void Initialize() override;
public:
	
	// 실행되는 주체
	void OnClick();
	Vec2& GetSize() { return _size; }
private:
	Image* _image;
	Vec2 _size;
};

