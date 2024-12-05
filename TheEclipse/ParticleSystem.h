#pragma once
#include <string>
#include <vector>
#include "Component.h"
#include "Object.h"
#include "IPoolable.h"

class ParticleCell;
class ParticleSystem : public Object, public IPoolable
{
public :
	ParticleSystem(wstring textureName, Vec2 offset, float radius, int emmisionAmount, float lifeTime, float speed);
	~ParticleSystem();

public:
	void Update() override;
	void LateUpdate() override;
	void Render(HDC _hdc) override;

public:
	void Play();
	void Reset();
	

private:
	vector<ParticleCell*> _particleCells;

	std::wstring _textureName;
	Vec2 _offset;
	float _radius = 0.4f;
	int _emissionAmount = 5;
	float _lifeTime = 2.f;
	float _speed =1.f;


	float _currentLifeTime;

private:

	virtual PoolingType GetPoolingType() override;

	virtual Object* GetPoolObject() override;

	virtual void ResetItem() override;
	


};

