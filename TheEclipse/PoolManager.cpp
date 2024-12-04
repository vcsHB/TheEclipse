#include "pch.h"
#include "PoolManager.h"
#include "Object.h"

std::unordered_map<PoolingType, std::queue<IPoolable*>> PoolManager::pool = {};
std::unordered_map<int, IPoolable*> PoolManager::enabledPool = {};

PoolManager::~PoolManager()
{
}

void PoolManager::Initialize()
{
	pool = {};
	enabledPool = {};
	
}

IPoolable* PoolManager::Pop(PoolingType type)
{
	if (pool[type].empty())
	{
		// 보충 예외 처리 일단 미룸
		//AddPool(type, )
		cout << "POOL ERROR : not poolObject in Pool";
	}
	IPoolable* poolObject = pool[type].front();
	pool[type].pop();
	Object* object = poolObject->GetPoolObject();
	enabledPool.insert({ object->GetId(), poolObject });
	object->enabled = true;
	poolObject->ResetItem();
	return poolObject;

}

void PoolManager::Push(IPoolable* poolable)
{
	int id = poolable->GetPoolObject()->GetId();
	if (enabledPool.count(id))
	{
		cout << "POOL ERROR : this Object is not regist in Pool" << "[ ID : " << id << " ]" << endl;
		return;
	}

	pool[poolable->GetPoolingType()].push(poolable);
	enabledPool.erase(id);
	poolable->GetPoolObject()->enabled = false;

}
