#pragma once
#include "Status.h"
class PlayerStatus : public Status
{
public:
	PlayerStatus(int health, int atk, int moveSpeed, int bulletMultiple, int bulletSpeed, int shieldPower);
	~PlayerStatus() override;
public:

	Stat* bulletMultipleStat;
	Stat* bulletSpeedStat;
	Stat* shieldPowerStat;

};

