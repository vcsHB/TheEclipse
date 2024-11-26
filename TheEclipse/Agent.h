#pragma once
#include "Object.h"
#include "GameScene.h"
class Texture;
class Agent :
	public Object
{
public:
	virtual void Movement();
	virtual void Shooting();
private:
	void CreateProjectile(Vec2 dir, GameScene* scene);
	GameScene* currentscene;
	Texture* m_pTex;
	HealthComponent* healthComponent;
};

