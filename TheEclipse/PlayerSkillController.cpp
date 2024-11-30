#include "pch.h"
#include "PlayerSkillController.h"

void PlayerSkillController::AddSkill(wstring key, PlayerSkill* skill)
{

	skillMap.insert({ key, skill });
}

PlayerSkill* PlayerSkillController::GetSkill(wstring key)
{
	return skillMap[key];
}
