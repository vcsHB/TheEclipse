#include "pch.h"
#include "StatusUpgrade.h"

StatusUpgrade::StatusUpgrade(wstring& name, wstring& description, wstring& textureKey, Player* player, int upgradeValue, UpgradeStatusType type)
{
	upgradeName = name;
	this->description = description;
	iconKey = textureKey;

	_player = player;
	this->upgradeValue = upgradeValue;
	_upgradeStatType = type;
}

void StatusUpgrade::ApplyUpgradeEffect()
{
	UpgradeData::ApplyUpgradeEffect();
	switch (_upgradeStatType)
	{

	case UpgradeStatusType::Health:
		_player->playerStatus->healthStat->AddModifier(upgradeValue);
		break; 

	case UpgradeStatusType::Attack:
		_player->playerStatus->atkStat->AddModifier(upgradeValue);
		break;

	case UpgradeStatusType::MoveSpeed:
		_player->playerStatus->moveSpeedStat->AddModifier(upgradeValue);
		break;

	case UpgradeStatusType::BulletMultiple:
		_player->playerStatus->bulletMultipleStat->AddModifier(upgradeValue);
		break;

	case UpgradeStatusType::BulletSpeed:
		_player->playerStatus->bulletSpeedStat->AddModifier(upgradeValue);
		break;
	case UpgradeStatusType::FireSpeed:
		_player->playerStatus->fireSpeedStat->AddModifier(upgradeValue);
		break;

	case UpgradeStatusType::ShieldSpeed:
		_player->playerStatus->shieldPowerStat->AddModifier(upgradeValue);
		break;
	}

}
