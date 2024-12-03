#include "pch.h"
#include "Stat.h"

Stat::Stat(int baseValue)
{
	_baseValue = baseValue;
}

Stat::~Stat()
{
}

void Stat::AddModifier(int value)
{

	_modifiers.push_back(value);
	_isValueChanged = true;
}

void Stat::RemoveModifier(int value)
{
	
	for (size_t i = 0; i < _modifiers.size();)
	{
		if (_modifiers[i] == value) {
			_modifiers.erase(_modifiers.begin() + i);
			break;
		}
		else
			i++;
	}
	_isValueChanged = true;
}

int Stat::GetValue()
{
	if (!_isValueChanged) return _changedValue;

	_changedValue = _baseValue;
	for (int value : _modifiers)
	{
		_changedValue += value;
	}
	_isValueChanged = false;
	return _changedValue;
}
