#pragma once
class CrackLine;
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
	CrackLine* crackLines[4];
	CrackLine* shootingCrackLines[4];
	int crackLineIdx = 0;

};

