#pragma once
class Enemy;
class State
{
public:
	State(wstring name);
	virtual void Init(Enemy* owner);
	virtual void Enter();
	void Update();
	virtual void Exit();
protected:
	void Timer();
	virtual void Movement() {};
	virtual void Shooting() {};
protected:
	wstring name;
	Enemy* owner;
	float timer = 0;
};

