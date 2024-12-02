#pragma once
#include "State.h"
#include "Enemy.h"
class StateMachine
{
public:
	StateMachine(Enemy* enemy, std::map< wstring, State*>* states);
	~StateMachine();
public:
	void ChangeState(wstring stateName);
public:
	State* Current() {
		return currentState;
	}
	void Update();
private:
	std::map< wstring, State*>* states;
	State* currentState;
};

