#pragma once
#include "UpgradeData.h"
class BulletMultipleUpgrade : public UpgradeData
{

public:
	BulletMultipleUpgrade(wstring& name, wstring& description, wstring& textureKey, Player* player, int upgradeValue);

public:

	void ApplyUpgradeEffect() override;

};

