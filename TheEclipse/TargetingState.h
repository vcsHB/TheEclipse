#pragma once
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
};