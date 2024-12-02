#include "pch.h"
#include "PlayerSkillController.h"

PlayerSkillController::PlayerSkillController()
{

}

PlayerSkillController::~PlayerSkillController()
{
	for (std::pair<wstring, PlayerSkill*> skillPair : skillMap)
	{
		delete skillPair.second;
		skillPair.second = nullptr;
	}
	skillMap.clear();
}

void PlayerSkillController::AddSkill(wstring key, PlayerSkill* skill)
{
	skillMap.insert({ key, skill });
}

PlayerSkill* PlayerSkillController::GetSkill(wstring key)
{
	return skillMap[key];
}
