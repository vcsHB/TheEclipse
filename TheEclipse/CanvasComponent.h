#pragma once
class RectTransform;

class CanvasComponent
{

public :
 	virtual void Initialize();
	
	virtual void Update();
	virtual void Render(HDC hdc);

public:
	void SetOwner(RectTransform* owner) { _owner = owner; }
	RectTransform* GetOwner() { return _owner; }

protected:

	RectTransform* _owner;
};

