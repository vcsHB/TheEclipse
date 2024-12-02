#pragma once
#include <vector>
class Stat
{
public:
	Stat(int baseValue);
	~Stat();

private :
	int _baseValue;
	vector<int> _modifiers;
	bool _isValueChanged = true;
	int _changedValue = 0;

public:
	void AddModifier(int value);
	void RemoveModifier(int value);

	int GetValue();

};

