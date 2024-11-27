#pragma once
#include "Agent.h"
class HealthComponent;
class GameScene;
class Enemy :
	public Agent
{
public:
	Enemy(GameScene* scene);
	~Enemy();

public:
	void Update() override;
	void Render(HDC _hdc) override;
	//void SetPos(Vec2 v) override;
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
private:
	Vec2 originPos;

private:
	HealthComponent* healthComponent;
	GameScene* currentScene;
};

