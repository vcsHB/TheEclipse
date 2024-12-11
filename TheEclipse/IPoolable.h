#pragma once
class Object;

enum class PoolingType
{
	Projectile,
	HitVFX
};

__interface IPoolable
{
public:
	virtual PoolingType GetPoolingType();
	virtual Object* GetPoolObject();
	virtual void ResetItem();
};