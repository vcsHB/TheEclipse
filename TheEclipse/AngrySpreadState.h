#pragma once
class Projectile;
class AngrySpreadState
	: public State

{
public:
	AngrySpreadState(wstring name) :State(name) {};
	void Enter() override;
	void Exit() override;
protected:
	void Movement(float _dt) override;
	void Shooting(float _dt) override;
private:
	int moveIdx = 0;
	float transTime = 0;
	bool isTransed = false;
};

