#pragma once
#include <vector>
class UpgradeData;

class UpgradeManager
{
	DECLARE_SINGLE(UpgradeManager);

	~UpgradeManager();
private:
	int _level = 1;
	int _exp = 0;
	vector<UpgradeData*> upgradeList;
private:

	int CalcMaxExp(int level);
	void CheckUpgrade();
public:
	int GetLevel() { return _level; }
public:
	void Init();

	void GainExp(int amount); // ����ġ ȹ��ó. �ƽ��ƽ��� ȸ�Ǳ⵿, �� �ǰ�
	void Select(int index);
};

