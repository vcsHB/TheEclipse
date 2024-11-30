#pragma once
#include "Agent.h"
#include "HealthComponent.h"
class Texture;
class PlayerStatus;
class Player : public Agent
{
public:
	Player(WorldSpaceScene* scene);
	virtual ~Player() override;
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
	void CreateProjectile(Vec2 dir);
	HealthComponent* healthComponent;
	PlayerStatus* _playerStatus;

	//GameScene* currentScene;
	//HealthComponent* healthComponent;
	//Texture* m_pTex;
};

