#pragma once
class Enemy;
class State
{
public:
	State(wstring name);
	virtual void Init(Enemy* owner);
	virtual void Enter();
	void Update(float _dt);
	virtual void Exit();
protected:
	virtual void Movement(float _dt) {};
	virtual void Shooting(float _dt) {};
protected:
	wstring name;
	Enemy* owner;
	float timerforMove = 0;
	float timerforShot = 0;
};

