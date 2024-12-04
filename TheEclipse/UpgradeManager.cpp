#include "pch.h"
#include "UpgradeManager.h"
#include "UpgradeButton.h"
#include "RectTransform.h"
#include "ExpGauge.h"
#include "TimeManager.h"
#include "Button.h"
#include "UpgradeData.h"
#include "AtkUpgrade.h"
#include "BulletMultipleUpgrade.h"
#include "StatusUpgrade.h"

UpgradeManager::~UpgradeManager()
{
    for (int i = 0; i < upgradeList.size(); i++)
    {
        delete upgradeList[i];
    }
    upgradeList.clear();
}

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
        RefreshGauge();
        LevelUp();
        // 레벨업 로직 필요 + UI랑 연계
        std::cout << "레벨업";
    }
}

void UpgradeManager::RefreshGauge()
{
    _expGauge->SetFillAmount(_exp, CalcMaxExp(_level));
}

void UpgradeManager::LevelUp()
{
    GET_SINGLE(TimeManager)->timeScale = 0.1f;
    _upgradeButton_1->GetOwner()->SetActive(true);
    SuffleSelectUpgradeData();

    _upgradeButton_1->SetUpgradeData(_data_1);
    _upgradeButton_2->SetUpgradeData(_data_2);


}

void UpgradeManager::SuffleSelectUpgradeData()
{
    vector<UpgradeData*> values = upgradeList;
    for (int i = values.size() - 1; i > 0; --i) {
        int randomIndex = std::rand() % (i + 1); // 0부터 i까지 난수 생성
        if (!values[randomIndex]->isLocked) continue;
        std::swap(values[i], values[randomIndex]); // values[i]와 values[j] 교환
    }
    _data_1 = values[0];
    _data_2 = values[1];
}

void UpgradeManager::HandleClickButton1(bool value)
{
    Select(0);
}

void UpgradeManager::HandleClickButton2(bool value)
{
    Select(1);
}


void UpgradeManager::Initialize(UpgradeButton* btn1, UpgradeButton* btn2, ExpGauge* gauge, Player* player)
{
    _upgradeButton_1 = btn1;
    _upgradeButton_2 = btn2;
    _expGauge = gauge;
    _player = player;

    _upgradeButton_1->GetOwner()->GetComponent<Button>()->OnClickEvent.Add(std::bind ( &UpgradeManager::HandleClickButton1, this, std::placeholders::_1));
    _upgradeButton_2->GetOwner()->GetComponent<Button>()->OnClickEvent.Add(std::bind ( &UpgradeManager::HandleClickButton2, this, std::placeholders::_1));
    //델리게이트.Add(std::bind(&클래스::메서드, this, std::placeholders::_1));

    // ==== Data 설정
    wstring name, description, texture;

    //  이거 함수로 빼
    texture = L"밍밍";
    name = L"체력 증가";
    description = L"";
    AddStatusUpgrade(L"체력 강화", L"최대 체력을 10 증가시킵니다", L"", UpgradeStatusType::Health, 10);
    AddStatusUpgrade(L"강화마법", L"공격력을 1 증가시킵니다", L"", UpgradeStatusType::Attack, 1);
    AddStatusUpgrade(L"신속", L"이동 속도를 1 증가시킵니다", L"", UpgradeStatusType::MoveSpeed, 1);
    AddStatusUpgrade(L"다중 탄환", L"마법 공격 탄환이 1개 증가합니다", L"", UpgradeStatusType::BulletMultiple, 1);
    AddStatusUpgrade(L"빠른 시전", L"마법 영창 시간이 단축됩니다", L"", UpgradeStatusType::FireSpeed, 4);
    //upgradeList.push_back(new StatusUpgrade(name, description, texture, _player, 2, UpgradeStatusType::Health));
    //upgradeList.push_back(new AtkUpgrade(L"공격력 업2", L"설명인..", L"TextureMing", _player, 3));

    
}

void UpgradeManager::GainExp(int amount)
{
    _exp += amount;
    CheckUpgrade();
    RefreshGauge();
    std::cout << "Gain EXP : " << amount;

}



void UpgradeManager::Select(int index)
{
    GET_SINGLE(TimeManager)->timeScale = 1.f;
    _upgradeButton_1->GetOwner()->SetActive(false);
    
    if (index == 0)
    {
        _data_1->ApplyUpgradeEffect();
    }
    else {
        _data_2->ApplyUpgradeEffect();

    }
}

void UpgradeManager::AddStatusUpgrade(wstring name, wstring description, wstring textureName, UpgradeStatusType type, int value)
{
    upgradeList.push_back(new StatusUpgrade(name, description, textureName, _player, value, UpgradeStatusType::Health));
}


