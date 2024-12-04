#pragma once
class Object;

enum class PoolingType
{
	Projectile
};

__interface IPoolable
{
public:
	virtual PoolingType GetPoolingType();
	virtual Object* GetPoolObject();
	virtual void ResetItem();
};
//class IPoolable
//{
//public:
//	virtual PoolingType GetPoolingType() abstract;
//	virtual Object* GetPoolObject() abstract;
//	virtual void ResetItem() abstract;
//};