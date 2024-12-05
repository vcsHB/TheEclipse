#pragma once
class Enemy;
class Player;
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
	Player* player;
	float timerforMove = 0;
	float timerforShot = 0;
	Vec2 vPos;
};

