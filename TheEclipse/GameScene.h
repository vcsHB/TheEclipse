#pragma once
#include "WorldSpaceScene.h"
class GameScene :
	public WorldSpaceScene
{
public:
	// Scene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;

};

