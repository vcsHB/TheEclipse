#pragma once
#pragma once
class CrackLine;
class WallThrowState :
	public State
{
public:
	WallThrowState(wstring name) :State(name) {};
	void Enter() override;
	void Exit() override;
protected:
	void Movement(float _dt) override;
	void Shooting(float _dt) override;

private:
	CrackLine* crackLines[16];
	int crackLineIdx = 0;

	float waitTime = 0;

	Vec2 positionArr[16] =
	{ {-150, -300 } , {150, -300 }
	, {-150, 300 } , { 150, 300}
	, {-300, 150 } , {300 , 150}
	, {-300 , -150}, {300 , -150}
	, {-150, -300 } , {150, -300 }
	, {-150, 300 } , { 150, 300}
	, {-300, 150 } , {300 , 150}
	, {-300 , -150}, {300 , -150}
	};

};