#pragma once

class IdleState : public State
{
public:
	IdleState(wstring name) :State(name) {};
	void Enter() override;
	void Exit() override;

protected:
	void Movement(float _dt) override;
	void Shooting(float _dt) override;
};

