#pragma once
class Projectile;
class ClampingState :
	public State
{
public:
	ClampingState(wstring name) :State(name) {};
	void Enter() override;
	void Exit() override;

protected:
	void Movement(float _dt) override;
	void Shooting(float _dt) override;
private:
	Projectile* projectiles[2];
	float waittime = 0;

};

