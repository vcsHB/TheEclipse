#pragma once
#include "Component.h"
class UIPanel : public Component
{
private:
	bool _isUIActive;
public :
	const void SetActive(bool value)
	{
		_isUIActive = value;
	}
	void OnClick();


};

