#pragma once
#include "Agent.h"
#include "HealthComponent.h"
#include "GameScene.h"
class Enemy :
	public Object
{
public:
	Enemy(GameScene* scene);
	~Enemy();
public:
	void Update() override;
	void Render(HDC _hdc) override;
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
private:
	HealthComponent* healthComponent;
	GameScene* currentScene;

};

