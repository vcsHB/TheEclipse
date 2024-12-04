#pragma once

#include "Player.h"
#include "Status.h"
#include "PlayerStatus.h"
#include "Stat.h"
class Player;
class UpgradeData
{
public:
	UpgradeData();
	UpgradeData(wstring& name, wstring& description, wstring& textureKey, Player* player, int upgradeValue);
	~UpgradeData();

protected:
	Player* _player;

public:
	wstring upgradeName;
	wstring description;
	wstring iconKey;

	int upgradeValue;
	bool isLocked = true;


public:

	virtual void ApplyUpgradeEffect();
};

