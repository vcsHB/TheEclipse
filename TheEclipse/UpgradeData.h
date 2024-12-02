#pragma once
class UpgradeData
{
public:
	UpgradeData(wstring name, wstring description, wstring textureKey);
	~UpgradeData();

private:
	

public:
	wstring upgradeName;
	wstring description;
	wstring iconKey;

	bool isLocked = true;

public :

};

