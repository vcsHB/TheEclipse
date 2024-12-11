#pragma once
#include "Agent.h"
#include "HealthComponent.h"
class Texture;
class PlayerStatus;
class Projectile;
class HealthGauge;

class Player : public Agent
{
public:
	Player(WorldSpaceScene* scene);
	virtual ~Player() override;
public:
	void Start() override;
	void Update() override;
	void Render(HDC _hdc) override;
	void Shooting() override;
	void Movement() override;
	Vec2 OriginPos() override;
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
private:
	void CreateProjectile(Vec2 dir);
	Projectile* GenerateProjectile(Vec2 position, Vec2 direction);
	void HandlePlayerDie(bool value);
	HealthComponent* healthComponent;
	HealthGauge* _healthGauge;
	float _currentShootCoolTime = 0.f;

	float _currentDashTime = 0.f;
	
	
public:
	PlayerStatus* playerStatus;
	HealthComponent* GetHealth() { return healthComponent; }


	//GameScene* currentScene;
	//HealthComponent* healthComponent;
	//Texture* m_pTex;
};

