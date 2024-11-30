#pragma once
#include <vector>
class UpgradeManager
{
	DECLARE_SINGLE(UpgradeManager);

private:
	int _level = 1;
	int _exp = 0;

private:

	int CalcMaxExp(int level);
	void CheckUpgrade();
public:
	int GetLevel() { return _level; }
public:

	void GainExp(int amount);
	void Select(int index);
};

