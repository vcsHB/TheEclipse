#pragma once
#include <map>
#include "Component.h"
class PlayerSkill;
class PlayerSkillController : public Component
{

public:
	map<wstring, PlayerSkill*> skillMap;

public:
	void AddSkill(wstring key, PlayerSkill* skill);
	PlayerSkill* GetSkill(wstring key);

};

