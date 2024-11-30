#include "pch.h"
#include "Status.h"
#include "Stat.h"

Status::Status(int health, int atk, int moveSpeed)
{
	healthStat = new Stat(health);
	atkStat = new Stat(atk);
	moveSpeedStat = new Stat(moveSpeed);
}

Status::~Status()
{
	delete healthStat;
	delete atkStat;
	delete moveSpeedStat;
}
