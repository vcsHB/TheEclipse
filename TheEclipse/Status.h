#pragma once
class Stat;

class Status
{
public:
	Status();
	Status(int health, int atk, int moveSpeed);
	virtual ~Status();

public :
	Stat* healthStat;
	Stat* atkStat;
	Stat* moveSpeedStat;
	
};

