#pragma once
#include "Agent.h"
#include "HealthComponent.h"
class Enemy :
	public Agent
{
public:
	Enemy(GameScene* scene);
	virtual ~Enemy();
public:
	void Update() override;
	void Render(HDC _hdc) override;
	void Shooting()override;
	void Movement() override;
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
private:
	void CreateProjectile(Vec2 dir, GameScene* scene);
private:
	Vec2 vecarr[3];
	HealthComponent *healthComponent ;
};

