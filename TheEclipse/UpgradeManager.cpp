#include "pch.h"
#include "UpgradeManager.h"

int UpgradeManager::CalcMaxExp(int level)
{
    return level * 10;
}

void UpgradeManager::CheckUpgrade()
{
    int max = CalcMaxExp(_level);
    if (_exp >= max)
    {
        _exp = _exp - max;
        _level++;
        // ������ ���� �ʿ� + UI�� ����
    }
}

void UpgradeManager::GainExp(int amount)
{
    _exp += amount;
}

void UpgradeManager::Select(int index)
{

}


