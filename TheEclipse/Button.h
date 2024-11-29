#pragma once
#include "CanvasComponent.h"
#include "Delegate.h"
class Image;

class Button : public CanvasComponent
{
public :
	void Initialize() override;
public:
	Delegate<bool> OnClickEvent = Delegate<bool>({});
	// ����Ǵ� ��ü
	void OnClick();
	Vec2& GetSize() { return _size; }
private:
	Image* _image;
	Vec2 _size;
};

