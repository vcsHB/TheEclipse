#pragma once
class Projectile;
class TargetingState :
	public State
{
public:
	TargetingState(wstring name) :State(name) {};
	void Enter() override;
	void Exit() override;
protected:
	void Movement(float _dt) override;
	void Shooting(float _dt) override;

private:
	float waittime = 0;
	Projectile* projectilles[24];
	int projIdx = 0;
};