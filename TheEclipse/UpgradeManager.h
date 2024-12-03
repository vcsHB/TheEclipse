#pragma once
#include <vector>
class UpgradeData;
class UpgradeButton;
class ExpGauge;
class Player;

class UpgradeManager
{
	DECLARE_SINGLE(UpgradeManager);

	~UpgradeManager();
private:
	int _level = 1;
	int _exp = 0;
	Player* _player;
	vector<UpgradeData*> upgradeList;
	UpgradeButton* _upgradeButton_1;
	UpgradeButton* _upgradeButton_2;
	ExpGauge* _expGauge;

	UpgradeData* _data_1;
	UpgradeData* _data_2;

private:


	int CalcMaxExp(int level);
	void CheckUpgrade();
	void RefreshGauge();
	void LevelUp();
	void SuffleSelectUpgradeData();

	void HandleClickButton1(bool value);
	void HandleClickButton2(bool value);

public:
	int GetLevel() { return _level; }
public:
	void Initialize(UpgradeButton* btn1, UpgradeButton* btn2, ExpGauge* gauge, Player* player);

	void GainExp(int amount); // 경험치 획득처. 아슬아슬한 회피기동, 적 피격
	void Select(int index);
};

