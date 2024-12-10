#pragma once
#include "CanvasComponent.h"

class Image;
class FadePanel : public CanvasComponent
{
private:
	Image* _imageComponent;
	float _duration = 1.5f;
	float _currentTime = 0.f; 
	bool _isFading = false;
	bool _onOff = false;
public:

	void OnEnable() override;
	void Update() override;
public:

	void Fade(bool value);
};

