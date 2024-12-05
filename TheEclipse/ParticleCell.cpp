#include "pch.h"
#include "ParticleCell.h"
#include "Texture.h"
#include "TimeManager.h"
#include "ResourceManager.h"

ParticleCell::ParticleCell(Vec2 position, Vec2 direction, float lifeTime, float speed)
{
	_position = position;
	_direction = direction;
	_lifeTime = lifeTime;
	_speed = speed;
	_texture = GET_SINGLE(ResourceManager)->TextureLoad(L"ParticleCell", L"Texture\\HitVFX.bmp");
}

void ParticleCell::Update()
{
	_currentLifeTime += GET_SINGLE(TimeManager)->GetDT();
	_position += _direction * _speed * GET_SINGLE(TimeManager)->GetDT();
}

void ParticleCell::Render(HDC _hdc)
{
	int width = _texture->GetWidth();
	int height = _texture->GetHeight();
	::TransparentBlt(_hdc
		, (int)(_position.x - width / 2) 
		, (int)(_position.y - height / 2)
		, width, height,
		_texture->GetTexDC()
		, 0, 0, width, height, RGB(255, 0, 255));
}

bool ParticleCell::IsDead()
{
	return _currentLifeTime >= _lifeTime;
}

void ParticleCell::Reset()
{
}
