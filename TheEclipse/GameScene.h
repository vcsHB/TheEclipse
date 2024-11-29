#pragma once
#include "WorldSpaceScene.h"
class GameScene :
	public WorldSpaceScene
{
public:
	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;

};

