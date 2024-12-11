#pragma once
#include "CanvasComponent.h"

class Image;
class TextPro;
class HealthGauge : public CanvasComponent
{

private :
	Image* _fillGaugeImage;
	TextPro* _text;
	
public:
	void OnEnable() override;
	void Initialize() override;
	void HandleRefreshGauge(int current, int max);

public:

	void SetTextCompo(TextPro* textCompo);
};

