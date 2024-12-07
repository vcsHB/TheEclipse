#pragma once
#include "Agent.h"
#include "HealthComponent.h"
class Projectile;
class CrackLine;
class StateMachine;
class State;
class Enemy :
	public Agent
{
public:
	Enemy(WorldSpaceScene* scene, map<int, map<wstring, State*>>* states);
	virtual ~Enemy();
public:
	void Update() override;
	void Render(HDC _hdc) override;
	Projectile* CreateProjectile(Vec2 dir);
	CrackLine* CreateCrackLine();
	void Blink(bool active) override;
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);

	StateMachine* GetStateMachine();
private:
	void DoAnimation(wstring name, wstring path);
	void ChangeToAngryMode();
public:
	bool isAngry = false;
private:
	map<int, map<wstring, State*>>* statesArr;
	StateMachine* stateMachine;
	HealthComponent* healthComponent;
	Collider* colliderComponent;
	float duration = 30;

};

