#include "pch.h"
#include "ParticleSystem.h"
#include "ParticleCell.h"
#include "TimeManager.h"
#include "PoolManager.h"
#include <math.h>

ParticleSystem::ParticleSystem(wstring textureName, Vec2 offset, float radius, int emmisionAmount, float lifeTime, float speed)
{
	_textureName = textureName;
	_offset = offset;
	_radius = radius;
	_emissionAmount = emmisionAmount;
	_lifeTime = lifeTime;
	_speed = speed;
}

ParticleSystem::~ParticleSystem()
{
	for (size_t i = 0; i < _particleCells.size();)
	{
		ParticleCell* cell = _particleCells[i];
		if (cell != nullptr )
		{
			delete cell;
			_particleCells.erase(_particleCells.begin() + i);
		}
	}
}


void ParticleSystem::Update()
{
	for (size_t i = 0; i < _particleCells.size();)
	{
		ParticleCell* cell = _particleCells[i];
		if (cell == nullptr || cell->IsDead())
		{
			delete cell;
			_particleCells.erase(_particleCells.begin() + i);
			continue;
		}
		cell->Update();
		i++;
	}
	

}

void ParticleSystem::LateUpdate()
{
	_currentLifeTime += GET_SINGLE(TimeManager)->GetDT();

	if (_currentLifeTime >= _lifeTime)
	{
		PoolManager::Push(this);
	}

}

void ParticleSystem::Render(HDC _hdc)
{
	for (size_t i = 0; i < _particleCells.size();)
	{
		ParticleCell* cell = _particleCells[i];
		if (cell == nullptr) continue;
		cell->Render(_hdc);
		i++;
	}
}


void ParticleSystem::Play()
{
	cout << GetId() << "가 아이디임";
	srand(time(0));
	Vec2 zero = { 0,0 };
	for (int i = 0; i < _emissionAmount; i++)
	{
		float randomX = cos(rand());
		float randomY = sin(rand());
		Vec2 randomPosition = {randomX, randomY};
		Vec2 direction = randomPosition - zero;
		direction.Normalize();
		ParticleCell* cell = new ParticleCell(randomPosition + GetPos(), direction, _lifeTime, _speed);
		_particleCells.push_back(cell);
	}

}

void ParticleSystem::Reset()
{
}

PoolingType ParticleSystem::GetPoolingType()
{
	return PoolingType::HitVFX;
}

Object* ParticleSystem::GetPoolObject()
{
	return this;
}

void ParticleSystem::ResetItem()
{
	_currentLifeTime = 0.f;
	Reset();
}
