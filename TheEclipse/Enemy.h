#pragma once
#include "Agent.h"
#include "HealthComponent.h"
class StateMachine;
class State;
class Enemy :
	public Agent
{
public:
	Enemy(WorldSpaceScene* scene, map<wstring, State*>* states);
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

	StateMachine* stateMachine;
	//StateMachine* GetStateMachine();
private:
	void CreateProjectile(Vec2 dir);
private:
	Vec2 vecarr[3];
	HealthComponent* healthComponent;
	float duration = 30;
	bool isShooting = false;
};

