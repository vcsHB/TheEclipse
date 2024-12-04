#pragma once
//#include <queue>
//#include <map>
#include <type_traits> // std::is_base_of
#include "SceneManager.h"
#include "Scene.h"
#include "IPoolable.h"
#include "Projectile.h"

//template <typename T>
//concept poolable = std::is_base_of<IPoolable, T>::value;

class PoolManager
{
	//DECLARE_SINGLE(PoolManager);

	~PoolManager();
private:
	//static std::map<PoolingType, std::queue<IPoolable*>> pool;
	//static std::map<int, IPoolable*> enabledPool;
	static std::map<PoolingType, std::queue<IPoolable*>> pool;
	static std::map<int, IPoolable*> enabledPool;

public:
	//template <poolable T>
	//template <typename T>
	//static void AddPool(PoolingType type, int amount)
	//{
	//	if (pool.find(type) == pool.end())
	//	{ // 만들어진 풀링이 있음
	//		pool[type] = std::queue<IPoolable*>();
	//	}
	//	for (int i = 0; i < amount; i++)
	//	{
	//		IPoolable* poolable = new T;
	//		pool[type].push(poolable);
	//		GET_SINGLE(SceneManager)->GetCurrentScene().get()->AddObject(poolable->GetPoolObject(), LAYER::PROJECTILE);
	//	}
	//}

	static void AddPool(PoolingType type, IPoolable* poolable)
	{
		if (pool.find(type) == pool.end())
		{ // 만들어진 풀링이 있음
			pool[type] = std::queue<IPoolable*>();
		}
		pool[type].push(poolable);
		GET_SINGLE(SceneManager)->GetCurrentScene().get()->AddObject(poolable->GetPoolObject(), LAYER::PROJECTILE);
	}


	static IPoolable* Pop(PoolingType type);

	static void Push(IPoolable* poolable);


};