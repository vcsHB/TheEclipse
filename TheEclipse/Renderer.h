#pragma once
#include "Component.h"
#include "Animator.h"
#include "Animation.h"
class Renderer : public Component
{
public : 

	virtual void Render(HDC _hdc) override;

public:

	void SetSprite(Sprite sprite)
	{
		_currentSprite = sprite;

		
	}

protected:
	Sprite _currentSprite;
};

