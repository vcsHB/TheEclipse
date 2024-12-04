#pragma once
#include "UpgradeData.h"

class AtkUpgrade : public UpgradeData
{
public:
	AtkUpgrade(wstring& name, wstring& description, wstring& textureKey, Player* player, int upgradeValue);
	
public:

	void ApplyUpgradeEffect() override;

};

