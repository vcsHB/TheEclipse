#pragma once
#include "Agent.h"
#include "HealthComponent.h"
class Texture;
class Player : public Agent
{
public:
	Player(GameScene* scene);
	virtual ~Player();
public:
	void Update() override;
	void Render(HDC _hdc) override;
	void Shooting() override;
	void Movement() override;
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
private:
	void CreateProjectile(Vec2 dir, GameScene* scene);
	HealthComponent* healthComponent;
	//GameScene* currentScene;
	//HealthComponent* healthComponent;
	//Texture* m_pTex;
};

