#include "pch.h"
#include "StateMachine.h"

StateMachine::StateMachine(Enemy* owner, map<wstring, State*>* states)
{
	SetStateList(owner, states);
}

StateMachine::~StateMachine()
{
}

void StateMachine::ChangeState(wstring stateName)
{
	currentState->Exit();
	currentState = states->at(stateName);
	currentState->Enter();
}

void StateMachine::SetStateList(Enemy* owner, std::map<wstring, State*>* states)
{
	if (currentState != nullptr)
		currentState->Exit();

	for (auto iter = states->begin(); iter != states->end(); iter++)
	{
		iter->second->Init(owner);
	}
	this->states = states;
	currentState = states->at(L"Idle");
	currentState->Enter();
}

void StateMachine::Update(float _dt)
{
	currentState->Update(_dt);
}
