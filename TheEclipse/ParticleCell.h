#pragma once

class Texture;
class ParticleCell
{

public:
	ParticleCell(Vec2 position, Vec2 direction, float lifeTime, float speed);
public:
	void Update();
	void Render(HDC _hdc);
public:

	bool IsDead();
	void Reset();

private :
	Texture* _texture;
	Vec2 _position;
	Vec2 _direction;
	float _lifeTime;
	float _speed;
	float _size;

private:
	float _currentLifeTime = 0;

	
};

