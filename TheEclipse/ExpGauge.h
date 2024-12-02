#pragma once
#include "CanvasComponent.h"
class Image;
class ExpGauge : public CanvasComponent
{

public:
	void OnEnable() override;
	void Initialize() override;

public:
	void SetFillAmount(int current, int max);


private :

	Image* _fillImage;
};

