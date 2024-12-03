#pragma once
#include "CanvasComponent.h"

class Image;
class HealthGauge : public CanvasComponent
{

private :
	Image* _fillGaugeImage;
	
public:
	void Initialize() override;
	void HandleRefreshGauge(int current, int max);
};
