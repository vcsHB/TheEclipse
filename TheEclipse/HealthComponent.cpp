#include "pch.h"
#include "HealthComponent.h"

HealthComponent::HealthComponent()
{
}

HealthComponent::~HealthComponent()
{

}


void HealthComponent::FillMaxHealth() 
{ 
	m_hp = _maxHealth; 
	OnHealthChangedEvent.Invoke(m_hp, _maxHealth);
}

bool HealthComponent::DecreaseHP(int damage)
{
	if (m_hp > 0)
	{
		m_hp -= damage;
	}
	cout << "\n=========== Health Changed" << endl;
	if (m_hp <= 0)
	{
		OnDieEvent.Invoke(true);
	}
	OnHealthChangedEvent.Invoke(m_hp, _maxHealth);
	return m_hp <= 0; 
}


void HealthComponent::LateUpdate()
{
}

void HealthComponent::Render(HDC _hdc)
{
}
