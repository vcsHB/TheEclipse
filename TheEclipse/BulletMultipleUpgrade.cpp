#include "pch.h"
#include "BulletMultipleUpgrade.h"

BulletMultipleUpgrade::BulletMultipleUpgrade(wstring& name, wstring& description, wstring& textureKey, Player* player, int upgradeValue)
{
	upgradeName = name;
	this->description = description;
	iconKey = textureKey;

	_player = player;
	this->upgradeValue = upgradeValue;
}

void BulletMultipleUpgrade::ApplyUpgradeEffect()
{
	UpgradeData::ApplyUpgradeEffect();
	_player->playerStatus->bulletMultipleStat->AddModifier(upgradeValue);
}
