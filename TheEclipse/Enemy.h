#pragma once
#include "Agent.h"
#include "HealthComponent.h"
#include "GameScene.h"
class Enemy :
	public Agent
{
public:
	Enemy(GameScene* scene);
	~Enemy();
};

