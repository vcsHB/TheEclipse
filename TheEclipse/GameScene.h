#pragma once
#include "WorldSpaceScene.h"
class Player;
class State;

class GameScene :
	public WorldSpaceScene
{
public:
	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	void SetNextLevel(int level);
	void ResetPlayer(int level);
	void SpawnBoss(int level);
public:
	map<int, map<wstring, State*>>* stateData;
private:
	HWND m_hWnd1;
	HWND m_hWnd2;
};

