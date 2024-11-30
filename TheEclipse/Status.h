#pragma once
class Stat;
class Status
{

public:
	Status(int health, int atk, int moveSpeed);
	~Status();
public :
	Stat* healthStat;
	Stat* atkStat;
	Stat* moveSpeedStat;


};

