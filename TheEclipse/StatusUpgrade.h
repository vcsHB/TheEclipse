#pragma once
#include "UpgradeData.h"

enum class UpgradeStatusType
{
	Health,
	Attack,
	MoveSpeed,
	BulletMultiple,
	BulletSpeed,
	ShieldSpeed

};

class StatusUpgrade : public UpgradeData
{


public:
	StatusUpgrade(wstring& name, wstring& description, wstring& textureKey, Player* player, int upgradeValue, UpgradeStatusType type);

private:
	UpgradeStatusType _upgradeStatType;

public:

	void ApplyUpgradeEffect() override;

};

