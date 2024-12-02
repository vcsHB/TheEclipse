#include "pch.h"
#include "Status.h"
#include "PlayerStatus.h"
#include "Stat.h"

PlayerStatus::PlayerStatus(int health, int atk, int moveSpeed, int bulletMultiple, int bulletSpeed, int shieldPower)
{
	healthStat = new Stat(health);
	atkStat = new Stat(atk);
	moveSpeedStat = new Stat(moveSpeed);
	bulletMultipleStat = new Stat(bulletMultiple);
	bulletSpeedStat = new Stat(bulletSpeed);
	shieldPowerStat = new Stat(shieldPower);

}

PlayerStatus::~PlayerStatus()
{
	Status::~Status();
	delete bulletMultipleStat;
	delete bulletSpeedStat;
	delete shieldPowerStat;
}
