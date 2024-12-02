#include "pch.h"
#include "PlayerSkill.h"
#include "TimeManager.h"

PlayerSkill::PlayerSkill()
{

}

PlayerSkill::~PlayerSkill()
{

}

void PlayerSkill::Initialize(Player* player)
{
	_owner = player;

}

void PlayerSkill::Update()
{
	_currentTime += GET_SINGLE(TimeManager)->GetDT();
}

void PlayerSkill::UseSkill()
{
	_currentTime = 0;
}
