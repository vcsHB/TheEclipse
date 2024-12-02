#include "pch.h"
#include "UpgradeData.h"

UpgradeData::UpgradeData(wstring name, wstring description, wstring textureKey)
{
	upgradeName = name;
	this->description = description;
	iconKey = textureKey;

}

UpgradeData::~UpgradeData()
{
	
}

