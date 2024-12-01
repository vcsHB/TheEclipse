#pragma once
#include "WorldSpaceScene.h"
class State;

class GameScene :
	public WorldSpaceScene
{
public:
	// Scene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	void SetNextLevel(int level);
	void ResetPlayer(int level);
	void SpawnBoss(int level);
public:
	map<int, map<wstring, State*>>* stateData;
};

