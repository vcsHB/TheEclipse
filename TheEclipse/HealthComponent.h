#pragma once
#include "Component.h"

class HealthComponent :
	public Component
{
public:
	HealthComponent();
	~HealthComponent();
public:
	void LateUpdate() override;
	void Render(HDC _hdc) override;
public:
	const int& GetHp() const { return m_hp; }
	void SetHp(int hp) { m_hp = hp; }
	bool DecreaseHP(int damage);
private:
	int m_hp;
};

