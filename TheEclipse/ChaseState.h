#pragma once
class Projectile;
class ChaseState :
	public State
{
public:
	ChaseState(wstring name) :State(name) {};
	void Enter() override;
	void Exit() override;
protected:
	void Movement(float _dt) override;
	void Shooting(float _dt) override;

private:
	Projectile* projectilles[24];
	int projIdx = 0;
	float targetingTime = 0;
};

