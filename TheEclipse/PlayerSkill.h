#pragma once
#include <string>
class Player;
class PlayerSkill
{

public :
	PlayerSkill();
	virtual ~PlayerSkill();
private :
	Player* _owner;
	float _currentTime;
	float _coolTime = 10.f;

public :

	virtual void Initialize(Player* player);
	virtual void Update();
	virtual void UseSkill();



};

