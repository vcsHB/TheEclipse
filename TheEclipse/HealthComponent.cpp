#include "pch.h"
#include "HealthComponent.h"

HealthComponent::HealthComponent()
{
}

HealthComponent::~HealthComponent()
{

}


bool HealthComponent::DecreaseHP(int damage)
{
	if (m_hp > 0)
	{
		m_hp -= damage;
	}

	return m_hp <= 0; 
}


void HealthComponent::LateUpdate()
{
}

void HealthComponent::Render(HDC _hdc)
{
}
