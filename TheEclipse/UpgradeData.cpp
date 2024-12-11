#include "pch.h"
#include "UpgradeData.h"

UpgradeData::UpgradeData()
{
}

UpgradeData::UpgradeData(wstring& name, wstring& description, wstring& textureKey, Player* player, int upgradeValue)
{
	upgradeName = name;
	this->description = description;
	iconKey = textureKey;

	_player = player;
	this->upgradeValue = upgradeValue;
}

UpgradeData::~UpgradeData()
{
		
}

void UpgradeData::ApplyUpgradeEffect()
{
	isLocked = false;
}

