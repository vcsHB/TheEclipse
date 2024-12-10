#pragma once
#include "WorldSpaceScene.h"
class State;
class GameScene_2 : public WorldSpaceScene
{
public:

	virtual void Init() override;
	virtual void Update() override;
	virtual void Release() override;

public:
	map<int, map<wstring, State*>>* stateData;
};

