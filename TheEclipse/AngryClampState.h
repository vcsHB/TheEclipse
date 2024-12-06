#pragma once
class Projectile;
class CrackLine;
class AngryClampState
	: public State
{
public:
	AngryClampState(wstring name) :State(name) {};
	void Enter() override;
	void Exit() override;
protected:
	void Movement(float _dt) override;
	void Shooting(float _dt) override;
private:
	CrackLine* crackLines[4];
	int crackLineIdx = 0;


	bool isCreated = false;
	float createTime = 0;
	float waittime = 0;
	Projectile* projectilles[24];
	int projIdx = 0;
};

