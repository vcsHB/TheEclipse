#pragma once
class SideSpreadState :
	public State
{
public:
	SideSpreadState(wstring name) :State(name) {};
	void Enter() override;
	void Exit() override;
protected:
	void Movement(float _dt) override;
	void Shooting(float _dt) override;
private:
	int moveIdx = 0;
	float durationTime = 0;
};

