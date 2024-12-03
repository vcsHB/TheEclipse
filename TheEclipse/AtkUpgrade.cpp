#include "pch.h"
#include "AtkUpgrade.h"
#include "Player.h"
#include "Status.h"
#include "PlayerStatus.h"
#include "Stat.h"

AtkUpgrade::AtkUpgrade(wstring& name, wstring& description, wstring& textureKey, Player* player, int upgradeValue)
{
	//UpgradeData::UpgradeData(name, description, textureKey, player, upgradeValue);
	upgradeName = name;
	this->description = description;
	iconKey = textureKey;

	_player = player;
	this->upgradeValue = upgradeValue;
}

void AtkUpgrade::ApplyUpgradeEffect()
{
	UpgradeData::ApplyUpgradeEffect();
	_player->playerStatus->atkStat->AddModifier(upgradeValue);
}
