#pragma once
#include "Agent.h"
#include "HealthComponent.h"
class Projectile;
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
	Projectile* CreateProjectile(Vec2 dir);
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);

	StateMachine* GetStateMachine();
private:
private:
	Texture* m_pTex2;  // ¾Þ±×¸® º¸½º
	StateMachine* stateMachine;
	HealthComponent* healthComponent;
	Collider* colliderComponent;
	float duration = 30;
	bool isShooting = false;
};

