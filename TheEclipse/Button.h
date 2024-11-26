#pragma once
#include "CanvasComponent.h"
class Image;
class Button : public CanvasComponent
{
public :
	void Initialize() override;
public:
	
	// ����Ǵ� ��ü
	void OnClick();
	Vec2& GetSize() { return _size; }
private:
	Image* _image;
	Vec2 _size;
};

