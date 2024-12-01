#pragma once

class IdleState : public State
{
public: 
	IdleState(wstring name):State(name){};
	void Enter() override;
	void Exit() override;

protected:
	void Movement() override;
	void Shooting() override;
};

