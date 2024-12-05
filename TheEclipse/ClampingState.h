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
	CrackLine* crackLines[16];
	int crackLineIdx = 0;
	float shootTime = 0;

	float sizeArr[4] = { 200 , 150 , 100 , 50 };
	int sizeIdx = 0;

};

