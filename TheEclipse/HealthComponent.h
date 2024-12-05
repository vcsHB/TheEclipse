#pragma once
#include "Component.h"
#include "Delegate.h"

class HealthComponent :
	public Component
{
public:
	Delegate<int, int> OnHealthChangedEvent = Delegate<int, int>({});;
	Delegate<bool> OnHealthValueChangedEvent = Delegate<bool>({});;
	HealthComponent();
	~HealthComponent();
public:
	void LateUpdate() override;
	void Render(HDC _hdc) override;
public:
	const int& GetHp() const { return m_hp; }
	void SetMaxHealth(int max) { _maxHealth = max; }
	void SetHp(int hp) { m_hp = hp; }
	void FillMaxHealth();
	bool DecreaseHP(int damage);
private:
	int m_hp;
	int _maxHealth;
};

